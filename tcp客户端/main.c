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
	//////��ʼ��//////


	char sendbuf[1024] = { 0 };		//���͵Ļ�����
	char recvbuf[1024] = { 0 };			//���յĻ�����

	SOCKET �������׽���;			//���������н���
	SOCKADDR_IN clientinfo;			//�����������Ľṹ��

	clientinfo.sin_family = AF_INET;
	clientinfo.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	clientinfo.sin_port = htons(60000);
	/*
		SOCK_DGRAM = udp
		SOCK_STREAM = tcp
	*/
	�������׽��� = socket(AF_INET, SOCK_STREAM, 0);		//����TCP��socket

	connect(�������׽���, &clientinfo, sizeof(clientinfo));//�����������ӷ�����


	while (1)
	{	
		//�ȷ��ͺ����


		//////������Ϣ//////
		printf("����:");
		scanf_s("%s", sendbuf, sizeof(sendbuf));		//�Ӽ��̻�ȡ���͵�����
		send(�������׽���, sendbuf, sizeof(sendbuf), 0);	//����
		//////������Ϣ//////

		///��˫�� ��Ҫ���еȴ�
		printf("�ȴ��Է�����......\n");

		//////������Ϣ//////
		recv(�������׽���, recvbuf, sizeof(recvbuf), 0);
		printf("\n�յ�����˷�������Ϣ:%s\n", recvbuf);
		//////������Ϣ//////
	}


	closesocket(�������׽���);	//�ر�

	WSACleanup();				//�ͷ�
	system("pause");			//�ȴ�
}