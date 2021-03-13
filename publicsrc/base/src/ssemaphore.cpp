#include "ssemaphore.h"
#include <fcntl.h>           /* 为了 O_* 常量 */
namespace base
{
	ssemaphore::ssemaphore(long initial/* = 0 */, const char *sem_name/*=NULL*/)
	{
#ifdef _MSC_VER
		sem_=CreateSemaphore(0,initial,0x7fffffff,0);
		if(sem_==NULL) {
			sem_=INVALID_HANDLE_VALUE;
		}
#else
		if(sem_name) {
			sem_name_=sem_name;
		}
		sem_=sem_open(sem_name, O_CREAT, 0644, initial);
#endif
	}

#ifdef _MSC_VER
	bool ssemaphore::wait(int millisecond)
	{
		if(INVALID_HANDLE_VALUE == sem_) {
			return false;
		}
		return WAIT_OBJECT_0==WaitForSingleObject(sem_,millisecond);
	}

	bool ssemaphore::post(int counter)
	{
		if (INVALID_HANDLE_VALUE == sem_) {
			return false;
		}
		return ReleaseSemaphore(sem_, counter, NULL) == TRUE;
	}
#else
	bool ssemaphore::wait(int millisecond)
	{
		if(-1 == millisecond) {
			return 0==sem_wait(sem_);
		} else {
			struct timespec ts;
			ts.tv_sec= millisecond / 1000;
			ts.tv_nsec=(millisecond % 1000) * 1000000L;

			/* Try to lock SSemaphore */
			return 0 == sem_timedwait(sem_, &ts);
		}
	}

	bool ssemaphore::post()
	{
		return sem_post(sem_) == 0;
	}
#endif

	bool ssemaphore::try_wait()
	{
#ifdef _MSC_VER
		if(INVALID_HANDLE_VALUE==sem_) {
			return false;
		}
		if(WAIT_OBJECT_0==WaitForSingleObject(sem_,0)) {
			return true;
		} else {
			return false;
		}
#else	
		if(NULL==sem_) {
			return false;
		}
		if(sem_trywait(sem_)==0) {
			return true;
		} else {
			return false;
		}
#endif
	}

	ssemaphore::~ssemaphore()
	{
#ifdef _MSC_VER
		if(INVALID_HANDLE_VALUE != sem_) {
			CloseHandle(sem_);
		}			
#else	
		sem_close(sem_);
		sem_unlink(sem_name_.c_str());
#endif
	}
}
