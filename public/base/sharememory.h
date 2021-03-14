#pragma once

#include <string>
#ifdef _MSC_VER
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <functional>
#endif

namespace base
{
	class sharememory
	{
	public:
		sharememory(const std::string& name);
		~sharememory();

		int create(size_t length);
		int destory();
		int open();
		int close();
		const std::string& name() const;
		void* address();
		static bool exists(const std::string& name);

	private:
		std::string name_;
#ifdef _MSC_VER
		HANDLE hmapping_;
		LPVOID address_;
#else
		int hmapping_;
		char* address_;
#endif
	};
}