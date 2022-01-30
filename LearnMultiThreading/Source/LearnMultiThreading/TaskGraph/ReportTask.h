#pragma once

class FReportTask
{
	FString TaskName;
	AActor* TaskOwner;
public:
	FReportTask(FString Name, AActor* Actor) : TaskName(Name), TaskOwner(Actor)
	{
	}

	~FReportTask()
	{
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FReportTask, STATGROUP_TaskGraphTasks);
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::GameThread;
	}
 
	static ESubsequentsMode::Type GetSubsequentsMode() { return ESubsequentsMode::TrackSubsequents; }
	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent);
};
