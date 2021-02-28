#pragma once
#include "thread.h"
#include <iostream>

class TestThread
{
public:
	void test()
	{
		std::cout << base::thread::curr_thread_id() << std::endl;
	}
};