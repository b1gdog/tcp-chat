#include <winsock.h>
#include <stdio.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")		//加载2版本32位的lib

//TCP服务端
void main()
{
	//////初始化//////
	WORD version = MAKEWORD(2, 2);		//版本号
	WSADATA wsdata;						//定义结构体
	if (WSAStartup(version, &wsdata))	//加载DLL 成功返回0
	{
		printf("加载失败");
		return;
	}
	//////初始化//////


	char sendbuf[1024] = { 0 };		//发送的缓冲区
	char recvbuf[1024] = { 0 };			//接收的缓冲区

	SOCKET 服务器套接字;			//服务器进行交流
	SOCKADDR_IN clientinfo;			//服务器交流的结构体

	clientinfo.sin_family = AF_INET;
	clientinfo.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	clientinfo.sin_port = htons(60000);
	/*
		SOCK_DGRAM = udp
		SOCK_STREAM = tcp
	*/
	服务器套接字 = socket(AF_INET, SOCK_STREAM, 0);		//创建TCP的socket

	connect(服务器套接字, &clientinfo, sizeof(clientinfo));//发起请求连接服务器


	while (1)
	{	
		//先发送后接收


		//////发送消息//////
		printf("输入:");
		scanf_s("%s", sendbuf, sizeof(sendbuf));		//从键盘获取发送的内容
		send(服务器套接字, sendbuf, sizeof(sendbuf), 0);	//发送
		//////发送消息//////

		///半双工 需要进行等待
		printf("等待对方输入......\n");

		//////接收消息//////
		recv(服务器套接字, recvbuf, sizeof(recvbuf), 0);
		printf("\n收到服务端发来的消息:%s\n", recvbuf);
		//////接收消息//////
	}


	closesocket(服务器套接字);	//关闭

	WSACleanup();				//释放
	system("pause");			//等待
}