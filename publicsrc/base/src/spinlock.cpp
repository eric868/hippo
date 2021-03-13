
#include "spinlock.h"
#include <assert.h> 
namespace base
{
	spinlock::spinlock(int spin_count/* = 4000*/)
	{
#ifdef _MSC_VER  
		//��תspin_count��ʱ�����ں��������
		InitializeCriticalSectionAndSpinCount(&cs_, spin_count);
#else  
		//PTHREAD_PROCESS_PRIVATE:
		//����ʼ�������������߳����ڵĽ����ڵ��̲߳��ܹ�ʹ�ø���������
		int rs = ::pthread_spin_init(&cs_, PTHREAD_PROCESS_PRIVATE);  
		assert(0 == rs);  
#endif  
	}

	spinlock::~spinlock()
	{
#ifdef _MSC_VER  
		DeleteCriticalSection(&cs_);
#else  
		int rs = ::pthread_spin_destroy(&cs_);  
		assert(0 == rs);  
#endif  
	}

	inline void spinlock::lock()
	{
#ifdef _MSC_VER
		EnterCriticalSection(&cs_);
		//assert(m_critical_section.RecursionCount == 1);
#else  
		int rs = ::pthread_spin_lock(&cs_);
		assert(0 == rs);
#endif  
	}

	inline bool spinlock::try_lock()
	{
#ifdef _MSC_VER 
		if (!TryEnterCriticalSection(&cs_)) { return false; }

		if (cs_.RecursionCount > 1) {
			LeaveCriticalSection(&cs_);
			throw ("Thread locked expcetion! LeaveCriticalSection");
		}
		return true;
#else  
		return 0 == ::pthread_spin_trylock(&cs_);
#endif  
	}

	inline void spinlock::unlock()
	{
#ifdef _MSC_VER
		//assert(m_critical_section.RecursionCount == 1);
		LeaveCriticalSection(&cs_);
#else  
		int rs = ::pthread_spin_unlock(&cs_);
		assert(0 == rs);
#endif  
	}

}
