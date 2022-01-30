// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAsyncActor.h"

#include "TestAsyncTask.h"


// Sets default values
ATestAsyncActor::ATestAsyncActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATestAsyncActor::TestAsyncTaskClass()
{
	OldTime = FPlatformTime::Seconds();
	//使用其他线程
	(new FAutoDeleteAsyncTask<FTestAsyncTask>(TargetCounter))->StartBackgroundTask();
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) main thread end."), __LINE__, (End-OldTime)*1000);
}

void ATestAsyncActor::TestAsyncTaskClass_Synchronous()
{
	OldTime = FPlatformTime::Seconds();
	//使用当前线程
	(new FAutoDeleteAsyncTask<FTestAsyncTask>(TargetCounter))->StartSynchronousTask();
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) main thread end."), __LINE__, (End-OldTime)*1000);
}

void ATestAsyncActor::TestAsyncTaskFunc_AnyThread()
{
	OldTime = FPlatformTime::Seconds();
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		double Result = 0;
		for (int32 i = 0; i < TargetCounter; i++)
		{
			Result += FMath::Sqrt(i) / TargetCounter;
		}

		UE_LOG(LogTemp, Log, TEXT("@%u wait TargetCounterR(%f)"), __LINE__, Result);

		double End = FPlatformTime::Seconds();
		UE_LOG(LogTemp, Log, TEXT("@%u wait millisecond(%f) end."), __LINE__, (End-OldTime)*1000);
	});
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) main thread end."), __LINE__, (End-OldTime)*1000);
}

void ATestAsyncActor::TestAsyncTaskFunc_GameThread()
{
	OldTime = FPlatformTime::Seconds();
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		double Result = 0;
		for (int32 i = 0; i < TargetCounter; i++)
		{
			Result += FMath::Sqrt(i) / TargetCounter;
		}
		UE_LOG(LogTemp, Log, TEXT("@%u wait TargetCounterR(%f)"), __LINE__, Result);

		double End = FPlatformTime::Seconds();
		UE_LOG(LogTemp, Log, TEXT("@%u wait millisecond(%f) end."), __LINE__, (End-OldTime)*1000);
	});
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) main thread end."), __LINE__, (End-OldTime)*1000);
}

void ATestAsyncActor::TestAsyncFunc_NoReturn()
{
	//TaskGraphMainThread 计算时间最慢
	//Thread 主线程结束时间最慢
	OldTime = FPlatformTime::Seconds();
	Async(EAsyncExecution::TaskGraph, [=]()
	{
		double Result = 0;
		for (int32 i = 0; i < TargetCounter; i++)
		{
			Result += FMath::Sqrt(i) / TargetCounter;
		}
		UE_LOG(LogTemp, Log, TEXT("@%u wait TargetCounterR(%f)"), __LINE__, Result);
		double End = FPlatformTime::Seconds();
		UE_LOG(LogTemp, Log, TEXT("@%u wait millisecond(%f) end."), __LINE__, (End-OldTime)*1000);
	});
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) main thread end."), __LINE__, (End-OldTime)*1000);
}

void ATestAsyncActor::TestAsyncFunc_WithReturn()
{
	OldTime = FPlatformTime::Seconds();
	TFuture<double> FutureResult = Async(EAsyncExecution::TaskGraph, [=]()
	{
		double Result = 0;
		for (int32 i = 0; i < TargetCounter; i++)
		{
			Result += FMath::Sqrt(i) / TargetCounter;
		}
		
		double End = FPlatformTime::Seconds();
		UE_LOG(LogTemp, Log, TEXT("@%u wait millisecond(%f) end."), __LINE__, (End-OldTime)*1000);
		return Result;
	});
	//使用Get获取返回值，会阻塞主线程
	UE_LOG(LogTemp, Log, TEXT("@%u wait TargetCounterR(%f)"), __LINE__, FutureResult.Get());
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) main thread end."), __LINE__, (End-OldTime)*1000);
}

//本案例使用ParallerlFor总计算时间会变慢
void ATestAsyncActor::TestAsyncFunc_ParallelFor()
{
	OldTime = FPlatformTime::Seconds();
	int Internal = TargetCounter / 10;
	
	auto FutureResult = Async(EAsyncExecution::TaskGraph, [=]()
	{
		TArray<double> ResultArray;
		ResultArray.Init(0, 10);
		ParallelFor(ResultArray.Num(), [&ResultArray,Internal,this](int32 Index)
		{
			for (int32 i = Index * Internal; i < (Index + 1) * Internal; i++)
			{
				ResultArray[Index] += FMath::Sqrt(i)/TargetCounter;
			}
		});
		double Sum = 0;
		for (int32 j = 0; j < ResultArray.Num(); j++)
		{
			Sum += ResultArray[j];
		}
		UE_LOG(LogTemp, Log, TEXT("@%u wait TargetCounterR(%f)"), __LINE__, Sum);
		double End = FPlatformTime::Seconds();
		UE_LOG(LogTemp, Log, TEXT("@%u wait millisecond(%f) end."), __LINE__, (End-OldTime)*1000);
		return Sum;
	});
	//UE_LOG(LogTemp, Log, TEXT("@%u wait TargetCounterR(%f)"), __LINE__, FutureResult.Get());
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) main thread end."), __LINE__, (End-OldTime)*1000);
}
