#pragma once 

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <semaphore.h>
#endif

namespace base
{

//无名(内存)信号量，可以用于线程（多用于）/进程间同步（信号量要放在共享内存中） 
class semaphore 
{
public:
	semaphore(long init_count = 0, long max_count = 1);
	~semaphore();

	bool wait() const;
	bool try_wait() const;
	bool post(int count = 1) const;

private:
#ifdef _MSC_VER
	mutable HANDLE sem_;
#else
	mutable sem_t sem_;
#endif
};

}
