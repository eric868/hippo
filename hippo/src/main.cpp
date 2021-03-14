#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "test_dictionary.h"
#include "test_struct_field.h"
#include "test_sigslot.h"
#include "test_alarm.h"
#include "test_thread.h"
#include "test_singleton.h"
#include "test_shareptr.h"

using namespace std;

int main()
{
	base::synclog::level_ = base::synclog::LOG_TRACE;
	base::synclog::iscout_ = true;

	TestShareptr test_shareptr;
	test_shareptr.test();

	TestThread test_thread;
	test_thread.test();

	TestSingleton::instance()->test();

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