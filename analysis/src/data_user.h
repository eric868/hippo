#pragma once
#include "parse.h"
#include "struct_field.h"


struct UserInfo
{
	int id;
	std::string name;
	int age;
	double money;

	void set_field(const std::string& key, const std::string& value);

private:
	static std::map<std::string, StructFieldBase<UserInfo>* > init_itemptrs();
	const static std::map<std::string, StructFieldBase<UserInfo>* > itemptrs_;
};

class DataUser
{
public:
	void init();
	void parse();

private:
	std::vector<UserInfo> datas_;
};