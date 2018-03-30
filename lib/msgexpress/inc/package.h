#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#ifdef _WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#endif

#define LIBVERSION "20180118"
#define MAXPACKSIZE 102400*5

#include <memory>
#include "msgexpress.h"
#include "AppAddress.h"
#include "../protobuf/protobuf.h"
#ifdef _WIN32
    #ifdef MSGEXPRESS_EXPORTS
    #include "winSock2.h"
    #endif
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#elif __linux__
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#endif
#include <sys/timeb.h>
#include <string.h>

using namespace std;

#ifndef strprintf
#ifdef _WIN32
	#define strprintf sprintf_s
#else
	#define strprintf snprintf
    #define stricmp strcasecmp
#endif
#endif

static const char PackageFlag='P';
static const unsigned char Version1=1;
static const unsigned char Version2 = 2;

#ifndef ntohll
uint64_t ntohll(uint64_t val);
uint64_t htonll(uint64_t val);
#endif
uint64_t getCurrentTime();//return ms

#pragma pack(push,1)
struct MSGEXPRESS_API PackageHeader
{
	enum MsgType
	{
		Request=1,
		Response,
		Publish,
	};
	char flag1;                 //���ݰ���ʼ��ʶ'P'
	char flag2;                 //���ݰ���ʼ��ʶ'P'
	unsigned char version;     //�汾�ţ�2
	unsigned char type;        //���ݰ�����MsgType
	unsigned char off;         //���ݿ��ƫ����
	union {
	    unsigned char options;     //������
		struct {
			unsigned char ext:1; //�Ƿ�����չ����
			unsigned char protocol:2;//�������л�Э�飬0��ʾprotobuf�������ʾ�Զ���
			unsigned char multicast:1; //�Ƿ��鲥
			unsigned char sequence:1; //�Ƿ�ʱ����Ϣ
			unsigned char loadbalance:2;
			unsigned char pubmsg:1;//�Ƿ�Ϊpublish����ͨ��Ϣ
		};
	};
	union 
	{
		unsigned char codeinfo;
		struct {
			unsigned char iszip:1;//�Ƿ�ѹ��
			unsigned char isencrypt:1;//�Ƿ����
			unsigned char compratio:6;//ѹ����
		};
	};
	union {
	    unsigned char multipageinfo;
		struct {
			unsigned char ismultipage:1; //�Ƿ�ְ�
			unsigned char pageno:7;//�����,��1��ʼ��ţ�0��ʾ���һ����
		};
	};
	unsigned int serialnum;    //��ˮ��
	unsigned int bodysize;     //���ݰ����С
	unsigned int srcaddr;    //Դ��ַ
	unsigned int dstaddr;    //Ŀ���ַ
	union {
		unsigned int command;   //���ȫ��Ψһ
        struct { 
            unsigned int functionindex:20;//app��api��ʶ��
            unsigned int app:12;  //app���
        };
	    //unsigned int topic;//topic��ȫ��Ψһ������Ϣ����ΪPublishʱ��Ч��
	};
    unsigned short code;

	PackageHeader();
	PackageHeader(const PackageHeader& header);
	void read(const char* buffer);
	void write(char* buffer)const;
	string getDebugString() const;
};
#pragma pack(pop)

static const size_t PackageHeaderLength=sizeof(PackageHeader);

class Package;

typedef  shared_ptr<google::protobuf::Message> MessagePtr;
typedef  shared_ptr<Package> PackagePtr;
typedef  shared_ptr<MsgExpress::PublishData> PublishPtr;

class MSGEXPRESS_API Package
{
private:
	PackageHeader m_Header;
	MessagePtr m_pMsg;
    MessagePtr m_pExtMsg;
	std::string m_Type;
	char*  m_pContent;
	size_t m_Size;
private:
	Package();
public:
	Package(const PackageHeader& header,const std::string& classType,const char* data,size_t size,MessagePtr pMsg);
	~Package();

	MessagePtr getMessage();
	MessagePtr getExtMessage();
	void setExtMessage(MessagePtr msg);
	void setMessage(MessagePtr msg);
	std::string getClassType();
	void setClassType(const std::string& clazz);
	PackageHeader::MsgType getPackageType();
	
	unsigned int getCommand();
	unsigned int getApp();
	unsigned int getFunctionIdx();
	char* getContent();
	size_t getSize();
    const PackageHeader& getHeader();
public:
	char* getBodyData();
	unsigned int getBodySize();
    void setSrcAddr(unsigned int addr);
	unsigned int getSrcAddr();
    void setDstAddr(unsigned int addr); 
	void setCode(unsigned short code); 
    unsigned int getDstAddr();
	void setSerialNum(unsigned int serila);
	unsigned int getSerialNum();
	bool isMulticast();
    std::string getDebugString(bool showHexContent=false);
};

#endif
