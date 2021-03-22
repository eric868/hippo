#include "server.h"
#include <iostream>
#include <thread>
#include "datetime.h"
#include "synclog.h"
#include "errordefine.h"
#include "publicdatacenter.h"
#include "../common/datatype_core.h"
#include "../common/messagetype.h"
Server::Server()
{
}

Server::~Server()
{
	//stop();
}

void Server::start(const std::string& configfile)
{
	status_.store(kInitializing);
	SYNC_LOG(base::synclog::LOG_INFO) << StatusToString();

	PublicDataCenter::instance();

	status_.store(kInitialized);
	SYNC_LOG(base::synclog::LOG_INFO) << StatusToString();

	while (!IsRunning())
	{
		start_internal();
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

void Server::stop()
{
	stop_internal();
}

void Server::join()
{
	while (!IsStopped())
	{
		SYNC_LOG(base::synclog::LOG_INFO) << "time:" << base::datetime().now().str() << " status:" << StatusToString();
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

int Server::start_internal()
{
	int ret = E_OK;

	status_.store(kStarting);
	SYNC_LOG(base::synclog::LOG_INFO) << StatusToString();

	data_user_.init();
	data_user_.parse();

	status_.store(kRunning);
	SYNC_LOG(base::synclog::LOG_INFO) << StatusToString();

	return ret;
}

int Server::stop_internal()
{
	int ret = E_OK;

	status_.store(kStopping);
	SYNC_LOG(base::synclog::LOG_INFO) << StatusToString();

	status_.store(kStopped);
	SYNC_LOG(base::synclog::LOG_INFO) << StatusToString();

	return ret;
}