#pragma once
//自旋锁：消耗很少的资源来建立锁,随后当线程被阻塞时,
//它就会一直重复检查看锁是否可用了，
//也就是说当自旋锁处于等待状态时它会一直消耗CPU时间。
//自旋锁就主要用在临界区持锁时间非常短且CPU资源不紧张的情况下。
 
#ifdef _MSC_VER
#include <Windows.h>  
#else  
#include <pthread.h>  
#endif  

namespace base
{

//不允许重复锁
class spinlock  
{  
public:  
	spinlock(int spin_count = 4000);
	virtual ~spinlock();

#ifdef _MSC_VER
	CRITICAL_SECTION* get_spinlock() { return &cs_; }
#else  
	pthread_spinlock_t* get_spinlock() { return &cs_; }
#endif  

	void lock();
	bool try_lock();
	void unlock(); 
private:
#ifdef _MSC_VER
	CRITICAL_SECTION cs_;
#else  
	pthread_spinlock_t cs_;
#endif  
};



class spinlock_scope
{
public:
	spinlock_scope(spinlock* sl)
		: spinlock_(sl)
	{
		spinlock_->lock();
	}

	virtual ~spinlock_scope()
	{
		spinlock_->unlock();
	}

private:
	spinlock* spinlock_;
};

}
