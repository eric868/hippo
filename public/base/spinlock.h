#pragma once
//�����������ĺ��ٵ���Դ��������,����̱߳�����ʱ,
//���ͻ�һֱ�ظ���鿴���Ƿ�����ˣ�
//Ҳ����˵�����������ڵȴ�״̬ʱ����һֱ����CPUʱ�䡣
//����������Ҫ�����ٽ�������ʱ��ǳ�����CPU��Դ�����ŵ�����¡�
 
#ifdef _MSC_VER
#include <Windows.h>  
#else  
#include <pthread.h>  
#endif  

namespace base
{

//�������ظ���
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
