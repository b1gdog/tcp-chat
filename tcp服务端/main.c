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

	printf("等待客户端连接\n");
	//////初始化//////
	

	char buf[1024] = { 0 };		//定义一个缓冲区 存储发送的数据
	SOCKET 监听套接字;			//监听
	SOCKET 客户套接字;			//和客户进行交流

	SOCKADDR_IN listneinfo;		//监听的结构体
	SOCKADDR_IN clientinfo;		//和客户交流的结构体
	int len = sizeof(clientinfo);

	listneinfo.sin_family = AF_INET;		
	listneinfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	listneinfo.sin_port = htons(60000);	
	/*
		SOCK_DGRAM = udp
		SOCK_STREAM = tcp
	*/
	监听套接字 = socket(AF_INET, SOCK_STREAM, 0);		//创建TCP的socket

	bind(监听套接字, &listneinfo, sizeof(listneinfo));	//bind
	listen(监听套接字, 5);								//5为队列的大小

	客户套接字 = accept(监听套接字, &clientinfo, &len);	

	/*
	//////简单的防火墙//////
	if (clientinfo.sin_addr.S_un.S_addr != "127.0.0.1") //判断来源IP
	{
		closesocket(客户套接字);	//关闭
		return;
	}
	if (clientinfo.sin_port != "80")	//判断来源端口
	{
		closesocket(客户套接字);	//关闭
		return;
	}
	//////简单的防火墙//////
	*/

	///半双工 需要进行等待
	printf("连接成功,等待对方输入......\n");

	while (1)
	{
		//先接收后发送
		
		
		//////接收消息//////
		recv(客户套接字, buf, sizeof(buf), 0); 
		printf("\n收到客户端发来的消息:%s\n", buf);
		//////接收消息//////

		//////发送消息//////
		printf("输入:");
		scanf_s("%s", buf, sizeof(buf));		//从键盘获取发送的内容
		send(客户套接字, buf, sizeof(buf), 0);	//发送
		//////发送消息//////

		///半双工 需要进行等待
		printf("等待对方输入......\n");
	}


	closesocket(客户套接字);	//关闭
	closesocket(监听套接字);	//关闭
	WSACleanup();				//释放
	system("pause");			//等待
}