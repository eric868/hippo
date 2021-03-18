#include "parse.h"
#include <fstream>
#include "synclog.h"
#include "errordefine.h"

void Parse::parse_file(const std::string& filename, char split, std::vector<std::map<std::string, std::string> >& results)
{
	std::ifstream in(filename);
	if (in.is_open() && !in.eof())
	{
		std::string str;
		getline(in, str);
#ifndef _MSC_VER
		str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
#endif
		std::vector<std::string> keys;
		split_string_to_vector(str, split, keys);
		while (!in.eof())
		{
			getline(in, str);
#ifndef _MSC_VER
			str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
#endif
			if (str.empty()) continue;
			std::vector<std::string> values;
			split_string_to_vector(str, split, values);
			if (keys.size() != values.size())
			{
				SYNC_LOG(base::synclog::LOG_ERROR) << GET_ERROR_INFO(E_NO);
				continue;
			}
			std::map<std::string, std::string> tmp;
			for (std::size_t i = 0; i < keys.size(); ++i)
			{
				tmp[keys[i]] = values[i];
			}
			results.push_back(tmp);
		}
	}
}

void Parse::split_string_to_vector(const std::string& str, char delim, std::vector<std::string>& result)
{
	size_t pos_begin = str.find_first_not_of(delim, 0);
	size_t pos_end = str.find(delim, pos_begin);
	while (pos_begin != std::string::npos)
	{
		result.push_back(str.substr(pos_begin, pos_end - pos_begin));
		pos_begin = str.find_first_not_of(delim, pos_end);
		pos_end = str.find(delim, pos_begin);
	}
}