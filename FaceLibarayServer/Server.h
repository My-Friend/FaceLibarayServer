/*==========================================================
* �ļ��� : Server
* ����	 : 2015/9/8
* ����   : ʵ��C++����ʶ�������
* ==========================================================*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include <WINSOCK2.H>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#pragma comment(lib,"ws2_32.lib")

class Server {

public:
	// �˿ں�
	int mPort;
	// ���������
	int mMaxConnectCount;
	// �ͻ������������ʶ��
	char* eof;
	// �ͻ��˽����Ự��ʶ��
	char* quit;
	// Recv��������С
	static const int recvBufferCount = 10000;

public:
	// �ڲ��࣬����Receiver�и���������ʵ�����õ����߿���֮������Ϣ
	class OnSenderHandler {
	public:
		virtual void sendMsg(string msg) = 0;
	};
	// �ڲ��࣬���ͻ��˷�����Ϣʱ�Ľ�������
	class OnReceiverListener {
	public:
		// ���ӽ���ʱ�Ļص��ӿ�
		virtual void started(SOCKADDR_IN clientsocket){};
		// �������ص��ӿ�
		virtual void receive(string msg, OnSenderHandler* sender) = 0;
		// �Ͽ�����ʱ�Ļص��ӿ�
		virtual void stopped(SOCKADDR_IN clientsocket, OnSenderHandler* sender){};
	};

public:
	// Ĭ�Ϲ�����
	Server();
	// ��ʼ����
	void startListen(int _port, int _maxConnectCount, OnReceiverListener* listener);
	// ��������
	void stopListen();
	// ʹ���Զ���ķ��ͺ���������Ϣ
	static int self_send(SOCKET socket, const char* buffer, int len);

private:
	OnReceiverListener* mListener;

private:
	// ʵ�ֵ�OnSenderHandler
	class SenderHandler : public OnSenderHandler{
	public:
		SOCKET serConn;
		void sendMsg(string msg) {
			int success = self_send(serConn, msg.c_str(), msg.length() + 1);
			if (success == -1) {
				cout << "�������ݳ���" << endl;
			}
		}
	};
	SenderHandler mSenderHandler;
};

// Ĭ�Ϲ�����
Server::Server(){
	mPort = 3000;
	mMaxConnectCount = 10;
	eof = ".";
	quit = "quit";
}

int Server::self_send(SOCKET socket, const char* buffer, int len) {
	int bytes_left;
	int written_bytes;
	const char *ptr;

	ptr = buffer;
	bytes_left = len;
	while (bytes_left>0)
	{

		written_bytes = send(socket, ptr, bytes_left, 0);
		if (written_bytes <= 0)
		{
			// ����ΪEINTR(eintr)��ʾ��д��ʱ��������жϴ���
			if (errno == EINTR)
				written_bytes = 0;
			else
				return(-1);
		}
		bytes_left -= written_bytes;
		ptr += written_bytes;
	}
	return(0);
}

void Server::startListen(int _port, int _maxConnectCount,
	OnReceiverListener* listener){
	mPort = _port;
	mMaxConnectCount = _maxConnectCount;
	mListener = listener;
	
	while (1) {
		//�����׽���
		WORD myVersionRequest;
		WSADATA wsaData;                    //����ϵͳ��֧�ֵ�WinStock�汾��Ϣ
		myVersionRequest = MAKEWORD(1, 1);  //��ʼ���汾1.1
		int err;
		err = WSAStartup(myVersionRequest, &wsaData);
		if (!err){
			cout << ("�Ѵ��׽���\n");
		}
		else{
			//��һ�����׽���
			cout << ("�׽���δ��!");
			return;
		}
		SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);//�����˿�ʶ���׽���
		//��Ҫ�󶨵Ĳ���
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip��ַ
		addr.sin_port = htons(this->mPort);//�󶨶˿�
		//���׽��ְ󶨵�ָ���������ַ
		bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//�����
		listen(serSocket, this->mMaxConnectCount);          //�ڶ������������ܹ����յ�����������
		SOCKADDR_IN clientsocket;
		int len = sizeof(SOCKADDR);
		SOCKET serConn;
		//�ȴ��ͻ��˵�����
		serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);
		cout << "�ͻ���" << inet_ntoa(clientsocket.sin_addr) << "������" << endl;
		//�ͻ���������
		if (mListener != NULL) {
			mListener->started(clientsocket);
		}
		// ��ʼ���տͻ��˴�������ݣ�ֱ������������������
		while (1) {
			string msg="";
			//while (1) {
			// ��������Ҫ��ʼ��
			char receiveBuf[recvBufferCount] = {0};
				// ���տͻ��˴�������Ϣ
				int success = recv(serConn, receiveBuf, sizeof(receiveBuf), 0);
				if (success <= 0) {
					// ������Ҫ���մ����봦��
					cout << "�������ݳ���" << endl;
					break;
				}
				
				if (!strcmp(receiveBuf, eof)){
					//�������
					//break;
				}
				msg += receiveBuf;
			//}
			if (mListener != NULL) {
				mSenderHandler.serConn = serConn;
				this->mListener->receive(msg, &mSenderHandler);
			}
			//����ͻ��˴�����quit�źţ������˵ȴ���һ���ͻ���
			if (msg == quit) {
				break;
			}
		}
		cout << "�ͻ���" << inet_ntoa(clientsocket.sin_addr) << "�ѹر�" << endl;
		if (mListener != NULL) {
			this->mListener->stopped(clientsocket, &mSenderHandler);
		}
		closesocket(serConn);   //�ر�
		WSACleanup();           //�ͷ���Դ�Ĳ���
	}
}



#endif


