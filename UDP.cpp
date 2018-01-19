#include "UDP.h"
#include<stdio.h>
#include<Windows.h>
#include<iostream>
#include<string>


using namespace std;

UDP::UDP()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printf("初始化失败");
		//return 0;//Failed;
	}

	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		//return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(serSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(serSocket);
		//return 0;
	}

	sockaddr_in remoteAddr;
	//新添加的指定地址client
	sockaddr_in remoteAddr2;
	//remoteAddr2.sin_family = AF_INET;
	//remoteAddr2.sin_port = htons(8888);

	//inet_pton(AF_INET, "192.168.155.136", (void*)&remoteAddr.sin_addr.S_un.S_addr);
	inet_pton(AF_INET, "192.168.155.135", (void*)&remoteAddr2.sin_addr.S_un.S_addr);//点十进制转换为二进制给第三个参数
	//???

	int nAddrLen = sizeof(remoteAddr);
	int nAddrLen2 = sizeof(remoteAddr2);
	//检测连接上的客户端
	char recvData[255];
	int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr*)&remoteAddr, &nAddrLen);
	if (ret > 0)
	{
		recvData[ret] = 0x00;
		char sendBuf[20] = { '\0' };
		//打印客户端的IP
		printf("接受到一个连接：%s \r\n", inet_ntop(AF_INET, (void*)&remoteAddr.sin_addr, sendBuf, 16));
		printf(recvData);
	}
	//检测连接上的客户端
	//char recvData2[255];
	//int ret2 = recvfrom(serSocket, recvData2, 255, 0, (sockaddr*)&remoteAddr2, &nAddrLen2);
	//if (ret2 > 0)
	//{
	//	recvData2[ret2] = 0x00;
	//	char sendBuf2[20] = { '\0' };
	//	//打印客户端的IP
	//	printf("接受到一个连接：%s \r\n", inet_ntop(AF_INET, (void*)&remoteAddr2.sin_addr, sendBuf2, 16));
	//	printf(recvData2);
	//}
	while (true)
	{
		
		//服务器发出的数据包
	    char * sendData = "一个来自服务端的UDP数据包\n";
		char * sendData2 = "一个来自服务端的UDP数据包\n";
		getIn();
		
		sendData = DATAbuf[255];
		
		//sendData2 = DATAbuf;
		//printf("%d",strlen(sendData));
		sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);
		
		sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr2, nAddrLen2);
		
	}
	closesocket(serSocket);
	WSACleanup();
}

UDP::~UDP()
{
}
void UDP::getIn()
{

	cout << "请输入要发送信息:\n";//发送字符长度不超过255
	string DATAstr;
	cin >> DATAstr;
	int len;
	len = DATAstr.length();
	DATAstr.copy(sendDATA, len, 0);

	sendDATA[len] = 0x00;
	DATAbuf[255] = sendDATA;
}