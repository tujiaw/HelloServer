#ifndef _CLIENTBASE_H_
#define _CLIENTBASE_H_

#include "AppServerIntf.h"
#include "ISubscription.h"
#include "IPublish.h"

class MSGEXPRESS_API DataBusClient
{
private:
	AppServerIntf* m_pAppServer;
public:
	DataBusClient();
	virtual ~DataBusClient();
public:
	///@brief 客户端初始化函数,
    int  Initialize(const char* configPath=NULL,ProxyCFG* proxyCfg=NULL);
	int  Initialize(const wchar_t* configPath,ProxyCFG* proxyCfg=NULL);
	int  Initialize(ClientCFG* clientCfg,ProxyCFG* proxyCfg);
    ///@brief 客户端释放函数,
    bool  Release();
	///@brief 客户端发送异步消息的接口,返回流水号,0表示失败，如果失败，调用GetLatestError查询错误信息,当dstaddr非零时消息路由到指定地址的服务，否则按照总线负载均衡算法路由
	unsigned int  PostMsg(const google::protobuf::Message& msg,int appId=-1,unsigned int dstaddr=0);
	unsigned int  PostMsg(int cmd,const char* buff,unsigned int size,Options opt=Options());
    ///推荐使用的接口
	bool  PostMsg(MessagePtr msg,function<void(const MsgParams&)> msgcb,void* arg,unsigned int msTimeout=3000,Options opt=Options());
	///@brief 客户端发送应答消息的接口
	bool Reply(PackagePtr requestPackage,const google::protobuf::Message& replyMsg);
	bool Reply(PackagePtr requestPackage,const char* buff,unsigned int size);
	bool Reply(PackagePtr requestPackage,unsigned int errCode,string errMsg);
    ///推荐使用的接口
	///@brief 客户端发送同步消息的接口,如果失败，调用GetLatestError查询错误信息，当dstaddr非零时消息路由到指定地址的服务，否则按照总线负载均衡算法路由
	bool SendMsg(const google::protobuf::Message& request, MessagePtr& response,unsigned int milliseconds,Options opt=Options());
	bool SendMsg(unsigned int cmd,const char* srcBuff,unsigned int srcSize,PackageHeader& retHeader,string& retData,unsigned int milliseconds,unsigned int dstaddr=0);
	//订阅消息
	bool Subscribe(ISubscription* subData);
	bool Subscribe(const MsgExpress::SubscribeData& subData, MessagePtr& response);
	bool UnSubscribe(const MsgExpress::UnSubscribeData& subData, MessagePtr& response);
	bool ComplexSubscribe(const MsgExpress::ComplexSubscribeData& subData, MessagePtr& response);
	//简单订阅
	virtual bool Subscribe(int subid,const google::protobuf::Message& subData, MessagePtr& response);
	virtual bool Subscribe(int subid,const vector<MessagePtr>& vecSubmsg, MessagePtr& response);
	virtual bool UnSubscribe(int subid, MessagePtr& response);
	//推送消息
	bool Publish(MessagePtr msg,function<void(const MsgParams&)> msgcb,void* arg,unsigned int msTimeout=3000);
	bool Publish(const MsgExpress::PublishData& pubData);
	//获取最近的错误
	MsgExpress::ErrMessage GetLatestError();
	void ClearLatestError();
	unsigned int GetAddress();
	uint64_t GetBrokerTime();
	int GetQueueSize();
	std::string GetServerIp();
	unsigned int GetCommand(const char* clazz,int packageType,int appId=-1);
	string GetClazz(unsigned int cmd,int packageType,bool isPub);
	//void SetDataManager(IDataManager* manager);
	//IDataManager* GetDataManager();
public: //call back
	virtual void OnMessage(PackagePtr package)=0;
	virtual void OnPublish(PackagePtr pubData);
	virtual void OnPublish(PublishPtr pubData);
	virtual void OnEvent(int eventId)=0;//eventId参见enum Event的定义
private:
	void OnPublishInternal(PackagePtr pubData);
protected:
	AppServerIntf* GetAppServer(){ return m_pAppServer; }
private:
	virtual MessagePtr CreateInstance(const std::string& clazz)
	{
		google::protobuf::Message* message=NULL;
		do
		{
			const google::protobuf::Descriptor* des=google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(clazz);
			if(!des)
				break;
			const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(des);
			if (!prototype)
				break;
			message = prototype->New();
		}while(false);
		return MessagePtr(message);
	}
};

#endif
