#ifndef APPCLIENT_H_
#define APPCLIENT_H_

#include "ClientBase.h"
#include <thread>

class AppClient : public DataBusClient
{
public:
	AppClient();
	~AppClient();

public: //call back
	virtual void OnMessage(PackagePtr package) override;
	virtual void OnPublish(PackagePtr pubData) override;
	virtual void OnEvent(int eventId) override;

private:
	AppClient(AppClient&);
	void operator=(AppClient&);
};

#endif // APPCLIENT_H_