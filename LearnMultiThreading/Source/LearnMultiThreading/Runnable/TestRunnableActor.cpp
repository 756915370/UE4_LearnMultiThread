// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRunnableActor.h"

#include "TestRunnable.h"


// Sets default values
ATestRunnableActor::ATestRunnableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestRunnableActor::BeginPlay()
{
	Super::BeginPlay();
	FTestRunnable* Runnable1 = new FTestRunnable(TEXT("线程1"), this);
	FTestRunnable* Runnable2 = new FTestRunnable(TEXT("线程2"), this);
	FRunnableThread* RunnableThread1 = FRunnableThread::Create(Runnable1, *Runnable1->MyThreadName);
	FRunnableThread* RunnableThread2 = FRunnableThread::Create(Runnable2, *Runnable2->MyThreadName);
}

