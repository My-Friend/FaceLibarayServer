/*==========================================================
* �ļ��� : Util
* ����	 : 2015/9/7
* ����   : ʵ��һЩ���ߺ�������Mat��IplImage���໥ת����
* ==========================================================*/

#include "cv.h"
using namespace cv;

#ifndef _UTIL_H_
#define _UTIL_H_

class Util {
public:
	// Matת��ΪIplImage
	static IplImage matToIplImage(Mat* mat);

	// IplImageת��ΪMat
	static Mat iplImageToMat(IplImage* img);

};

IplImage Util::matToIplImage(Mat* mat){
	return IplImage(*mat);
}

Mat Util::iplImageToMat(IplImage* img) {
	return Mat(img, true);
}

#endif
