#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "singleton.h"
#include "lock.h"

#define APP_LOG(LEVEL) base::synclog_finisher() = base::synclog_input(LEVEL, __FILE__, __LINE__)

namespace base
{
	class synclog 
	{
        SINGLETON_UNINIT(synclog)
	public:
		enum level
		{
			LOG_TRACE = 1,
			LOG_DEBUG,
			LOG_INFO,
			LOG_WARNING,
			LOG_ERROR,
			LOG_CRITICAL
		};

		static void set_level(unsigned int level);
		std::string localdatetimestr();
		std::string localdatestr();
		void mkdir(const std::string& dir);
		void log(level elevel, const std::string& fileline, const std::string& msg);
	
	private:
		static bool iscout_;
		static int level_;
		static mutex mutex_;
	};
    SINGLETON_GET(synclog)

	class synclog_input
	{    
	public:
		synclog_input(synclog::level level, const char* filename, int line);
				
		synclog_input& operator<<(char c)
		{ msg_ << c; return *this; };
		synclog_input& operator<<(short s)
		{ msg_ << s; return *this; };
		synclog_input& operator<<(int n)                  
		{ msg_ << n; return *this; };
		synclog_input& operator<<(unsigned int un)        
		{ msg_ << un; return *this; };
		synclog_input& operator<<(float f)                
		{ msg_ << f; return *this; };
		synclog_input& operator<<(double d)               
		{ msg_ << d; return *this; };
		synclog_input& operator<<(long l)                 
		{ msg_ << l; return *this; };
		synclog_input& operator<<(const char* msg)        
		{ msg_ << msg; return *this; };
		synclog_input& operator<<(const std::string& msg) 
		{ msg_ << msg; return *this; };

		friend class synclog_finisher;
	private:
		std::stringstream fileline_;
		std::stringstream msg_;
		synclog::level level_;
	};

	class synclog_finisher
	{
	public:
		void operator=(synclog_input& input);
	};

}

