#pragma once

/*
 *当线程池被销毁的时候，会调用Abandon函数
 *继承FNonAbandonableTask的话这个时候就不会丢弃而且等待执行完
*/
class FTestAsyncTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FTestAsyncTask>;
	int32 TargetCounter;

	double OldTime = 0;

	FTestAsyncTask(int32 Target): TargetCounter(Target)
	{
	}

	void DoWork();
	
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MyAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};
