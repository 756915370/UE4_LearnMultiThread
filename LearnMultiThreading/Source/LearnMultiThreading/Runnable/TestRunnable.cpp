#include "TestRunnable.h"
#include "TestRunnableActor.h"

FCriticalSection FTestRunnable::CriticalSection;

bool FTestRunnable::Init()
{
	UE_LOG(LogTemp, Log, TEXT("%s初始化"), *MyThreadName);
	return IsValid(Tester);
}

uint32 FTestRunnable::Run()
{
	while (IsValid(Tester))
	{
#if true // thread sync 线程同步
		FScopeLock Lock(&CriticalSection);
#endif
		if (Tester->TestCount < Tester->TestTarget)
		{
			Tester->TestCount++;
			WorkCount++;
			if (WorkCount % 100 == 0)
				UE_LOG(LogTemp, Log, TEXT("%s %d"), *MyThreadName, WorkCount);
		}
		else
		{
			break;
		}
	}
	return 0;
}

void FTestRunnable::Exit()
{
	UE_LOG(LogTemp, Log, TEXT("%s执行了%d次"), *MyThreadName, WorkCount);
}
