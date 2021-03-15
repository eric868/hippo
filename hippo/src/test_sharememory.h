#pragma once
#include <iostream>
#include "sharememory.h"
#include "ssemaphore.h"
#include "util.h"
#ifndef _MSC_VER
#include <unistd.h>
#include <sys/types.h>
#endif

struct SharememoryData
{
	char name[64];
	int age;
};

class TestSharememory
{
public:
	void test()
	{
#ifdef _MSC_VER
		base::sharememory sm1("sm_test");
		int ret = sm1.create(sizeof(SharememoryData));
		if (ret == 0)
		{
			SharememoryData* data = (SharememoryData*)sm1.address();
			strcpy(data->name, "tom");
			data->age = 99;
		}

		base::sharememory sm2("sm_test");
		ret = sm2.create(sizeof(SharememoryData));
		if (ret == 0)
		{
			SharememoryData* data = (SharememoryData*)sm2.address();
			std::cout << "name: " << data->name << " age: " << data->age << std::endl;
		}

#else
		base::ssemaphore ss_producer(1, "ss_producer");
		base::ssemaphore ss_customer(0, "ss_customer");
		if (fork() == 0)
		{
			//子进程消费者
			base::sharememory sm2("sm_test");
			int ret = sm2.create(sizeof(SharememoryData));
			if (ret == 0)
			{
				for (int i = 0; i < 10; ++i)
				{
					ss_customer.wait();
					SharememoryData* data = (SharememoryData*)sm2.address();
					std::cout << "name: " << data->name << " age: " << data->age << std::endl;
					ss_producer.post();
				}
			}
		}
		else
		{
			//父进程生产者
			base::sharememory sm1("sm_test");
			int ret = sm1.create(sizeof(SharememoryData));
			if (ret == 0)
			{
				for (int i = 0; i < 10; ++i)
				{
					ss_producer.wait();
					SharememoryData* data = (SharememoryData*)sm1.address();
					strcpy(data->name, "tom");
					data->age = i+100;
					ss_customer.post();
					base::util::sleep(1000);
				}
			}
		}
#endif
	}
};