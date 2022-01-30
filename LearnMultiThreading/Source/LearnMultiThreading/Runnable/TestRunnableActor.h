// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestRunnableActor.generated.h"

UCLASS()
class LEARNMULTITHREADING_API ATestRunnableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestRunnableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//从0开始的计数器
	int32 TestCount;

	UPROPERTY(EditAnywhere)
	int32 TestTarget;
};
