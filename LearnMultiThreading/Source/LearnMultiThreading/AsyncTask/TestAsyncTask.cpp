#include "TestAsyncTask.h"

void FTestAsyncTask::DoWork()
{
	OldTime = FPlatformTime::Seconds();
	double Result = 0;
	for (int32 i = 0; i < TargetCounter; i++)
	{
		Result += FMath::Sqrt(i)/TargetCounter;
	}

	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait TargetCounterR(%f)"), __LINE__, Result);
	double End = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Log, TEXT(__FUNCTION__"@%u wait millisecond(%f) end."), __LINE__, (End-OldTime)*1000);
}
