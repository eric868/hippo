#pragma once
#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <pthread.h>
#endif
#include <assert.h>
#include "base.h"
/*
���������̻߳��sleep������������>running����������
�������������ĵ��л���cpu����ռ���źŵķ��͵ȿ�����
�����������ٽ�������ʱ��Ƚϳ��Ĳ���������������Щ��������Կ���
1 �ٽ�����IO����
2 �ٽ������븴�ӻ���ѭ������
3 �ٽ��������ǳ�����
4 ���˴�����
 * critical_section: not a kernal object(so it is faster than mutex/rwlock), can not synchronize multiple processes
 * mutex/rwlock: kernal object, can synchronize multiple processes
 */
namespace base {

class mutex
{
public:
	mutex();
	~mutex();

	void init();
	void exit();
	void acquire();
	int try_acquire();
	void release();
#ifdef _MSC_VER
	CRITICAL_SECTION* get_mutex() { return &cs_; }
#else
	pthread_mutex_t* get_mutex() { return &cs_; }
#endif

protected:
#if defined(_MSC_VER)
	CRITICAL_SECTION cs_;
#else
	pthread_mutex_t cs_;
	pthread_mutexattr_t cs_attr_;
#endif
	bool initialized_;
};

class mutex_scope
{
public:
	mutex_scope(mutex* m);
	~mutex_scope();

protected:
	mutex* mutex_;
};

/****************************************************************************/

class rwlock
{
public:
	rwlock();
	~rwlock();

public:
	void lock_read();
	void unlock_read();
	void lock_write();
	void unlock_write();

private:
	void init();
	void release();

private:
#if defined(_MSC_VER)
	LONG numWritersWaiting_;
	LONG numReadersWaiting_;

	// HIWORD is writer active flag;
	// LOWORD is readers active count;
	DWORD activeWriterReaders_;

	HANDLE hReadyToRead_;
	HANDLE hReadyToWrite_;
	CRITICAL_SECTION cs_;

	DWORD numReaderRacesLost_;

	DWORD numReaderWakeups_;
#else
	pthread_rwlock_t rwlock_;
#endif
};

class read_lock_scope
{
public:
	read_lock_scope(rwlock* lock)
		: rwlock_(lock) {
		assert(lock != NULL);
		rwlock_->lock_read();
	}
	~read_lock_scope() {
		rwlock_->unlock_read();
	}

private:
	rwlock* rwlock_;
};

class write_lock_scope
{
public:
	write_lock_scope(rwlock* lock)
		: rwlock_(lock) {
		assert(lock != NULL);
		rwlock_->lock_write();
	}
	~write_lock_scope() {
		rwlock_->unlock_write();
	}

private:
	rwlock* rwlock_;
};

} // end of namespace base
