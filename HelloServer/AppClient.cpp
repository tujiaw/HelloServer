#include "AppClient.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "./protobuf/helloserver.pb.h"

using namespace HelloServer;

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
	std::cout << "================on message type:" << type << "===============" << std::endl;
	if (type == "HelloServer.HelloReq") {
		HelloReq *req = static_cast<HelloReq*>(package->getMessage().get());
		MessagePtr rsp(new HelloRsp());
		HelloRsp* p = static_cast<HelloRsp*>(rsp.get());
		p->set_str(req->str());
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
	return;
	int number = 0;
	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		MessagePtr sub(new HelloSub());
		HelloSub *p = static_cast<HelloSub*>(sub.get());
		std::string str2;
		for (int i = 0; i < 1024; i++) {
			str2 += "a";
		}
		p->set_str2(str2);
		p->set_str1(std::to_string(getCurrentMilliseconds()));
		this->Publish(sub, [&number](const MsgParams &msg) {
			std::cout << "publish result:" << msg.result << ", number:" << ++number << std::endl;
		}, nullptr);
	}
}