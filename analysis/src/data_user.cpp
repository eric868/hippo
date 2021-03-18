#include "data_user.h"
#include "errordefine.h"
#include "synclog.h"

void DataUser::init()
{
}

void DataUser::parse()
{
	std::vector<std::map<std::string, std::string> > values;
	Parse::parse_file("user.txt", ',', values);

	for (const auto& value : values)
	{
		UserInfo tmp;
		for (const auto& item : value)
		{
			tmp.set_field(item.first, item.second);
		}
		datas_.push_back(tmp);
	}
}

void UserInfo::set_field(const std::string& key, const std::string& value)
{
	auto itemptr = itemptrs_.find(key);
	if (itemptr != itemptrs_.end())
	{
		itemptr->second->set_value(value, *this);
	}
	else
	{
		SYNC_LOG(base::synclog::LOG_ERROR) << GET_ERROR_INFO(E_NO);
	}
}

std::map<std::string, StructFieldBase<UserInfo>* > UserInfo::init_itemptrs()
{
	std::map<std::string, StructFieldBase<UserInfo>* > itemptrs;
	itemptrs["id"] = new StructField<UserInfo, int UserInfo::*>(&UserInfo::id);
	itemptrs["name"] = new StructField<UserInfo, std::string UserInfo::*>(&UserInfo::name);
	itemptrs["age"] = new StructField<UserInfo, int UserInfo::*>(&UserInfo::age);
	itemptrs["money"] = new StructField<UserInfo, double UserInfo::*>(&UserInfo::money);

	return itemptrs;

}
const std::map<std::string, StructFieldBase<UserInfo>* > UserInfo::itemptrs_ = UserInfo::init_itemptrs();