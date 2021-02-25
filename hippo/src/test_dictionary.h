#pragma once
#include "dictionary.h"
class TestDictionary
{
public:
	void test()
	{
		base::dictionary dict1;
		dict1.add_object("one", "one");
		dict1.add_object("two", 2);
		dict1.add_object("three", 3.14);

		base::darray darr1;
		darr1.append("tom");
		darr1.append(1);
		darr1.append(2.22);

		base::dictionary* dict2 = new base::dictionary();
		base::ref_dictionary refdict1(dict2);
		dict2->add_object("four", dict1);
		dict2->add_object("five", darr1);
		dict2->print();

		base::dictionary* dict3 = new base::dictionary();
		dict3->add_object("six", 6);
		base::ref_dictionary* refdict2 = new base::ref_dictionary(dict3);
		{
			refdict2->retain();
			refdict2->release();
		}
		refdict2->release();
	}
};