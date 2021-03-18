#include <iostream>
#include <sstream>
#include <string>
#include <signal.h>

#ifndef _MSC_VER
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "version.h"
#include "server.h"

Server server;

#ifndef _MSC_VER
#include <sys/ipc.h>
#include <sys/shm.h>

bool check_single_instance()
{
	// 打开或创建一个文件
	std::string file_path = "./pid.lck";
	int fd = open(file_path.c_str(), O_RDWR | O_CREAT, 0666);
	if (fd < 0) {
		printf("Open file failed, error : %s", strerror(errno));
		exit(1);
	}

	// 将该文件锁定
	// 锁定后的文件将不能够再次锁定
	int ret = lockf(fd, F_TLOCK, 0);
	if (ret < 0) {
		if (errno == EACCES || errno == EAGAIN) {
			printf("%s already locked, error: %s\n", file_path.c_str(), strerror(errno));
			close(fd);
			return false;
		}
	}

	// 锁定文件后，将该进程的pid写入文件
	char buf[32] = { 0 };
	sprintf(buf, "process id:%d", getpid());
	ftruncate(fd, 0);
	ret = write(fd, buf, strlen(buf));
	if (ret < 0) {
		printf("Write file failed, file: %s, error: %s\n", file_path.c_str(), strerror(errno));
		close(fd);
		exit(1);
	}

	// 函数返回时不需要调用close(fd)
	// 不然文件锁将失效
	// 程序退出后kernel会自动close
	return true;
}

//Bit-mask values for 'flags' argument of become_daemon()
#define BD_NO_CHDIR           01    //Don't chdir("/")
#define BD_NO_CLOSE_FILES     02    //Don't close all open files
#define BD_NO_REOPEN_STD_FDS  04    //Don't reopen stdin, stdout, and
//stderr to /dev/null
#define BD_NO_UMASK0         010    //Don't do a umask(0)

#define BD_MAX_CLOSE  8192          //Maximum file descriptors to close if
//sysconf(_SC_OPEN_MAX) is indeterminate
//Returns 0 on success, -1 on error
int become_daemon(int flags)
{
	int maxfd, fd;

	switch (fork())                     //Become background process
	{
	case -1: return -1;
	case 0:  break;                     //Child falls through...
	default: _exit(EXIT_SUCCESS);       //while parent terminates
	}

	if (setsid() == -1)                 //Become leader of new session
		return -1;

	switch (fork()) {                   //Ensure we are not session leader
	case -1: return -1;
	case 0:  break;
	default: _exit(EXIT_SUCCESS);
	}

	if (!(flags & BD_NO_UMASK0))
		umask(0);                       //Clear file mode creation mask

	if (!(flags & BD_NO_CHDIR))
		chdir("/");                     //Change to root directory

	if (!(flags & BD_NO_CLOSE_FILES)) { //Close all open files
		maxfd = sysconf(_SC_OPEN_MAX);
		if (maxfd == -1)                //Limit is indeterminate...
			maxfd = BD_MAX_CLOSE;       //so take a guess

		for (fd = 0; fd < maxfd; fd++)
			close(fd);
	}

	if (!(flags & BD_NO_REOPEN_STD_FDS)) {
		close(STDIN_FILENO);            //Reopen standard fd's to /dev/null

		fd = open("/dev/null", O_RDWR);

		if (fd != STDIN_FILENO)         //'fd' should be 0
			return -1;
		if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
			return -1;
		if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
			return -1;
	}

	return 0;
}
#endif

void usage(const char *bin)
{
	std::cout << std::endl
		<< "-----------------------------------------------------" << std::endl
		<< "usage: " << bin << "[options]" << std::endl
		<< "  -c config-file : config file" << std::endl
		<< "  -v             : get version" << std::endl
		<< "  -d             : service run as deamon" << std::endl
		<< "  -h             : get help info" << std::endl
		<< "-----------------------------------------------------" << std::endl;
}

void handler(int signo)
{
	std::cout << "catch signal:" << signo << std::endl;
	if (signo == SIGINT)
	{
		server.stop();
	}
}

static int proc_main(std::string& param)
{
#ifndef _MSC_VER
	//Repeat start disable
	if (!check_single_instance()) return -1;
#endif

	server.start(param);
	server.join();

	std::cout << "server exit" << std::endl;
	return 0;
}

int main(int argc, char* argv[])
{
	std::string curr_path = argv[0];
#ifndef _MSC_VER
	int pos = curr_path.rfind("/");
	curr_path = curr_path.substr(0, pos);
	std::string config_file = curr_path + "/config/analysis_server_config.xml";
	const char* binary_name = strrchr(argv[0], '/');
#else
	int pos = curr_path.rfind("\\");
	curr_path = curr_path.substr(0, pos);
	std::string config_file = curr_path + "/config/analysis_server_config.xml";
	const char* binary_name = strrchr(argv[0], '\\');
#endif

#ifndef _MSC_VER
	bool run_as_deamon = false;
	int c;
	while ((c = getopt(argc, argv, "c:t:vdh")) != -1) {
		switch (c) {
		case 'c':
			config_file = optarg;
			break;
		case 'v':
			fprintf(stdout, "current version is '%s' (%s)\n", CURRENT_VERSION, UPDATE_DATE);
			return 0;
		case 'd':
			run_as_deamon = true;
			break;
		case 'h':
		case '?':
			usage(binary_name);
			return 0;
		default:
			break;
		}
	}
	if (run_as_deamon)
	{
		// run as deamon
		become_daemon(BD_NO_CHDIR);
	}
	else
	{
		signal(SIGPIPE, handler);
		signal(SIGINT, handler);
		signal(SIGHUP, handler);
		signal(SIGTERM, handler);
		signal(SIGCHLD, handler);
		signal(SIGTSTP, handler);
		signal(SIGQUIT, handler);
	}
#endif

	proc_main(config_file);

	return 0;
}
