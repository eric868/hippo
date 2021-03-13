
#include "tsemaphore.h"
namespace base
{
semaphore::semaphore(long init_count, long max_count)
{
#ifdef _MSC_VER
	sem_ = CreateSemaphore(0, init_count, max_count, 0);
#else
	//第二个参数为0,则在同一个线程间共享
	sem_init(&sem_, 0 , init_count);
#endif
}

semaphore::~semaphore()
{
#ifdef _MSC_VER
	CloseHandle(sem_);
#else
	sem_destroy(&sem_);
#endif
}

bool semaphore::wait() const
{
#ifdef _MSC_VER
	int rc = WaitForSingleObject(sem_, INFINITE);
	if (rc != WAIT_OBJECT_0) {
		return false;
	}
#else
	sem_wait(&sem_);
#endif

	return true;
}

bool semaphore::try_wait() const
{
#ifdef _MSC_VER
	return (WaitForSingleObject(sem_, 1) != WAIT_TIMEOUT);
#else
	return (sem_trywait(&sem_) == 0);
#endif
}

//用于以原子操作的方式将信号量的值加1
bool semaphore::post(int count/* = 1 */) const
{
#ifdef _MSC_VER    
	ReleaseSemaphore(sem_, count, 0);
#else
	sem_post(&sem_);
#endif

	return true;
}

}
