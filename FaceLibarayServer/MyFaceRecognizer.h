/*===========================================
* �ļ��� : MyFaceRecognizer
* ����	 : 2015/9/6
* ����   : ʵ������ʶ��
* ============================================*/

#ifndef _MYFACERECOGNIZER_H_
#define _MYFACERECOGNIZER_H_
#include <vector>
#include "cv.h"
#include <opencv2/opencv.hpp>  
using std::vector;
using namespace cv;

// ��ǩ����
typedef int Labels;

class MyFaceRecognizer {

public:
	// Ĭ�Ϲ��캯��
	MyFaceRecognizer();

public:
	// �洢������
	void save(const char* filename);
	// װ��������
	void load(const char* filename);
	// ���������Ϣ
	void add(vector<Mat> faces, vector<Labels> labels);
	// ѵ��ϵͳ
	void train(vector<Mat> faces, vector<Labels> labels);
	// ����ʶ��
	Labels predict(Mat img);
	// ��ȡ��ʱ��������·��
	string getFilePath();

private:
	string filename;				// ������·��
	Ptr<FaceRecognizer> model;		// ʶ����

};


#endif
