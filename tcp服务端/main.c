#include <winsock.h>
#include <stdio.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")		//����2�汾32λ��lib

//TCP�����
void main()
{
	//////��ʼ��//////
	WORD version = MAKEWORD(2, 2);		//�汾��
	WSADATA wsdata;						//����ṹ��
	if (WSAStartup(version, &wsdata))	//����DLL �ɹ�����0
	{
		printf("����ʧ��");
		return;
	}

	printf("�ȴ��ͻ�������\n");
	//////��ʼ��//////
	

	char buf[1024] = { 0 };		//����һ�������� �洢���͵�����
	SOCKET �����׽���;			//����
	SOCKET �ͻ��׽���;			//�Ϳͻ����н���

	SOCKADDR_IN listneinfo;		//�����Ľṹ��
	SOCKADDR_IN clientinfo;		//�Ϳͻ������Ľṹ��
	int len = sizeof(clientinfo);

	listneinfo.sin_family = AF_INET;		
	listneinfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	listneinfo.sin_port = htons(60000);	
	/*
		SOCK_DGRAM = udp
		SOCK_STREAM = tcp
	*/
	�����׽��� = socket(AF_INET, SOCK_STREAM, 0);		//����TCP��socket

	bind(�����׽���, &listneinfo, sizeof(listneinfo));	//bind
	listen(�����׽���, 5);								//5Ϊ���еĴ�С

	�ͻ��׽��� = accept(�����׽���, &clientinfo, &len);	

	/*
	//////�򵥵ķ���ǽ//////
	if (clientinfo.sin_addr.S_un.S_addr != "127.0.0.1") //�ж���ԴIP
	{
		closesocket(�ͻ��׽���);	//�ر�
		return;
	}
	if (clientinfo.sin_port != "80")	//�ж���Դ�˿�
	{
		closesocket(�ͻ��׽���);	//�ر�
		return;
	}
	//////�򵥵ķ���ǽ//////
	*/

	///��˫�� ��Ҫ���еȴ�
	printf("���ӳɹ�,�ȴ��Է�����......\n");

	while (1)
	{
		//�Ƚ��պ���
		
		
		//////������Ϣ//////
		recv(�ͻ��׽���, buf, sizeof(buf), 0); 
		printf("\n�յ��ͻ��˷�������Ϣ:%s\n", buf);
		//////������Ϣ//////

		//////������Ϣ//////
		printf("����:");
		scanf_s("%s", buf, sizeof(buf));		//�Ӽ��̻�ȡ���͵�����
		send(�ͻ��׽���, buf, sizeof(buf), 0);	//����
		//////������Ϣ//////

		///��˫�� ��Ҫ���еȴ�
		printf("�ȴ��Է�����......\n");
	}


	closesocket(�ͻ��׽���);	//�ر�
	closesocket(�����׽���);	//�ر�
	WSACleanup();				//�ͷ�
	system("pause");			//�ȴ�
}