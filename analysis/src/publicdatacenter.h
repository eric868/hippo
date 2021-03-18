#pragma once

class PublicDataCenter
{
public:
	static PublicDataCenter& instance()
	{
		static PublicDataCenter pb;
		return pb;
	}
	~PublicDataCenter(){};

private:
	PublicDataCenter();

private:

};



