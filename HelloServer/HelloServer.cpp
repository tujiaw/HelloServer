// testServer.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <string>
#include <thread>
#include <tchar.h>
#include "logger.h"
#include "AppClient.h"


int _tmain(int argc, _TCHAR* argv[])
{

	////////////////////////////////////////////////////////
	bool logResult = LogInit("./config/log4cxx.properties");
	if (!logResult) {
		std::cout << "init log error" << std::endl;
		return 1;
	}

	AppClient *appClient = new AppClient();
	int appResult = appClient->Initialize("./config/");
	if (appResult != 0) {
		std::cout << "init app client error, code:" << appResult << std::endl;
		return 2;
	}

	while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}

