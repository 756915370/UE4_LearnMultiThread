// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestAsyncActor.generated.h"

UCLASS()
class LEARNMULTITHREADING_API ATestAsyncActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestAsyncActor();

protected:
	double OldTime;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TargetCounter;
	
	UFUNCTION(BlueprintCallable)
	void TestAsyncTaskClass();

	UFUNCTION(BlueprintCallable)
	void TestAsyncTaskClass_Synchronous();

	UFUNCTION(BlueprintCallable)
	void TestAsyncTaskFunc_AnyThread();
	
	UFUNCTION(BlueprintCallable)
	void TestAsyncTaskFunc_GameThread();

	UFUNCTION(BlueprintCallable)
	void TestAsyncFunc_NoReturn();

	UFUNCTION(BlueprintCallable)
	void TestAsyncFunc_WithReturn();

	UFUNCTION(BlueprintCallable)
	void TestAsyncFunc_ParallelFor();
};
