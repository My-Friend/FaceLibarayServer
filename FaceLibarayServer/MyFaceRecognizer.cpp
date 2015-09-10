
#include "MyFaceRecognizer.h"

// Ĭ�Ϲ��캯��
MyFaceRecognizer::MyFaceRecognizer() {
	// ����ʶ����
	model = createLBPHFaceRecognizer(1, 8, 8, 8, 60);
}

// �洢������
void MyFaceRecognizer::save(const char* filename) {
	this->filename = filename;
	model->save(filename);
}

// װ��������
void MyFaceRecognizer::load(const char* filename) {
	this->filename = filename;
	model->load(filename);
}

// ���������Ϣ
void MyFaceRecognizer::add(vector<Mat> faces, vector<Labels> labels) {
	model->update(faces, labels);
	model->save(this->filename);
}

// ѵ��ϵͳ
void MyFaceRecognizer::train(vector<Mat> faces, vector<Labels> labels) {
	model->train(faces, labels);
}

// ����ʶ��
Labels MyFaceRecognizer::predict(Mat img) {
	return model->predict(img);
}


// ��ȡ��ʱ��������·��
string MyFaceRecognizer::getFilePath() {
	return this->filename;
}






