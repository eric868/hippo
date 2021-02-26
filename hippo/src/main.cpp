#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "test_dictionary.h"
#include "test_struct_field.h"
#include "test_sigslot.h"
#include "test_alarm.h"
using namespace std;

int main()
{
	TestDictionary test_dictionary;
	test_dictionary.test();

	TestStructField test_structfield;
	test_structfield.test();

	TestSigslot test_sigslot;
	test_sigslot.test();

	TestAlarm test_alarm;
	test_alarm.test();

	getchar();
	return 0;
}