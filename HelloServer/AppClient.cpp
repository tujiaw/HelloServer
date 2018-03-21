#include "AppClient.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "protobuf.h"

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

AppClient::AppClient()
	: t_(std::bind(&AppClient::threadHandle, this))
{
}


AppClient::~AppClient()
{
}

void AppClient::OnMessage(PackagePtr package)
{
	std::string type = package->getClassType();
	std::cout << "on message, class type:" << type << std::endl;
	if (type == "HelloServer.HelloReq") {
		HelloReq *req = static_cast<HelloReq*>(package->getMessage().get());
		MessagePtr rsp(new HelloRsp());
		HelloRsp* p = static_cast<HelloRsp*>(rsp.get());
		p->set_code(0);
		p->set_content(std::to_string(getCurrentMilliseconds()));
		this->Reply(package, *rsp.get());
	}
}

void AppClient::OnPublish(PackagePtr pubData)
{

}

void AppClient::OnEvent(int eventId)
{

}

void AppClient::threadHandle()
{
	while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		MessagePtr sub(new HelloSub());
		HelloSub *p = static_cast<HelloSub*>(sub.get());
		p->set_str1(getFormatCurrentTime());
		this->Publish(sub, [](const MsgParams &msg) {
			std::cout << "publish result:" << msg.result << std::endl;
		}, nullptr);
	}
}