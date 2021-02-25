#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "test_dictionary.h"
#include "test_struct_field.h"
using namespace std;

int main()
{
	TestDictionary testdictionary;
	testdictionary.test();

	TestStructField test_structfield;
	test_structfield.test();

	getchar();
	return 0;
}