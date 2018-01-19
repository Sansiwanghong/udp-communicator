#pragma once
#include <stdio.h>
#include<string.h>
#include <winsock2.h>   
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

class UDP
{
public:
    
	UDP();
	~UDP();
	void getIn();
	char sendDATA[255];//从控制台写入，便于controlCenter访问；
private:
	char *DATAbuf[255];//缓存，等待UDP发出；

};

