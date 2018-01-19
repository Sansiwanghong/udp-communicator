//客户端
#include <stdio.h>   
#include <winsock2.h>   
#include<WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")    
using namespace std;
int main(int argc, char* argv[])
{
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		printf("failed to initial client\n");
		return 0;
		
	}
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sin;
	sin.sin_family = AF_INET;//选择IPV4
	sin.sin_port = htons(8888);//端口号 
	sin.sin_addr.S_un.S_addr = inet_addr("192.168.155.136");
	inet_pton(AF_INET, "192.168.155.136", (void*)&sin.sin_addr.S_un.S_addr);//点十进制转换为二进制给第三个参数

	int len = sizeof(sin);

	const char * sendData = "来自客户端的数据包.\n";
	
	sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);

	while (true)
	{
		char recvData[255];
		int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);
	//	int ret2 = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);
		//printf("ret: %d\n", ret);
		if (ret > 0)
		{
			recvData[ret] = 0x00;//添加结束符‘\0’			
			cout << recvData << endl;
			//printf(recvData);

			

		}
		
	}
	system("pause");
	closesocket(sclient);
	WSACleanup();
	return 0;
}