#pragma once 

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <semaphore.h>
#endif

namespace base
{

//����(�ڴ�)�ź��������������̣߳������ڣ�/���̼�ͬ�����ź���Ҫ���ڹ����ڴ��У� 
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
