#pragma once
#include <string>
#include "server_status.h"
#include "data_user.h"

class Server : public ServerStatus
{
public:
	Server();
	virtual ~Server();

	void start(const std::string& configfile);
	void stop();
	void join();

private:
	int start_internal();
	int stop_internal();

private:
	DataUser data_user_;
};

