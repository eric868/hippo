#pragma once

template <typename T>
class StructFieldBase
{
public:
	virtual ~StructFieldBase() {};
	virtual void set_value(const std::string& source, T& inst) = 0;
	virtual std::string get_value(const T& inst) = 0;
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

	inline std::string get_field(std::string value)
	{
		return value;
	}

	inline std::string get_field(int value)
	{
		return std::to_string(value);
	}

	inline std::string get_field(double value)
	{
		return std::to_string(value);
	}

	virtual std::string get_value(const T& inst)
	{
		return get_field(inst.*fieldptr_);;
	}
private:
	IT T::* fieldptr_;
};