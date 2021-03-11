#pragma once
#include <mutex>
#include "nocopyable.h"
#include "lock.h"

namespace base
{
	template <typename T>
	class singleton_lazy : public nocopyable
	{
	public:
		static T* instance()
		{
			if (instance_ == NULL)
			{
				mutex_scope locker(&mutex_);
				if (instance_ == NULL)
				{
					instance_ = new T();
				}
			}
			return instance_;
		}
	private:
		class deletor
		{
		public:
			~deletor()
			{
				if (singleton_lazy<T>::instance_ != NULL)
				{
					delete singleton_lazy<T>::instance_;
					singleton_lazy<T>::instance_ = NULL;
				}
			}
		};
		static deletor deletor_;
		static T* instance_;
		static mutex mutex_;
	};
	template<typename T>
	typename singleton_lazy<T>::deletor singleton_lazy<T>::deletor_;
	template<typename T>
	T* singleton_lazy<T>::instance_ = NULL;
	template<typename T>
	mutex singleton_lazy<T>::mutex_;

	///////////////////////////////////////////////////////////////////////////////
	//������main����֮ǰ��ʼ��������û���̰߳�ȫ�����⣬����Ǳ����������no-local static����
	//���������static�����ڲ�ͬ���뵥Ԫ�������Ϊcpp�ļ����������ͷ�ļ����еĳ�ʼ��˳����δ����ġ�
	template<typename T>
	class singleton_eager : public nocopyable
	{
	public:
		inline static T& instance()
		{
			return instance_;
		}

	private:
		static T instance_;
	};
	template<typename T>
	T singleton_eager<T>::instance_;


	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class singleton_once : public nocopyable
	{
	public:
		static inline T& instance()
		{
			std::call_once(flag_, std::bind(&singleton_once<T>::init));
			return *instance_;
		}

	private:
		static inline void init()
		{
			instance_.reset(new T());
		}

		static std::auto_ptr<T> instance_;
		static std::once_flag flag_;
	};

	template<typename T>
	std::auto_ptr<T> singleton_once<T>::instance_;
	template<typename T>
	std::once_flag singleton_once<T>::flag_;

	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class singleton_meyers : public nocopyable
	{
	public:
		static T& instance()
		{
			mutex_scope locker(&mutex_); // not needed after C++0x
			static T instance_;
			return instance_;
		}

	private:
		static mutex mutex_;
	};
	template <typename T>
	mutex singleton_meyers<T>::mutex_;
}
////////////////////////////////////////////////////////////////////////////////
//��Ҫ���졢��������
#define SINGLETON(class_type)\
public:\
    inline ~class_type(){}\
    static inline class_type& instance()\
{\
    return base::singleton_meyers<class_type>::instance(); \
}\
private:\
    friend class base::singleton_meyers<class_type>; \
    inline class_type(){}

//����Ҫ���졢��������
#define SINGLETON_UNINIT(class_type)\
public:\
    static inline class_type& instance()\
{\
    return base::singleton_meyers<class_type>::instance(); \
}\
private:\
    friend class base::singleton_meyers<class_type>;

////////////////////////////////////////////////////////////////////////////////
//��Ҫ���졢��������
#define SINGLETON_ONCE(class_type)\
public:\
    inline ~class_type(){}\
    static inline class_type& instance()\
{\
    return base::singleton_once<class_type>::instance(); \
}\
private:\
    friend class base::singleton_once<class_type>; \
    inline class_type(){}

//����Ҫ���졢��������
#define SINGLETON_ONCE_UNINIT(class_type)\
public:\
    static inline class_type& instance()\
{\
    return base::singleton_once<class_type>::instance(); \
}\
private:\
    friend class base::singleton_once<class_type>;


////////////////////////////////////////////////////////////////////////////////
#define SINGLETON_GET(class_type)\
    inline class_type& get_##class_type()\
{\
    return class_type::instance(); \
}


