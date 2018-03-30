#ifndef _MSGEXPRESS_H_
#define _MSGEXPRESS_H_


#ifdef _WIN32
 #ifdef MSGEXPRESS_EXPORTS
   #define MSGEXPRESS_API __declspec(dllexport)
 #elif MSGEXPRESS_IMPORTS
   #define MSGEXPRESS_API __declspec(dllimport)
 #else
   #define MSGEXPRESS_API
 #endif
#elif __linux__
  #ifdef MSGEXPRESS_EXPORTS
  #define MSGEXPRESS_API
  #else
  #define MSGEXPRESS_API
  #endif
#endif

enum Event
{
	Online=1,
	Offline=2,
	Upgrade2Master=3,//����ΪMaster����
	Downgrade2Slave=4,//����ΪSlave����
	Downgrade2Standby = 5,//����ΪStandby����
};

#define DEFERROR(name,code,msg) \
    const static int ERRCODE_##name= ((APPID<<20) | code); \
    const static char ERRMSG_##name[]= msg; 

namespace MsgExpress //���߷�����
{
	const static int APPID=0x000;

	const static int KEY_UUID=1;
	const static int KEY_AUTH=2;
	const static int KEY_ADDR=3;
	const static int KEY_NAME=4;
	const static int KEY_TYPE=5;
	const static int KEY_GROUP=6;
	const static int KEY_IP=7;
	const static int KEY_STARTTIME=8;
	const static int KEY_LOGINTIME=9;
	const static int KEY_SERVICE=10;
	const static int KEY_TIME=11;
	const static int KEY_BROKER=12;

	const static int KEY_HBTIME=20;
	const static int KEY_CPU=21;
	const static int KEY_TOPMEM=22; 
	const static int KEY_MEM=23;
	const static int KEY_CSQUEUE=24;//send queue length of the client
    const static int KEY_CRQUEUE=25;//receive queue length of the client

    const static int KEY_QUEUELENGTH=29;//process queue length of server
	const static int KEY_RECVREQUEST=30;
	const static int KEY_SENTREQUEST=31;
	const static int KEY_RECVRESPONSE=32;
	const static int KEY_SENTRESPONSE=33;
	const static int KEY_RECVPUBLISH=34;
	const static int KEY_SENTPUBLISH=35;
	const static int KEY_RECVREQUESTB=36;
	const static int KEY_SENTREQUESTB=37;
	const static int KEY_RECVRESPONSEB=38;
	const static int KEY_SENTRESPONSEB=39;
	const static int KEY_RECVPUBLISHB=40;
	const static int KEY_SENTPUBLISHB=41;

	const static int KEY_LOGLEVEL=61;
	const static int KEY_LOGDATA=62;

	const static int TOPIC_TEST= 0; //����ר��
	const static int TOPIC_LOGIN= ((APPID<<20) | 0x00001);
	const static int TOPIC_LOGOUT= ((APPID<<20) | 0x00002);
	const static int TOPIC_HEARTBEAT= ((APPID<<20) | 0x00003);
	const static int TOPIC_LOG= ((APPID<<20) | 0x00004);

	const static int TOPIC_MAX= ((APPID<<20) | 0x10000);
	/*
	topic TOPIC_RESERVE_START to TOPIC_RESERVE_END����������;
	*/
	const static int TOPIC_SPECIAL_START= ((APPID<<20) | 0x10001);
	const static int TOPIC_SPECIAL_END=   ((APPID<<20) | 0x20000);

    DEFERROR(NOTCONNECTED,0x00001,"Disconnect to data bus.");
    DEFERROR(TIMEOUT,0x00002,"Time out.");
    DEFERROR(REGISTERR,0x00003,"Regist sync message error.");
    DEFERROR(SERIALIZEFAILE,0x00004,"Serialize message failed.");
    DEFERROR(UNSERIALIZEFAILE,0x00005,"Unserialize message failed.");
    DEFERROR(SENDQUEUEFULL,0x00006,"Send queue is full.");
    DEFERROR(NOSERVICE,0x00007,"No service available.");
	DEFERROR(NORIGHTS,0x00008,"No rights.");
	DEFERROR(UNZIPFAILED,0x00009,"Uncompress failed.");
	DEFERROR(COMMANDDEFINEDERR,0x0000A,"Command defined error.");
	DEFERROR(LOSTDATA,0x0000B,"Lost data.");
};

namespace Gateway //���ط�����
{
	const static int APPID=0x001;

	const static int KEY_STATE=1;//0��ʾ�Ͽ����磬1��ʾ��������
	const static int KEY_TOKEN=2;
	const static int KEY_USERID=3;
	const static int KEY_TIME=11;

	const static int TOPIC_OFFLINE= ((APPID<<20) | 0x00001); //�û�����
	const static int TOPIC_HEARTBEAT= ((APPID<<20) | 0x00002);
    const static int TOPIC_LOGOUT= ((APPID<<20) | 0x00003);
	const static int TOPIC_LOGIN= ((APPID<<20) | 0x00004);
	const static int TOPIC_NETWORKSTATE= ((APPID<<20) | 0x00005);//����״̬

    DEFERROR(NOLOGIN,0x00001,"Gateway not login to data bus.");
    DEFERROR(NOCLIENTINFO,0x00002,"Cant get client info.");
    DEFERROR(NOAUTHENRITY,0x00003,"Has not been authenrized to access service.");
	DEFERROR(UNCOMPRESSFAIL,0x00004,"Uncompress failed.");
	DEFERROR(PARSEFAILED,0x00005,"Parse failed.");
	DEFERROR(NOADDRESS,0x00006,"Map token to address failed.");
	DEFERROR(NOAPPINFO,0x00007,"Broker has no app info.");
	DEFERROR(OTHER,0x000FF,"Other error.");
};

namespace Storage //�洢����
{
	const static int APPID=0x004;

	const static int KEY_DATA=1;//
	const static int KEY_DATASET=2;//

	const static int TOPIC_NEWDATA= ((APPID<<20) | 0x00001);
	const static int TOPIC_DELDATA= ((APPID<<20) | 0x00002);

    DEFERROR(NONE,0x00001,"None.");

};

namespace DesktopGateway //��������������
{
	const static int APPID=0x002;

	const static int KEY_NONE=1;

	const static int TOPIC_NONE= ((APPID<<20) | 0x00001);


    DEFERROR(NONE,0x00001,"None.");

};

namespace STOCK
{
	const static int APPID=0x0F0;

	const static int KEY_DATETIME=1; //����
	const static int KEY_CODE=2; //����
	const static int KEY_FULLNAME_CH=3; //����ȫ��
	const static int KEY_SIMPLENAME_CH=4; //���ļ��
	const static int KEY_FULLNAME_EN=5; //Ӣ��ȫ��
	const static int KEY_SIMPLENAME_EN=6; //Ӣ�ļ��
	const static int KEY_MARKET=7; //�г�
	const static int KEY_OPEN=8; //���̼�
	const static int KEY_CLOSE=9; //���̼�
	const static int KEY_LOW=10; //��ͼ�
	const static int KEY_HIGH=11; //��߼�
	const static int KEY_VOL=12; //�ɽ���
	const static int KEY_AMOUNT=13; //�ɽ���
	const static int KEY_MA5=14; //5�վ���
	const static int KEY_MA10=15; //10�վ���
	const static int KEY_MA20=16; //20�վ���
	const static int KEY_MA30=17; //30�վ���
	const static int KEY_MA60=18; //60�վ���

	const static int TOPIC_NONE= ((APPID<<20) | 0x00001);


    DEFERROR(NONE,0x00001,"None.");

};

#endif