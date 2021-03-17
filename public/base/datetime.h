#pragma once
#include <string>

#ifdef _MSC_VER
#include <windows.h>
#include <time.h>
#else
#include <sys/time.h>
#endif

namespace base
{
struct date
{
	int year;
	int month;
	int day;

	date();
	date(int y, int m, int d);
	date(const date& date);
	date& operator=(const date& date);

	bool operator==(const date& date) const;
	bool operator>(const date& date) const;
	bool operator<(const date& date) const;
	bool operator<=(const date& date) const;
	bool operator>=(const date& date) const;
	bool operator!=(const date& date) const;

	//format 0:YYYYMMDD 1:YYYY-MM-DD 2:YYYY/MM/DD
	date& setvalue(const std::string& str, int format = 1)
	{
		if (format == 0)
			sscanf(str.c_str(), "%4d%2d%2d", &year, &month, &day);
		else if (format == 1)
			sscanf(str.c_str(), "%4d-%2d-%2d", &year, &month, &day);
		else
			sscanf(str.c_str(), "%4d/%2d/%2d", &year, &month, &day);

		return *this;
	}
	//format 0:YYYYMMDD 1:YYYY-MM-DD 2:YYYY/MM/DD
	std::string str(int format = 1) const
	{
		char buf[32] = { 0 };
		if (format == 0)
			sprintf(buf, "%04d%02d%02d", year, month, day);
		else if (format == 1)
			sprintf(buf, "%04d-%02d-%02d", year, month, day);
		else
			sprintf(buf, "%04d/%02d/%02d", year, month, day);

		return std::string(buf);
	}

	date& now();
};

struct time
{
	int hour;
	int minute;
	int second;
	int millisecond;

	time();
	time(int h, int m, int s, int ms = 0);
	time(const time& t);
	time& operator=(const time& t);

	bool operator==(const time& t) const;
	bool operator>(const time& t) const;
	bool operator<(const time& t) const;
	bool operator<=(const time& t) const;
	bool operator>=(const time& t) const;
	bool operator!=(const time& t) const;

	//format 1:hh:mm:ss 2:hh:mm:ss.ms
	time& setvalue(const std::string& str, int format = 1)
	{
		if (format == 1)
			sscanf(str.c_str(), "%d:%d:%d", &hour, &minute, &second);
		else
			sscanf(str.c_str(), "%d:%d:%d.%d", &hour, &minute, &second, &millisecond);

		return *this;
	}

	//format 1:hh:mm:ss 2:hh:mm:ss.ms
	std::string str(int format = 1) const
	{
		char buf[32] = { 0 };
		if (format == 1)
			sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
		else
			sprintf(buf, "%02d:%02d:%02d.%03d", hour, minute, second, millisecond);

		return std::string(buf);
	}

	time& now();

	friend time operator+(const time& t1, const time& t2)
	{
		long t1_milsecs = ((t1.hour * 60 + t1.minute) * 60 + t1.second) * 1000 + t1.millisecond;
		long t2_milsecs = ((t2.hour * 60 + t2.minute) * 60 + t2.second) * 1000 + t2.millisecond;
		long ret_milsecs = t1_milsecs + t2_milsecs;
		int ret_hour = ret_milsecs / (60 * 60 * 1000);
		int ret_min = (ret_milsecs % (60 * 60 * 1000)) / (60 * 1000);
		int ret_sec = (ret_milsecs % (60 * 1000)) / 1000;
		int ret_milsec = ret_milsecs % 1000;

		return time(ret_hour, ret_min, ret_sec, ret_milsec);
	}

	friend time operator-(const time& t1, const time& t2)
	{
		long t1_milsecs = ((t1.hour * 60 + t1.minute) * 60 + t1.second) * 1000 + t1.millisecond;
		long t2_milsecs = ((t2.hour * 60 + t2.minute) * 60 + t2.second) * 1000 + t2.millisecond;
		long ret_milsecs = t1_milsecs - t2_milsecs;
		int ret_hour = ret_milsecs / (60 * 60 * 1000);
		int ret_min = (ret_milsecs % (60 * 60 * 1000)) / (60 * 1000);
		int ret_sec = (ret_milsecs % (60 * 1000)) / 1000;
		int ret_milsec = ret_milsecs % 1000;

		return time(ret_hour, ret_min, ret_sec, ret_milsec);
	}
};

struct datetime
{
	date m_date;
	time m_time;

	datetime() {}
	datetime(const date& d, const time& t) : m_date(d), m_time(t) {}
	datetime(const datetime& other) : m_date(other.m_date), m_time(other.m_time) {}
	datetime(const time_t& t)
	{
		struct tm p = { 0 };
#ifdef _MSC_VER
		localtime_s(&p, &t);
#else
		localtime_r(&t, &p);
#endif
		m_date = date(p.tm_year + 1900, p.tm_mon + 1, p.tm_mday);
		m_time = time(p.tm_hour, p.tm_min, p.tm_sec);
	}
	datetime& operator=(const datetime& other)
	{
		if (this != &other)
		{
			m_date = other.m_date;
			m_time = other.m_time;
		}

		return *this;
	}

	bool operator==(const datetime& other) const
	{
		if(m_date == other.m_date && m_time == other.m_time)
		{ return true; }

		return false;
	}

	bool operator>(const datetime& other) const
	{
		if(m_date > other.m_date || (m_date == other.m_date && m_time > other.m_time))
		{ return true; }

		return false;
	}

	bool operator<(const datetime& other) const
	{
		if(m_date < other.m_date || (m_date == other.m_date && m_time < other.m_time))
		{ return true; }

		return false;
	}

	bool operator!=(const datetime& other) const
	{
		return !(*this == other);
	}

	bool operator>=(const datetime& other) const
	{
		return !(*this < other);
	}

	bool operator<=(const datetime& other) const
	{
		return !(*this > other);
	}

	friend datetime operator+(const datetime& t1, const time& t2)
	{
		time t3 = t1.m_time + t2;
		return datetime(t1.m_date, t3);
	}

	friend datetime operator+(const time& t1, const datetime& t2)
	{
		return t2 + t1;
	}

	friend datetime operator-(const datetime& t1, const time& t2)
	{
		time t3 = t1.m_time - t2;
		return datetime(t1.m_date, t3);
	}

	time_t gettimestamp() const
	{
		tm p;
		p.tm_year = m_date.year - 1900;
		p.tm_mon = m_date.month - 1;
		p.tm_mday = m_date.day;
		p.tm_hour = m_time.hour;
		p.tm_min = m_time.minute;
		p.tm_sec = m_time.second;

		return mktime(&p);
	}

	datetime operator+(int second) const
	{
		time_t t = gettimestamp() + (time_t)second;
		return datetime(t);
	}

	datetime& operator+=(int second)
	{
		*this = *this + second;
		return *this;
	}

	datetime operator-(int second) const
	{
		time_t t = gettimestamp() - (time_t)second;
		return datetime(t);
	}

	datetime& operator-=(int second)
	{
		*this = *this - second;
		return *this;
	}

	//format 0:YYYYMMDD hh:mm:ss 1:YYYY-MM-DD hh:mm:ss 2:YYYY/MM/DD hh:mm:ss 3:YYYY-MM-DD hh:mm:ss.ms
	datetime& setvalue(const std::string& str, int format = 1)
	{
		if (format == 0)
			sscanf(str.c_str(), "%4d%2d%2d %d:%d:%d", &m_date.year, &m_date.month, &m_date.day, &m_time.hour, &m_time.minute, &m_time.second);
		else if (format == 1)
			sscanf(str.c_str(), "%4d-%2d-%2d %d:%d:%d", &m_date.year, &m_date.month, &m_date.day, &m_time.hour, &m_time.minute, &m_time.second);
		else if (format == 2)
			sscanf(str.c_str(), "%4d/%2d/%2d %d:%d:%d", &m_date.year, &m_date.month, &m_date.day, &m_time.hour, &m_time.minute, &m_time.second);
		else
			sscanf(str.c_str(), "%4d-%2d-%2d %d:%d:%d.%d", &m_date.year, &m_date.month, &m_date.day, &m_time.hour, &m_time.minute, &m_time.second, &m_time.millisecond);

		return *this;
	}

	//format 0:YYYYMMDD hh:mm:ss 1:YYYY-MM-DD hh:mm:ss 2:YYYY/MM/DD hh:mm:ss 3:YYYY-MM-DD hh:mm:ss.ms
	std::string str(int format = 1) const
	{
		char buf[64] = { 0 };
		if (format == 0)
			sprintf(buf, "%04d%02d%02d %02d:%02d:%02d", m_date.year, m_date.month, m_date.day, m_time.hour, m_time.minute, m_time.second);
		else if (format == 1)
			sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", m_date.year, m_date.month, m_date.day, m_time.hour, m_time.minute, m_time.second);
		else if (format == 2)
			sprintf(buf, "%04d/%02d/%02d %02d:%02d:%02d", m_date.year, m_date.month, m_date.day, m_time.hour, m_time.minute, m_time.second);
		else
			sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d.%03d", m_date.year, m_date.month, m_date.day, m_time.hour, m_time.minute, m_time.second, m_time.millisecond);

		return std::string(buf);
	}

	datetime& now();
};
}
