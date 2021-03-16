#pragma once
#include <iostream>
#include "datetime.h"

class TestDatetime
{
public:
	void test()
	{
		base::date date;
		std::cout << date.now().str() << std::endl;

		base::time time;
		std::cout << time.now().str() << std::endl;

		base::datetime datetime;
		std::cout << datetime.now().str() << std::endl;

		base::datetime datetime1;
		datetime1.m_date.setvalue("2021-03-17");
		std::cout << datetime1.str() << std::endl;

		datetime1.m_time.setvalue("17:30:00");
		std::cout << datetime1.str() << std::endl;
	}
};