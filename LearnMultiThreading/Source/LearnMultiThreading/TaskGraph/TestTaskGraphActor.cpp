// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTaskGraphActor.h"

#include "WorkTask.h"


// Sets default values
ATestTaskGraphActor::ATestTaskGraphActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

FTaskItem ATestTaskGraphActor::CreateTask(FString TaskName, const TArray<FTaskItem>& Prerequisites,
	const TArray<FTaskItem>& ChildTasks, bool DispatchWhenReady)
{
	FGraphEventArray PrerequisiteEvents;
	TArray<TGraphTask<FWorkTask>*> ChildEvents;
	UE_LOG(LogTemp, Log, TEXT("Task[%s] is Created."), *TaskName);
	if (Prerequisites.Num() > 0)
	{
		PrerequisiteEvents.Reserve(Prerequisites.Num());
		for (FTaskItem Item : Prerequisites)
		{
			if (Item.GraphTask)
			{
				PrerequisiteEvents.Add(Item.GraphTask->GetCompletionEvent());
				UE_LOG(LogTemp, Log, TEXT("Task[%s] wait Task[%s]"), *TaskName, *Item.TaskName);
			}
			else if (Item.GraphEvent.IsValid())
			{
				PrerequisiteEvents.Add(Item.GraphEvent);
				UE_LOG(LogTemp, Log, TEXT("Task[%s] wait Task[%s]"), *TaskName, *Item.TaskName);
			}
		}
	}
	if (ChildTasks.Num() > 0)
	{
		ChildEvents.Reserve(ChildTasks.Num());
		for (FTaskItem Item : ChildTasks)
		{
			if (Item.GraphTask)
			{
				ChildEvents.Add(Item.GraphTask);
				UE_LOG(LogTemp, Log, TEXT("Task[%s] will execute after Task[%s]"), *Item.TaskName, *TaskName);
			}
		}
	}
	
	if (DispatchWhenReady)
	{
		//ConstructAndDispatchWhenReady返回的是Event
		return FTaskItem(TaskName, TGraphTask<FWorkTask>::CreateTask(&PrerequisiteEvents).
			ConstructAndDispatchWhenReady(TaskName, ChildEvents, this));
	}
	//ConstructAndHold返回的是Task
	return FTaskItem(TaskName, TGraphTask<FWorkTask>::CreateTask(&PrerequisiteEvents).
		ConstructAndHold(TaskName, ChildEvents, this));
}

void ATestTaskGraphActor::FireTask(const FTaskItem& Task)
{
	if(Task.GraphTask)
	{
		UE_LOG(LogTemp, Log, TEXT("Task[%s] Fire."), *Task.TaskName);
		Task.GraphTask->Unlock();
	}
}

void ATestTaskGraphActor::OnTaskComplete(const FString& TaskName)
{
	UE_LOG(LogTemp, Log, TEXT("Task[%s] is Reported."), *TaskName);
}
