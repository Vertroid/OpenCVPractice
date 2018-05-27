#include "SomeHandles.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>

using std::cout;
using std::endl;

IplImage* doPyrDown(IplImage* in, int filter)
{
	assert(in->width % 2 == 0 && in->height % 2 == 0);
	IplImage* out = cvCreateImage(cvSize(in->width / 2, in->height / 2), in->depth, in->nChannels);
	cvPyrDown(in, out, filter);
	return out;
}

IplImage* doCanny(IplImage* in, double lowT, double highT, double aperture)
{
	if (in->nChannels != 1)
		return 0;
	IplImage* out = cvCreateImage(cvSize(in->width, in->height), IPL_DEPTH_8U, 1);
	cvCanny(in, out, lowT, highT, aperture);
	return out;
}

float sum() {
	float s = 0.0f;
	CvMat* mat = cvCreateMat(3, 3, CV_32FC1);
	for (int row = 0; row < mat->rows; row++) {
		float* ptr = (float*)(mat->data.ptr + row * mat->step); // 通过指针加减获取元素位置
		for (int col = 0; col < mat->cols; col++) {
			*ptr = 3.0f;
			ptr++;
		}
	}
	for (int row = 0; row < mat->rows; row++) {
		const float* ptr = (const float*)(mat->data.ptr + row * mat->step); // 通过指针加减获取元素位置
		for (int col = 0; col < mat->cols; col++) {
			s += *ptr++;
		}
	}
	return s;
}

void saturate_sv(IplImage* img) {
	for (int y = 0; y < img->height; y++) {
		uchar* ptr = (uchar*)(img->imageData + y * img->widthStep); // 每一行开始的位置
		for (int x = 0; x < img->width; x++) {
			ptr[3 * x + 1] = 255;
		}
	}
}

void save_xml() {
	CvMat* mat = cvCreateMat(5, 5, CV_32FC1);
	cvZero(mat);
	float* ptr = (float*)(mat->data.ptr);
	*ptr = 3.0f;
	cvSave("my_matrix.xml", mat);
	cout << "Matrix saved." << endl;
}

void save_fileStorage() {
	CvFileStorage* fs = cvOpenFileStorage("my_config.yaml", 0, CV_STORAGE_WRITE);
	cvWriteInt(fs, "frame_count", 10);
	cvWriteInt(fs, "frame_count", 20);
	cvWriteInt(fs, "frame_count", 30);
	cvStartWriteStruct(fs, "frame_size", CV_NODE_SEQ);
	cvWriteInt(fs, 0, 320);
	cvWriteInt(fs, 0, 240);
	cvWriteInt(fs, 0, 480);
	cvEndWriteStruct(fs);
	cvReleaseFileStorage(&fs);
	cout << "Config saved." << endl;
}

void load_fileStorage() {
	CvFileStorage* fs = cvOpenFileStorage("my_config.xml", 0, CV_STORAGE_READ);
	CvSeq* s = cvGetFileNodeByName(fs, 0, "frame_size")->data.seq;
	int count = cvReadIntByName(fs, 0, "frame_count", 99);
	int width = cvReadInt((CvFileNode*)cvGetSeqElem(s, 0));
	int height = cvReadInt((CvFileNode*)cvGetSeqElem(s, 1));
	cout << width << " " << height <<" "<<count<< endl;
}

void module_info() {
	char* libraries;
	char* modules;
}

