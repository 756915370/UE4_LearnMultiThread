#pragma once

class FTestRunnable : public FRunnable
{
public:
	FTestRunnable(FString ThreadName, class ATestRunnableActor* TestActor): MyThreadName(ThreadName),
																			Tester(TestActor)
	{
	}

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	FString MyThreadName;
	class ATestRunnableActor* Tester;
private:
	int32 WorkCount = 0;

	//线程临界区，用于线程加锁
	static FCriticalSection CriticalSection;
};
