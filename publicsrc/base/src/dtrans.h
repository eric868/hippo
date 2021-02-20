#pragma once
#include "base.h"
#include "dictionary.h"

namespace base
{

class djson
{
public:
	static std::string dict2str(const base::dictionary* dict);
	static std::string dict2str(const base::dictionary& dict);
	static base::dictionary* str2dict(const std::string& json_str);
	static base::dictionary* str2dict(const char* json_str);
};

/*********************************************************************/

class dxml
{
public:
	static std::string dict2str(const base::dictionary* dict);
	static std::string dict2str(const base::dictionary& dict);
	static base::dictionary* str2dict(const std::string& xml_str);
	static base::dictionary* str2dict(const char* xml_str);
};

}