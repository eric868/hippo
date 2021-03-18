#pragma once
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#define SET_STRUCT_FIELD(inst, field, data) inst.##field = data

class Parse
{
public:
	static void parse_file(const std::string& filename, char split, std::vector<std::map<std::string, std::string> >& results);
	static void split_string_to_vector(const std::string& str, char delim, std::vector<std::string>& result);
};