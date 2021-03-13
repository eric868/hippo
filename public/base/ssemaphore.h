#pragma once

#include <string>
#ifdef _MSC_VER
#include <Windows.h>
#else
#include <semaphore.h>
#endif

namespace base
{
	//有名信号量，可以用于进程（多用于）/线程间同步 
	class ssemaphore
	{
	public:
		ssemaphore(long initial = 0, const char *sem_name = NULL);
#ifdef _MSC_VER
		bool wait(int millisecond = INFINITE);
		bool post(int counter = 1);
#else
		bool wait(int millisecond = -1);
		bool post();
#endif
		bool try_wait();
		~ssemaphore();
	private:

#ifdef _MSC_VER
		HANDLE sem_;
#else
		sem_t* sem_;
		std::string sem_name_;
#endif

	};
}
