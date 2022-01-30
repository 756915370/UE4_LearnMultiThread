#pragma once

class FWorkTask
{
	FString TaskName;
	TArray<TGraphTask<FWorkTask>*> ChildTasks;
	AActor* TaskOwner;
public:
	FWorkTask(FString Name, TArray<TGraphTask<FWorkTask>*> Children, AActor* Actor) : TaskName(Name),
		ChildTasks(Children), TaskOwner(Actor)
	{}
	~FWorkTask()
	{}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FWorkTask, STATGROUP_TaskGraphTasks);
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}
	
	//ESubsequentsMode::TrackSubsequents 追踪完成状态，一般用这个
	//ESubsequentsMode::FireAndForget 做了以后无法得知是否完成，只有没有任何依赖的Task才用。亲测用了这个容易崩溃。
	static ESubsequentsMode::Type GetSubsequentsMode() { return ESubsequentsMode::TrackSubsequents; }
	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);
};
