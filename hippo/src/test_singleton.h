#pragma once
#include <iostream>
#include "synclog.h"



class TestSynclog
{
	SINGLETON_UNINIT(TestSynclog)
public:
	void test()
	{
		SYNC_LOG(base::synclog::LOG_INFO) << "hello synclog";
	}
};
SINGLETON_GET(TestSynclog)

class TestSingleton : public base::singleton_lazy<TestSingleton>
{
public:
	void test()
	{
		get_TestSynclog().test();
	}
};