#pragma once

template <typename T>
class StructFieldBase
{
public:
	virtual ~StructFieldBase() {};
	virtual void set_value(const std::string& source, T& inst) = 0;
};

template <typename T, typename IT>
class StructField {};

template <typename T, typename IT>
class StructField<T, IT T::*> : public StructFieldBase<T>
{
public:
	StructField(IT T::* fieldptr)
		: fieldptr_(fieldptr) {}

	inline void set_field(const std::string& source, std::string& value)
	{
		value = source;
	}

	inline void set_field(const std::string& source, int& value)
	{
		value = atoi(source.c_str());
	}

	inline void set_field(const std::string& source, double& value)
	{
		value = atof(source.c_str());
	}


	virtual void set_value(const std::string& source, T& inst)
	{
		set_field(source, inst.*fieldptr_);
	}

private:
	IT T::* fieldptr_;
};