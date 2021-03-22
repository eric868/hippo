#pragma once

#include <string.h>
#include <limits>
#include <exception>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <memory>
#include <sstream>

#define EPSILON				1e-10
#define DOUBLE_INVALID		1e50
#define DOUBLE_VALID_MAX	1e20
#define DOUBLE_VALID_MIN	-1e20
#define INT_INVALID			0xFFFFFFFF
#define INT_VALID_MIN		-1e10
#define INT_VALID_MAX		1e10

namespace common
{
    template<size_t N>
    inline void strcpy_x(char(&dest)[N], const char *src)
    {
#ifdef WIN32
        strncpy_s(dest, src, N - 1);
#else
        strncpy(dest, src, N - 1);
#endif
    }
    template<size_t N>
    inline void strcpy_x(char(&dest)[N], const std::string& src)
    {
#ifdef WIN32
        strncpy_s(dest, src.c_str(), N - 1);
#else
        strncpy(dest, src.c_str(), N - 1);
#endif
    }

    template <int v> struct Int2Type {enum { value = v };};

    template<typename Source>
    std::string to_str(const Source &v)
    {
        std::stringstream s;
        s << v;
        return s.str();
    }

    template<>
    inline std::string to_str(const std::string &v)
    {
        return v;
    }

    template<typename Target>
    Target my_cast(const std::string &str)
    {
        std::stringstream s(str);
        Target val;
        return (s >> val).fail()?Target():val;
    }

    template<typename Target>
    inline Target my_cast(const char * v)
    {
        return v?my_cast<Target>(std::string(v)):Target();
    }

    template<>
    inline std::string my_cast(const std::string &str)
    {
        return str;
    }

    template<class T>
    void assignment(T& target, T& source)
    {
        target = source;
    }


    template<class T, size_t N>
    void assignment(T(& target)[N], T(& source)[N])
    {
        for(size_t i = 0; i < N; i++)
        {
            assignment(target[i], source[i]);
        }
    }

    template<class T>
    void assignDefault(T& target)
    {
        target = T();
    }


    template<class T, size_t N>
    void assignDefault(T(& target)[N])
    {
        for(size_t i = 0; i < N; i++)
        {
            assignDefault(target[i]);
        }
    }

	template<typename FundamentalTypes, class T>
	class DataTypeBase
	{
	public:
		typedef FundamentalTypes fund_type;

		fund_type m_Value;

		DataTypeBase()
			: m_Value(fund_type())
		{
		}

		inline FundamentalTypes GetValue() const
		{
			return m_Value;
		}

		inline const T & SetValue(const fund_type Value)
		{
			m_Value = Value;
			return *static_cast<T*>(this);
		}
		inline const T & SetValue(const T ov)
		{
			m_Value = ov.GetValue();
			return *static_cast<T*>(this);
		}

		inline bool operator < (const T & ov) const
		{
			return m_Value < ov.m_Value;
		}
		inline bool operator <= (const T & ov) const
		{
			return m_Value <= ov.m_Value;
		}

		inline bool operator > (const T & ov) const
		{
			return m_Value > ov.m_Value;
		}
		inline bool operator >= (const T & ov) const
		{
			return m_Value >= ov.m_Value;
		}

		inline bool operator == (const T & ov) const
		{
			return m_Value == ov.m_Value;
		}

		inline bool operator != (const T & ov) const
		{
			return m_Value != ov.m_Value;
		}

		inline T operator + (const T & ov) const
		{
			T tval;
			return tval.SetValue(m_Value + ov.m_Value);
		}

		inline T operator - (const T & ov) const
		{
			T tval;
			return tval.SetValue(m_Value - ov.m_Value);
		}

		inline T operator += (const T & ov)
		{
			return static_cast<T*>(this)->SetValue(m_Value + ov.m_Value);
		}
		inline T operator -= (const T & ov)
		{
			return static_cast<T*>(this)->SetValue(m_Value - ov.m_Value);
		}
		inline T operator -- ()
		{
			return static_cast<T*>(this)->SetValue(m_Value--);
		}
		std::string GetText() const
		{
			return to_str(m_Value);
		}

		bool SetText(const std::string &str)
		{
			m_Value = my_cast<FundamentalTypes>(str);
			return true;
		}
		inline std::string ValueToString() const
		{
			return to_str(m_Value);
		}

		inline T& ValueFromString(const std::string &str)
		{
			m_Value = my_cast<fund_type>(str);
			return *static_cast<T*>(this);
		}
	};

	template<class T>
	class DataTypeDecimal : public DataTypeBase<double, T>
	{
	public:
	    // using DataTypeBase<double, T>::m_Value;
	    // using DataTypeBase<double, T>::SetValue;
		DataTypeDecimal()
		{
			SetZero();
		}
		bool IsValid() const
		{
			return (this->m_Value > DOUBLE_VALID_MIN && this->m_Value < DOUBLE_VALID_MAX);
		}
		inline T operator + (const T & ov) const
		{
			T tval = *static_cast<const T*>(this);
			if (IsValid() && ov.IsValid())
			{
				return tval.SetValue(this->m_Value + ov.m_Value);
			}else{
				return tval.SetInvalid();
			}
		}
		inline T operator - (const T & ov) const
		{
			T tval = *static_cast<const T*>(this);
			if (IsValid() && ov.IsValid())
			{
				return tval.SetValue(this->m_Value - ov.m_Value);
			}else{
				return tval.SetInvalid();
			}
		}
		inline T operator += (const T & ov)

		{
			if (IsValid() && ov.IsValid())
			{
				return static_cast<T*>(this)->SetValue(this->m_Value + ov.m_Value);
			}else{
				return static_cast<T*>(this)->SetInvalid();
			}
		}
		inline T operator -= (const T & ov)
		{
			if (IsValid() && ov.IsValid())
			{
				return static_cast<T*>(this)->SetValue(this->m_Value - ov.m_Value);
			}else{
				return static_cast<T*>(this)->SetInvalid();
			}
		}
		bool operator == (const T & ov) const
		{
			double x = this->m_Value - ov.m_Value;
			return (x > -0.000001 && x < 0.000001);
		}
		bool operator < (const T & ov) const
		{
			double x = this->m_Value - ov.m_Value;
			return x < -0.000001;
		}
		bool operator > (const T & ov) const
		{
			double x = this->m_Value - ov.m_Value;
			return x > 0.000001;
		}
		inline bool operator != (const T & ov) const
		{
			return !(*this==ov);
		}
		T& SetInvalid()
		{
			this->m_Value = DOUBLE_INVALID;
			return *static_cast<T*>(this);
		}
		bool IsZero() const
		{
			return (this->m_Value > -0.000001 && this->m_Value < 0.000001);
		}
		inline const T & SetZero()
		{
			return this->SetValue(0);
		}
	};

	template<class T, int STR_LENGTH = 0>
	class DataTypeString
    {
	public:

		enum {STRLENGTH = STR_LENGTH, STRBUFSIZE = STR_LENGTH + 1};

		typedef char fund_type[STRBUFSIZE];

		fund_type m_Value;

		DataTypeString()
		{
			memset(&this->m_Value, 0, sizeof(this->m_Value));
		}

		std::string GetValue() const
		{
			return this->m_Value;
		}

		const T & SetValue(const fund_type &Value)
		{
			strcpy_x(this->m_Value, Value);
			return *static_cast<T*>(this);
		}

		const T & SetValue(const std::string &Value)
		{
			strcpy_x(this->m_Value, Value.c_str());
			return *static_cast<T*>(this);
		}

		const char * c_str() const
		{
			return this->m_Value;
		}

		inline bool empty() const
		{
			return 0 == this->m_Value[0];
		}

		size_t length() const
		{
			return strlen(this->m_Value);
		}

		size_t find(char c) const
		{
			for (size_t i = 0; i < STRBUFSIZE; i++)
			{
				if ('\0' == this->m_Value[i]) break;
				if (c == this->m_Value[i]) return i;
			}
			return std::string::npos;
		}

		inline bool operator < (const T & ov) const
		{
			return strcmp(this->m_Value, ov.m_Value) < 0;
		}
		inline bool operator > (const T & ov) const
		{
			return strcmp(this->m_Value, ov.m_Value) > 0;
		}
		inline bool operator <= (const T & ov) const
		{
			return !operator >(ov);
		}
		inline bool operator >= (const T & ov) const
		{
			return !operator <(ov);
		}
		inline bool operator == (const T & ov) const
		{
			return strcmp(this->m_Value, ov.m_Value) == 0;
		}
		inline bool operator != (const T & ov) const
		{
			return !operator ==(ov);
		}

		std::string ltrim() const
		{
			int i = 0;
			while (this->m_Value[i] == ' ' && i < STRLENGTH) ++i;
			return &this->m_Value[i];
		}
		std::string GetText() const
		{
			return this->m_Value;
		}

		bool SetText(const std::string &str)
		{
			strcpy_x(this->m_Value, str.c_str());
			return true;
		}

		inline std::string ValueToString() const
		{
			return this->m_Value;
		}

		inline T& ValueFromString(const std::string &str)
		{
			strcpy_x(this->m_Value, str.c_str());
			return *static_cast<T*>(this);
		}

	};

	template<class T>
	class DataTypeString<T, 0> : public DataTypeBase<std::string, T>
	{
	public:
		//  using DataTypeBase<std::string, T>::m_Value;
		const T & SetValue(const std::string &Value)
		{
			this->m_Value = Value;
			return *static_cast<T*>(this);
		}

		const std::string & GetValue() const
		{
			return this->m_Value;
		}

		const char * c_str() const
		{
			return this->m_Value.c_str();
		}

		inline bool empty() const
		{
			return this->m_Value.empty();
		}
	};

	template<class T>
	class DataTypeUint : public DataTypeBase<unsigned int, T>
	{
	public:
	    // using DataTypeBase<unsigned int, T>::m_Value;
		DataTypeUint()
		{
			SetInvalid();
		}
		inline T& operator ++ ()
		{
			++this->m_Value;
			return *static_cast<T*>(this);
		}
		inline T operator ++ (int)
		{
			T t = *static_cast<T*>(this);
			this->m_Value++;
			return t;
		}
		inline bool IsValid() const
		{
			return this->m_Value != (std::numeric_limits<unsigned int>::max)();
		}
		inline void SetInvalid()
		{
			this->m_Value = (std::numeric_limits<unsigned int>::max)();
		}
	};
	template<class T>
	class DataTypeInt : public DataTypeBase<int, T>
	{
	public:
	    // using DataTypeBase<int, T>::m_Value;
	    // using DataTypeBase<int, T>::SetValue;
		bool IsZero() const
		{
			return (this->m_Value == 0);
		}
		inline const T & SetZero()
		{
			return this->SetValue(0);
		}
		T& SetInvalid()
		{
			this->m_Value = static_cast<int>(INT_INVALID);
			return *static_cast<T*>(this);
		}
		bool IsValid() const
		{
			return (this->m_Value > INT_VALID_MIN && this->m_Value < INT_VALID_MAX);
		}
	};

	template<class T>
	class DataTypeDouble : public DataTypeBase<double, T>
	{
	public:
	    // using DataTypeBase<double, T>::m_Value;
		bool IsValid() const
		{
			return (this->m_Value > DOUBLE_VALID_MIN && this->m_Value < DOUBLE_VALID_MAX);
		}
		T& SetInvalid()
		{
			this->m_Value = DOUBLE_INVALID;
			return *static_cast<T*>(this);
		}
		bool IsZero() const
		{
			return (this->m_Value > -EPSILON && this->m_Value < EPSILON);
		}
	};

	template<class T>
	class DataTypeBool : public DataTypeBase<int, T>
	{
	public:
	    // using DataTypeBase<int, T>::m_Value;
		operator bool& ()
		{
			return this->m_Value;
		}

		bool IsTrue() const
		{
			return this->m_Value != 0;
		}

		bool IsFalse() const
		{
			return this->m_Value == 0;
		}
		T& SetTrue()
		{
			this->m_Value = 1;
			return *static_cast<T*>(this);
		}
		T& SetFalse()
		{
			this->m_Value = 0;
			return *static_cast<T*>(this);
		}
		std::string GetText() const
		{
			return IsTrue()?"1":"0";
		}
		bool SetText(const std::string &str)
		{
			this->m_Value = my_cast<int>(str);
			return true;
		}
		T GetNegative() const
		{
			return T().SetValue(!this->m_Value);
		}
	};
}
