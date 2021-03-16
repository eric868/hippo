#include "datetime.h"

namespace base
{

	date::date() : year(1900), month(1), day(1)
	{

	}

	date::date(int y, int m, int d) : year(y), month(m), day(d)
	{

	}

	date::date(const date& date) : year(date.year), month(date.month), day(date.day)
	{

	}

	date& date::operator=(const date& date)
	{
		if (this != &date)
		{
			year = date.year;
			month = date.month;
			day = date.day;
		}

		return *this;
	}

	bool date::operator==(const date& date) const
	{
		if (year == date.year && month == date.month && day == date.day)
		{
			return true;
		}

		return false;
	}

	bool date::operator>(const date& date) const
	{
		if (year > date.year || (year == date.year && month > date.month) || (year == date.year && month == date.month && day > date.day))
		{
			return true;
		}

		return false;
	}

	bool date::operator<(const date& date) const
	{
		if (year < date.year || (year == date.year && month < date.month) || (year == date.year && month == date.month && day < date.day))
		{
			return true;
		}

		return false;
	}

	bool date::operator<=(const date& date) const
	{
		return !(*this > date);
	}

	bool date::operator>=(const date& date) const
	{
		return !(*this < date);
	}

	bool date::operator!=(const date& date) const
	{
		return !(*this == date);
	}

	date& date::now()
	{
		time_t t;
		::time(&t);
		tm p;
#ifdef _MSC_VER
		localtime_s(&p, &t);
#else
		localtime_r(&t, &p);
#endif
		year = p.tm_year + 1900;
		month = p.tm_mon + 1;
		day = p.tm_mday;

		return *this;
	}

	time::time() : hour(0), minute(0), second(0), millisecond(0)
	{

	}

	time::time(int h, int m, int s, int ms /*= 0*/) : hour(h), minute(m), second(s), millisecond(ms)
	{

	}

	time::time(const time& t) : hour(t.hour), minute(t.minute), second(t.second), millisecond(t.millisecond)
	{

	}

	time& time::operator=(const time& t)
	{
		if (this != &t)
		{
			hour = t.hour;
			minute = t.minute;
			second = t.second;
			millisecond = t.millisecond;
		}

		return *this;
	}

	bool time::operator==(const time& t) const
	{
		if (hour == t.hour && minute == t.minute && second == t.second && millisecond == t.millisecond)
		{
			return true;
		}

		return false;
	}

	bool time::operator>(const time& t) const
	{
		if (hour > t.hour ||
			(hour == t.hour && minute > t.minute) ||
			(hour == t.hour && minute == t.minute && second > t.second) ||
			(hour == t.hour && minute == t.minute && second == t.second && millisecond > t.millisecond))
		{
			return true;
		}

		return false;
	}

	bool time::operator<(const time& t) const
	{
		if (hour < t.hour ||
			(hour == t.hour && minute < t.minute) ||
			(hour == t.hour && minute == t.minute && second < t.second) ||
			(hour == t.hour && minute == t.minute && second == t.second && millisecond < t.millisecond))
		{
			return true;
		}

		return false;
	}

	bool time::operator<=(const time& t) const
	{
		return !(*this > t);
	}

	bool time::operator>=(const time& t) const
	{
		return !(*this < t);
	}

	bool time::operator!=(const time& t) const
	{
		return !(*this == t);
	}

	time& time::now()
	{
#ifdef _MSC_VER
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		hour = sys.wHour;
		minute = sys.wMinute;
		second = sys.wSecond;
		millisecond = sys.wMilliseconds;
#else
		struct timeval t;
		gettimeofday(&t, NULL);
		struct tm p = { 0 };
		localtime_r(&t.tv_sec, &p);
		hour = p.tm_hour;
		minute = p.tm_min;
		second = p.tm_sec;
		millisecond = t.tv_usec / 1000;
#endif
		return *this;
	}

	datetime& datetime::now()
	{
#ifdef WIN32
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		m_date = date(sys.wYear, sys.wMonth, sys.wDay);
		m_time = time(sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#else
		struct timeval t;
		gettimeofday(&t, NULL);
		struct tm p = { 0 };
		localtime_r(&t.tv_sec, &p);
		m_date = date(p.tm_year + 1900, p.tm_mon + 1, p.tm_mday);
		m_time = time(p.tm_hour, p.tm_min, p.tm_sec, t.tv_usec / 1000);
#endif
		return *this;
	}

}

