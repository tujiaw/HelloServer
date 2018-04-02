// HelloClient.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "logger.h"
#include "AppClient.h"
#include "./simpleini/SimpleIni.h"
#include "./protobuf/helloserver.pb.h"

using namespace HelloServer;
std::string getFormatCurrentTime()
{
	std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm tm;
	localtime_s(&tm, &tt);
	char buffer[1024] = { 0 };
	sprintf_s(buffer, "%04d/%02d/%02d %02d:%02d:%02d",
		1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return buffer;
}

int64_t getCurrentMilliseconds()
{
	auto time_now = chrono::system_clock::now();
	auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
	return duration_in_ms.count();
}

void sleep_second(int second)
{
	std::this_thread::sleep_for(std::chrono::seconds(second));
}

std::string generateStr(int size)
{
	std::string str;
	str.resize(size);
	for (int i = 0; i < size; i++) {
		str[i] = rand() % 26 + 'A';
	}
	return str;
}

void startThread(AppClient *app, const std::string &name, int intervalSecond, int size)
{
	LOGGER_ERROR("start thread name:" << name << ", interval:" << intervalSecond << "(s), size:" << size << "(bytes)");
	std::thread t([=]() {
		const std::string str = generateStr(size);
		while (1) {
			sleep_second(intervalSecond);
			MessagePtr req(new HelloReq());
			HelloReq *helloReq = static_cast<HelloReq*>(req.get());
			helloReq->set_str(str);
			MessagePtr rsp;
			int64_t start = getCurrentMilliseconds();
			if (app->SendMsg(*helloReq, rsp, 10000)) {
				HelloRsp *helloRsp = static_cast<HelloRsp*>(rsp.get());
				int64_t elapsed = getCurrentMilliseconds() - start;
				LOGGER_ERROR("{name:" << name << ", elapsed:" << elapsed << "ms}");
			} else {
				LOGGER_ERROR("{name:" << name << ", errcode:" << app->GetLatestError().errcode() << "}");
			}
		}
	});
	t.detach();
}

int main(int argc, char* argv[])
{
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

	CSimpleIniA ini;
	ini.LoadFile("./config/setting.ini");
	CSimpleIniA::TNamesDepend sections;
	ini.GetAllSections(sections);
	for (auto iter = sections.begin(); iter != sections.end(); ++iter) {
		std::string name = iter->pItem;
		if (!name.empty()) {
			int interval = (int)ini.GetLongValue(iter->pItem, "interval");
			int size = (int)ini.GetLongValue(iter->pItem, "size");
			if (interval > 0 && size > 0) {
				startThread(appClient, name, interval, size);
			}
		}
	}

	while (1) { sleep_second(1); }
	return 0;
}

