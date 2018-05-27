#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void test104_2() 
{
	CvMat* mat = cvCreateMat(100, 100, CV_8SC3);
	cvZero(mat);
	cvCircle(mat, cvPoint(50, 50), 30, cvScalar(200, 100, 50), 2, 8, 0);

	cvNamedWindow("TEST104_2", CV_WINDOW_AUTOSIZE);
	cvShowImage("TEST104_2", mat);
	cvWaitKey(0);
	cvReleaseMat(&mat);
	cvDestroyAllWindows();
}

void test104_3() 
{
	CvMat* mat = cvCreateMat(100, 100, CV_8SC3);
	cvZero(mat);
	for (int x = 20; x <= 40; x++) 
	{
		for (int y = 5; y <= 20; y++)
		{
			*(cvPtr2D(mat, x, y) + 1) = 127;
		}
	}
	
	cvNamedWindow("TEST104_3", CV_WINDOW_AUTOSIZE);
	cvShowImage("TEST104_3", mat);
	cvWaitKey(0);
	cvReleaseMat(&mat);
	cvDestroyAllWindows();
}

void test104_4()
{
	CvMat* mat = cvCreateMat(100, 100, CV_8UC3);
	cvZero(mat);
	char c;
	cout << mat->cols << endl;
	cout << mat->step << endl;
	for (int i = 5; i <= 20; i++)
	{
		for (int j = 20; j <= 40; j++)
		{
			*(mat->data.ptr + i*mat->step + j) = 255;
		}
	}

	cvNamedWindow("TEST104_4", CV_WINDOW_AUTOSIZE);
	cvShowImage("TEST104_4", mat);
	cvWaitKey(0);
	cvReleaseMat(&mat);
	cvDestroyAllWindows();
}

void test104_5()
{
	IplImage* image = cvCreateImage(cvSize(210, 210), IPL_DEPTH_8U, 1);
	cvZero(image);
	int width = 0;
	// cvSet(image, 120, NULL);
	_IplROI roi;
	roi.coi = 1;
	roi.width = 100;
	roi.height = 100;
	roi.xOffset = 10;
	roi.yOffset = 10;
	image->roi = &roi;

	cvNamedWindow("TEST104_5", CV_WINDOW_AUTOSIZE);
	cvShowImage("TEST104_5", image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyAllWindows();
}

void test104_6()
{
	IplImage* image = cvLoadImage("C:/Girl.jpg");
	IplImage* h1 = cvCreateImageHeader(cvSize(200, 300), image->depth, image->nChannels);
	IplImage* h2 = cvCreateImageHeader(cvSize(200, 300), image->depth, image->nChannels);
	
	h1->imageData = (image->imageData + 10*image->widthStep + 5*image->nChannels);
	h2->imageData = (image->imageData + 350*image->widthStep + 250*image->nChannels);
	
	for (int i = 0; i <= 300; i++)
	{
		for (int j = 0; j <= 200; j++)
		{
			*(image->imageData + (10 + i)*image->widthStep + (5 + j)*image->nChannels) = ~*(h1->imageData + i*image->widthStep + j*image->nChannels);
			*(image->imageData + (10 + i)*image->widthStep + (5 + j)*image->nChannels + 1) = ~*(h1->imageData + i*image->widthStep + j*image->nChannels + 1);
			*(image->imageData + (10 + i)*image->widthStep + (5 + j)*image->nChannels + 2) = ~*(h1->imageData + i*image->widthStep + j*image->nChannels + 2);
			*(image->imageData + (10 + i)*image->widthStep + (5 + j)*image->nChannels + 3) = ~*(h1->imageData + i*image->widthStep + j*image->nChannels + 3);
			
		}
	}
	for (int i = 0; i <= 300; i++)
	{
		for (int j = 0; j <= 200; j++)
		{
			*(image->imageData + (350 + i)*image->widthStep + (250 + j)*image->nChannels) = ~*(h2->imageData + i*image->widthStep + j*image->nChannels);
			*(image->imageData + (350 + i)*image->widthStep + (250 + j)*image->nChannels + 1) = ~*(h2->imageData + i*image->widthStep + j*image->nChannels + 1);
			*(image->imageData + (350 + i)*image->widthStep + (250 + j)*image->nChannels + 2) = ~*(h2->imageData + i*image->widthStep + j*image->nChannels + 2);
			*(image->imageData + (350 + i)*image->widthStep + (250 + j)*image->nChannels + 3) = ~*(h2->imageData + i*image->widthStep + j*image->nChannels + 3);
		}
	}

	cvNamedWindow("TEST104_6", CV_WINDOW_AUTOSIZE);
	cvShowImage("TEST104_6", image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&h1);
	cvReleaseImage(&h2);
	cvDestroyAllWindows();
}