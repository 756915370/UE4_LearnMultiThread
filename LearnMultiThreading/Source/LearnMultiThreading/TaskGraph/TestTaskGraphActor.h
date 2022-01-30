// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestTaskGraphActor.generated.h"

USTRUCT(BlueprintType)
struct FTaskItem
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString TaskName;

	FGraphEventRef GraphEvent;
	TGraphTask<class FWorkTask>* GraphTask;

	FTaskItem()
		: TaskName(TEXT("NoName")), GraphEvent(nullptr), GraphTask(nullptr)
	{
	}

	FTaskItem(FString Name, FGraphEventRef EventRef = FGraphEventRef())
		: TaskName(Name), GraphEvent(EventRef), GraphTask(nullptr)
	{
	}

	FTaskItem(FString Name, TGraphTask<class FWorkTask>* Task = nullptr)
		: TaskName(Name), GraphEvent(nullptr), GraphTask(Task)
	{
	}

	~FTaskItem() { GraphEvent = nullptr; }
};

UCLASS()
class LEARNMULTITHREADING_API ATestTaskGraphActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestTaskGraphActor();

public:
	UFUNCTION(BlueprintCallable)
	FTaskItem CreateTask(FString TaskName, const TArray<FTaskItem>& Prerequisites,
	                     const TArray<FTaskItem>& ChildTasks, bool DispatchWhenReady = true);

	UFUNCTION(BlueprintCallable)
	FTaskItem CreateTaskPure(FString TaskName, bool DispatchWhenReady = true)
	{
		const TArray<FTaskItem> Empty;
		return CreateTask(TaskName, Empty, Empty, DispatchWhenReady);
	}

	UFUNCTION(BlueprintCallable)
	FTaskItem CreateTaskWithPrerequisitesOnly(FString TaskName, const TArray<FTaskItem>& Prerequisites,
	                                          bool DispatchWhenReady = true)
	{
		return CreateTask(TaskName, Prerequisites, TArray<FTaskItem>(), DispatchWhenReady);
	}

	UFUNCTION(BlueprintCallable)
	FTaskItem CreateTaskWithChildTasksOnly(FString TaskName, const TArray<FTaskItem>& ChildTasks,
	                                       bool DispatchWhenReady = true)
	{
		return CreateTask(TaskName, TArray<FTaskItem>(), ChildTasks, DispatchWhenReady);
	}

	UFUNCTION(BlueprintCallable)
	void FireTask(const FTaskItem& Task);

	void OnTaskComplete(const FString& TaskName);
};
