#ifndef _APPSERVERINTF_H_
#define _APPSERVERINTF_H_

#include <string>
#include <vector>
#include "package.h"
#include "../protobuf/protobuf.h"
#include "IPublish.h"

#include <functional>

using namespace std;

struct ServerCFG
{
	bool isValid;
	std::string serverIP;
	int port;
	std::string protocol;
	std::string role;
	int id;
	int groupNum;
	ServerCFG()
	{
		isValid=false;
		protocol="tcp";
		id=0;
		groupNum=0;
	}
    ServerCFG& operator = (const ServerCFG& cfg)
    {
        this->isValid=cfg.isValid;
		this->serverIP=cfg.serverIP;
		this->port=cfg.port;
		this->protocol=cfg.protocol;
		this->role=cfg.role;
		this->id=cfg.id;
		this->groupNum=cfg.groupNum;
	    return *this;
    }
};
struct ClientCFG
{
	std::string appName;
	int appType;
	int appGroup;
	std::string uuid;
	std::string auth;
	std::string localIp;
	std::vector<int> serviceList;
	std::vector<int> subscribeList;
	std::vector<int> datasync;

	ServerCFG udpSenderCfg;
	ServerCFG udpReceiverCfg;
	std::vector<ServerCFG> serverGroup;
	int threadNum;
	int buffersize;
	int sendqueuesize;
	int receivequeuesize;
    int connect_time_out;

	int sendmode;

	int maxHeartBeatTick;
	int heartbeat_interval;
	int broken_interval;
	int heartbeatSwitch;

	int zlibswitch;
	int zlibthreshold;

	bool multipageswitch;
	int multipagesize;

	int loglevel;
	string logfilename;
	bool reportlog;
	int reportlevel;
	ClientCFG()
	{
		appName="";
		appType=0;
		appGroup=-1;
		localIp="";
		uuid="";
		auth="test";
		connect_time_out=5000;
		threadNum=4;
		buffersize=1000000;
		sendqueuesize=10000;
		receivequeuesize=10000;
		maxHeartBeatTick=6;
		heartbeat_interval=5000;
		broken_interval=3000;
		heartbeatSwitch=1;//默认心跳
		zlibswitch=1;
	    zlibthreshold=30;

		multipageswitch = 0;
		multipagesize = 100000;

		sendmode=0;

		loglevel=1;
		logfilename="databus";
		reportlog=false;
		reportlevel=2;
	}
	ClientCFG& operator = (const ClientCFG& cfg)
	{
		appName=cfg.appName;
		appType=cfg.appType;
		localIp=cfg.localIp;
		appGroup=cfg.appGroup;
		auth=cfg.auth;
		uuid=cfg.uuid;
		serviceList=cfg.serviceList;
		subscribeList=cfg.subscribeList;
		datasync=cfg.datasync;

		udpSenderCfg=cfg.udpSenderCfg;
		udpReceiverCfg=cfg.udpReceiverCfg;
		serverGroup=cfg.serverGroup;
		connect_time_out=cfg.connect_time_out;
		threadNum=cfg.threadNum;
		buffersize=cfg.buffersize;
		sendqueuesize=cfg.sendqueuesize;
		receivequeuesize=cfg.receivequeuesize;
		maxHeartBeatTick=cfg.maxHeartBeatTick;
		heartbeat_interval=cfg.heartbeat_interval;
		broken_interval=cfg.broken_interval;
		heartbeatSwitch=cfg.heartbeatSwitch;
		zlibswitch=cfg.zlibswitch;
		zlibthreshold=cfg.zlibthreshold;

		multipageswitch = cfg.multipageswitch;
		multipagesize = cfg.multipagesize;

		loglevel=cfg.loglevel;
		reportlog=cfg.reportlog;
		reportlevel=cfg.reportlevel;
		return *this;
	}
};
enum ProxyType
{
	TypeHTTP	= 0,
	TypeSocks4	= 1,
	TypeSocks5	= 2,
};
///@brief 代理设置结构
struct ProxyCFG
{
	bool enable;
	ProxyType type;
	string address;
	unsigned short port;
	string user;
	string pass;
	string domain;
	ProxyCFG()
	{
		enable=false;
		address=user=pass=domain="";
	}
	ProxyCFG& operator=(const ProxyCFG& cfg)
	{
		enable=cfg.enable;
		type=cfg.type;
		address=cfg.address;
		port=cfg.port;
		user=cfg.user;
		pass=cfg.pass;
		domain=cfg.domain;
		return *this;
	}
};
struct MsgParams
{
	int result; //0表示成功，resp有值，非0表示出错，错误信息在errmsg中，此时resp为空
	std::string errmsg;
	bool hasNextPackage;//是否分包并且还没有收完整
	std::string data;
	MessagePtr req;
	PackagePtr resp;
	void* arg;
	MsgParams()
	{
		result = 0;
		hasNextPackage = false;
		arg = NULL;
	}
};
enum LoadBalanceType : unsigned char
{
	RANDMIZE=0,//随机分配服务
	BYCODE,//根据用户填入的code值分配服务,code/[instance number]
	BYADDRESS,//根据接入到总线分配的地址值分配服务address/[instance number]
};
struct Options
{
	int appId;//发给指定服务号的app
	PackageHeader::MsgType type;
	unsigned int protocol;//数据协议
	unsigned int dstaddr;//发给指定地址的app
	unsigned int serial;//非0则指定流水号
	bool ext;//数据体中是否带有扩展头
	bool multicast;//是否多播
	bool sequence;//是否时序消息
	LoadBalanceType loadbalance;
	unsigned short code;//当loadbalance=BYCODE时有效
	unsigned char version;
	Options()
	{
		appId=-1;
		type=PackageHeader::Request;
		protocol=0;
		dstaddr=0;
		serial=0;
		ext=false;
		multicast=false;
		sequence=false;
		loadbalance=RANDMIZE;
		code=0;
		version = Version2;
	}
};

class AppServerIntf
{
public:
	virtual ~AppServerIntf(){}
public:
	///@brief 客户端初始化函数,
    virtual int  Initialize(ClientCFG* clientCfg,ProxyCFG* proxyCfg)=0;
    ///@brief 客户端释放函数,
    virtual bool  Release()=0;
	///@brief 客户端发送异步消息的接口,返回流水号,0表示失败，如果失败，调用GetLatestError查询错误信息
	virtual unsigned int  PostMessage(const google::protobuf::Message& msg,int appId=-1,unsigned int dstaddr=0)=0;
	virtual unsigned int  PostMessage(int cmd,const char* buff,unsigned int size,Options opt=Options())=0;
	virtual bool  PostMessage(MessagePtr msg,function<void(const MsgParams&)> msgcb,void* arg,unsigned int msTimeout=3000,Options opt=Options())=0;
	///@brief 客户端发送应答消息的接口
	virtual bool Reply(PackagePtr requestPackage,const google::protobuf::Message& replyMsg)=0;
	virtual bool Reply(const PackageHeader& header,const char* buff,unsigned int size)=0;
	virtual bool Reply(PackagePtr requestPackage,unsigned int errCode,string errMsg)=0;
	///@brief 客户端发送同步消息的接口,如果失败，调用GetLatestError查询错误信息
	virtual bool SendMessage(const google::protobuf::Message& request, MessagePtr& response,unsigned int milliseconds,Options opt=Options())=0;
	virtual bool SendMessage(unsigned int cmd,const char* srcBuff,unsigned int srcSize,PackageHeader& retHeader,string& retData,unsigned int milliseconds,unsigned int dstaddr=0)=0;
	//订阅消息
	virtual bool Subscribe(const MsgExpress::SubscribeData& subData, MessagePtr& response)=0;
	virtual bool UnSubscribe(const MsgExpress::UnSubscribeData& subData, MessagePtr& response)=0;
	virtual bool ComplexSubscribe(const MsgExpress::ComplexSubscribeData& subData, MessagePtr& response)=0;
	//简单订阅
	virtual bool Subscribe(int subid,const google::protobuf::Message& subData, MessagePtr& response)=0;
	virtual bool Subscribe(int subid,const vector<MessagePtr>& vecSubmsg, MessagePtr& response)=0;
	virtual bool UnSubscribe(int subid, MessagePtr& response)=0;
	//推送消息
	virtual bool Publish(MessagePtr msg,function<void(const MsgParams&)> msgcb,void* arg,unsigned int msTimeout=3000)=0;
	//获取最近的错误
	virtual MsgExpress::ErrMessage GetLatestError()=0;
	virtual void ClearLatestError()=0;
	//获取本appserver被分配的地址
	virtual unsigned int GetAddress()=0;
	virtual uint64_t GetBrokerTime()=0;//单位毫秒
	//virtual void SetDataManager(IDataManager* manager)=0;
	//virtual IDataManager* GetDataManager()=0;
public:
	function<MessagePtr(const std::string&)> onCreateInstance;
    function<void(const char* buf,unsigned int size)> onRawData;
	function<void(PackagePtr)> onMessage;
	function<void(PackagePtr)> onPublish;
    function<void(int)> onEvent;
};

#endif

