
#include "Util.h"
#include "highgui.h"
void _1() {

	IplImage* img = cvLoadImage("person1/p4.jpg");
	Util util;
	// IplImageת��ΪMat
	Mat mat = util.iplImageToMat(img);

	// �ٽ�Matת��ΪIplImage
	IplImage img2 = util.matToIplImage(&mat);

	char* w1 = "ԭIplImage";
	char* w2 = "ת��������Mat";
	char* w3 = "��ת��������IplImage";
	// ��ʾIplImage
	cvNamedWindow(w1);
	cvShowImage(w1, img);

	// ��ʾMat
	namedWindow(w2);
	imshow(w2, mat);

	// ��ʾ��ת������IplImage
	cvNamedWindow(w3);
	cvShowImage(w3, &img2);

	cvWaitKey();
	cvDestroyWindow(w1);
	destroyWindow(w2);
	cvDestroyWindow(w3);
}


