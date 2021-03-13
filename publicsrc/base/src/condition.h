#pragma once
#include <assert.h> 
#if defined WIN32
#include <windows.h>  
#else  
#include <pthread.h>  
#endif  
#include "lock.h"

namespace base
{

class condition
{
public:
    condition();
    virtual ~condition();

    bool signal();
    bool broadcast();

    //release lock, wait for signal or interrupt, lock and wake  
	bool wait(mutex *mutex);
	bool wait_time(mutex *mutex, unsigned s, unsigned ms = 0);
private:
#if defined WIN32
	CONDITION_VARIABLE m_cond;
#else
	pthread_cond_t m_cond;
#endif
};
}
