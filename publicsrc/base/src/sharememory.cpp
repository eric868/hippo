
#include "sharememory.h"

base::sharememory::sharememory(const std::string& name) : name_(name)
{
#ifdef _MSC_VER
	hmapping_ = NULL;
	address_ = NULL;
#else
	hmapping_ = -1;
	address_ = NULL;
#endif
}

base::sharememory::~sharememory()
{
	destory();
}

int base::sharememory::create(size_t length)
{
#ifdef _MSC_VER
	if (NULL != address_ || NULL != hmapping_) return -1;

	hmapping_ = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, length, name_.c_str());
	if (hmapping_ != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		//已经存在
		CloseHandle(hmapping_);
		hmapping_ = NULL;
		return -2;
	}
	else if (NULL == hmapping_)
	{
		//创建失败
		return -3;
	}

	//映射内存
	address_ = MapViewOfFileEx(hmapping_, FILE_MAP_ALL_ACCESS, 0, 0, length, 0);
	if (NULL == address_)
	{
		CloseHandle(hmapping_);
		hmapping_ = NULL;
		return -4;
	}
#else
	if (NULL != address_ || -1 != hmapping_) return -1;

	size_t key = std::hash<std::string>()(name_);
	hmapping_ = shmget(key, length, IPC_CREAT);
	if (-1 == hmapping_) { return -2; }

	// attach share memory
	address_ = (char*)shmat(hmapping_, 0, 0);
	if ((void*)-1 == address_)
	{
		shmctl(hmapping_, IPC_RMID, 0);
		hmapping_ = -1;
		address_ = NULL;
		return -3;
	}
#endif
	return 0;
}

int base::sharememory::destory()
{
#ifdef _MSC_VER
	if (NULL == address_ || NULL == hmapping_) return -1;

	UnmapViewOfFile(address_);
	CloseHandle(hmapping_);
	address_ = NULL;
	hmapping_ = NULL;
#else
	if (NULL == address_ || -1 == hmapping_) return -1;

	//detech and remove share memory
	shmdt(address_);
	shmctl(hmapping_, IPC_RMID, 0);
	address_ = NULL;
	hmapping_ = -1;
#endif
	return 0;
}

int base::sharememory::open()
{
#ifdef _MSC_VER
	if (NULL != address_ || NULL != hmapping_) return -1;

	//open share memory
	hmapping_ = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, name_.c_str());
	if (NULL == hmapping_) { return -2; }

	//attach share memory
	address_ = MapViewOfFileEx(hmapping_, FILE_MAP_ALL_ACCESS, 0, 0, 0, 0);
	if (NULL == address_)
	{
		CloseHandle(hmapping_);
		hmapping_ = NULL;
		return -3;
	}
#else
	if (NULL != address_ || -1 != hmapping_) return -1;

	//open share memory
	size_t key = std::hash<std::string>()(name_);
	hmapping_ = shmget(key, 0, SHM_R | SHM_W);
	if (-1 == hmapping_) { return -2; }

	//attach share memory
	address_ = (char*)shmat(hmapping_, 0, 0);
	if ((void*)-1 == address_)
	{
		return -3;
	}
#endif
	return 0;
}

int base::sharememory::close()
{
#ifdef _MSC_VER
	if (NULL == address_ || NULL == hmapping_) return -1;

	UnmapViewOfFile(address_);
	//CloseHandle(hmapping_);
	address_ = NULL;
	//hmapping_ = NULL;
#else
	if (NULL == address_ || -1 == hmapping_) return -1;

	//detech and remove share memory
	shmdt(address_);
	//shmctl(hmapping_, IPC_RMID, 0);
	address_ = NULL;
	//hmapping_ = -1;
#endif
	return 0;
}

const std::string& base::sharememory::name() const
{
	return name_;
}

void* base::sharememory::address()
{
	return address_;
}

bool base::sharememory::exists(const std::string& name)
{
#ifdef _MSC_VER
	HANDLE ret = OpenFileMapping(FILE_MAP_READ, false, name.c_str());
	return (ret != NULL);
#else
	size_t key = std::hash<std::string>()(name);
	int ret = shmget(key, 0, SHM_R);
	return (ret != -1);
#endif
}
