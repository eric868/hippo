#pragma once
#include "thread.h"
#include "event.h"
#include "state.h"
#include "tsemaphore.h"
#include <iostream>

class TestThread
{
public:
	void test()
	{
		thread_.create((base::thread::thread_proc_t)thread_func, this);
		base::thread::sleep(10000);
		semaphore_.post();
		thread_.join();
	}

protected:
	static void thread_func(void* value)
	{
		while (1)
		{
			std::cout << "this thread func" << std::endl;
			TestThread* tt = (TestThread*)value;
			tt->semaphore_.wait();
			std::cout << "this thread func break" << std::endl;
			break;
		}
	}

private:
	base::thread thread_;
	base::event event_;
	base::state state_;
	base::semaphore semaphore_;
};