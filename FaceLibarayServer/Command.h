/*==========================================================
* �ļ��� : Command
* ����	 : 2015/9/8
* ����   : �ṩ��ͻ��˽���ʱָ��������
* ==========================================================*/

#ifndef _COMMAND_H_
#define _COMMAND_H_

class Command {
public:
	// �����������������
	static const char* ADD;
	// ʶ������
	static const char* PREDICT;
	// �ر�����
	static const char* CLOSE;

};

const char* Command::ADD = "add";
const char* Command::PREDICT = "predict";
const char* Command::CLOSE = "close";

#endif


