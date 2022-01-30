#include "ReportTask.h"

#include "TestTaskGraphActor.h"

void FReportTask::DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
	ATestTaskGraphActor* Actor = Cast<ATestTaskGraphActor>(TaskOwner);
	if (IsValid(Actor))
	{
		Actor->OnTaskComplete(TaskName);
	}
}
