#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#ifdef _MSC_VER
#include <process.h>
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/unistd.h>
#endif
#include "synclog.h"

namespace base 
{
	static const char* LOG_LEVEL_STR[] = {
		"NULL",
		"[TRACE]",
		"[DEBUG]",
		"[INFO]",
		"[WARNING]",
		"[ERROR]",
		"[CRITICAL]"
	};

	bool synclog::iscout_ = true;
	int synclog::level_ = synclog::LOG_DEBUG;
	mutex synclog::mutex_;
	void synclog::set_level(unsigned int level)
	{
		level_ = level;
	}

	std::string synclog::localdatetimestr()
	{
		char buf[64] = { 0 };
#ifdef _MSC_VER
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d.%03d",
			sys.wYear, sys.wMonth, sys.wDay,
			sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#else
		struct timeval t;
		gettimeofday(&t, NULL);
		struct tm ti = {0};
		localtime_r(&t.tv_sec, &ti);
		sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d.%03ld",
			ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday,
			ti.tm_hour, ti.tm_min, ti.tm_sec,
			t.tv_usec / 1000);
#endif
		return buf;
	}

	std::string synclog::localdatestr()
	{
		char buf[32] = { 0 };
#ifdef _MSC_VER
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		sprintf(buf, "%4d%02d%02d", sys.wYear, sys.wMonth, sys.wDay);
#else
		time_t t;
		time(&t);
		struct tm ti = { 0 };
		localtime_r(&t, &ti);
		sprintf(buf, "%4d%02d%02d", ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday);
#endif
		return buf;
	}

	void synclog::mkdir(const std::string& dir)
	{
#ifdef _MSC_VER
		_mkdir(dir.c_str());
#else
		::mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
#endif
	}

	void synclog::log(level elevel, const std::string& fileline, const std::string& msg)
	{
		mutex_scope locker(&mutex_);
		if (elevel >= level_)
		{
			if (iscout_)
			{
				std::cout << msg << std::endl;
			}
			std::string datestr = localdatestr();
			std::string filename("../log/");
			mkdir(filename);
			filename += datestr;
			mkdir(filename);
			filename += "/" + datestr +  ".log";
			std::ofstream out(filename.c_str(), std::ios::app);
			out << "## ";
			out << localdatetimestr();
			out << " ";
			out << LOG_LEVEL_STR[elevel];
			out << " ";
			out << "[" << fileline << "]";
			out << " ";
			out << msg;
			out << std::endl;
			out.close();
		}
	}

	synclog_input::synclog_input(synclog::level level, const char* filename, int line) : level_(level)
	{

		fileline_ << filename << ":" << line;
	}

	void synclog_finisher::operator=(synclog_input& input)
	{
		get_synclog().log(input.level_, input.fileline_.str(), input.msg_.str());
	}

}
