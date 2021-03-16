#pragma once
#include "shareptr.h"
#include <iostream>

class Person
{
public:
	Person(const std::string& name, int age)
		: name_(name)
		, age_(age)
	{
		std::cout << "construction" << std::endl;
	}

	~Person()
	{
		std::cout << "destruction" << std::endl;
	}

	void printinfo()
	{
		std::cout << "name: " << name_ << " age: " << age_ << std::endl;
	}
private:
	std::string name_;
	int age_;
};

class TestShareptr
{
public:
	void test()
	{
		base::shareptr<Person> pp(new Person("tom", 18));
		pp->printinfo();
		std::cout << "refcount: " << pp.get_ref_count() << std::endl;
		{
			base::shareptr<Person> pp2 = pp;
			pp2->printinfo();
			std::cout << "refcount: " << pp.get_ref_count() << std::endl;
		}
		pp->printinfo();
		std::cout << "refcount: " << pp.get_ref_count() << std::endl;
	}

};