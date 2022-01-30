#include "WorkTask.h"

#include "ReportTask.h"

void FWorkTask::DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__ " %s:Begin"), *TaskName);
	for (TGraphTask<FWorkTask>* Task : ChildTasks)
	{
		if (Task)
		{
			Task->Unlock();
			MyCompletionGraphEvent->DontCompleteUntil(Task->GetCompletionEvent());
		}
	}
	// do something
	MyCompletionGraphEvent->DontCompleteUntil(TGraphTask<FReportTask>::CreateTask().
		ConstructAndDispatchWhenReady(TaskName, TaskOwner));
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__ " %s:End"), *TaskName);
}
