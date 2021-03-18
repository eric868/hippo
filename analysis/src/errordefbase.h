#pragma once

#include <map>
#include <string>

class Wrapper
{
public:
	std::map<int, std::string> m_Infos;
	void InsertInfo(int val, std::string str)
	{
		m_Infos[val] = str;
	}
	const std::string& GetInfo(int val)
	{
		return m_Infos[val];
	}
	static Wrapper& _instance()
	{
		static Wrapper w;
		return w;
	}
private:
	Wrapper()
	{

	}
};

#define MAKE_ERROR(name, value, info) \
	const static int name = value;\
class C##name \
{ \
public:\
	C##name(std::string inf) \
{\
	m_Info = inf;\
}\
	std::string m_Info;\
};\
	const static C##name name##name = C##name(info); \
struct C##value \
{ \
	C##value(int v, std::string i) \
{\
	Wrapper::_instance().InsertInfo(v,i);\
}\
} ;\
	const static C##value name##value = C##value(value, info); 

#define GET_ERROR_INFO(name) name##name.m_Info
#define GET_ERROR_INFO_BY_ID(value) Wrapper::_instance().GetInfo(value)
