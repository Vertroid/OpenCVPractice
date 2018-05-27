#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include "SomeHandles.h"
#include "ChapterTests.h"

using namespace std;
using namespace cv;

extern void display1();
extern void display2();
extern void display3();
extern void displayROI();
extern void displayROI2();
extern void displayVideo();
extern void writeVideo();
extern void displaySmooth();
extern void displayHandle();
extern void OnTrackbarSlider(int pos);

int g_slider_position = 0;
CvCapture* g_capture = NULL;

int main() 
{
	test104_6();
}

void display1()
{
	IplImage* img = cvLoadImage("C:\Sakamoto.jpg");
	cvNamedWindow("Example", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Exmpale");

}

void display2()
{
	Mat image = imread("C:/Sakamoto.jpg");
	imshow("Image", image);
	waitKey(0);
}

void display3() {
	IplImage* img = cvLoadImage("C:/Sakamoto.jpg");
	saturate_sv(img);
	cvNamedWindow("SATURATE", CV_WINDOW_AUTOSIZE);
	cvShowImage("SATURATE", img);
	cout << "widthStep: " << img->widthStep << endl;
	cout << "width: " << img->width << endl;
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("SATURATE");
}

void displayROI() {
	IplImage* img = cvLoadImage("C:/Girl.jpg");
	int x = 50, y = 50, width = 50, height = 50;
	//cvSetImageROI(img, cvRect(x, y, width, height));
	cvAddS(img, cvScalar(100), img);
	//cvResetImageROI(img);
	cvNamedWindow("ROI");
	cvShowImage("ROI", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyAllWindows();
}

void displayROI2() {
	IplImage* img = cvLoadImage("C:/Girl.jpg");
	CvRect roi_rect = cvRect(0, 0, 200, 200);
	IplImage* sub_img = cvCreateImageHeader(cvSize(roi_rect.width, roi_rect.height), img->depth, img->nChannels);
	sub_img->origin = img->origin;
	sub_img->widthStep = img->widthStep;
	sub_img->imageData = img->imageData + roi_rect.y * img->widthStep + roi_rect.x * img->nChannels;
	cvAddS(img, cvScalar(100), img);
	cvNamedWindow("ROI2-A", CV_WINDOW_AUTOSIZE);
	cvShowImage("ROI2-A", img);
	cvNamedWindow("ROI2-B", CV_WINDOW_AUTOSIZE);
	cvShowImage("ROI2-B", sub_img);
	cvWaitKey(0);
	cvReleaseImageHeader(&sub_img);
	cvReleaseImage(&img);
	cvDestroyAllWindows();
}

void displayVideo()
{
	cvNamedWindow("Video", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture("C:/Nature.avi");
	int frames = (int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	if (frames != 0)
	{
		cvCreateTrackbar("Trackbar", "Video", &g_slider_position, frames, OnTrackbarSlider);
	}
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(g_capture);
		if (!frame)
			break;
		cvShowImage("Video", frame);
		char c = cvWaitKey(33);
		if (c == 27)
			break;
	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("Video");
}

void writeVideo() 
{
	CvCapture* capture = NULL;
	capture = cvCreateFileCapture("C:/Nature.avi");
	if (!capture)
	{
		return;
	}
	cvNamedWindow("OUTPUT", CV_WINDOW_AUTOSIZE);
	IplImage* bgr_frame = cvQueryFrame(capture);
	double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	CvSize size = cvSize((int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH)/2, (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT)/2);
	CvVideoWriter* writer = cvCreateVideoWriter("F:/AnotherNature.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, size);
	IplImage* logpolar_frame = cvCreateImage(size, bgr_frame->depth, 3);

	int count = 0;
	while ((bgr_frame = cvQueryFrame(capture)) != NULL)
	{
		//cvLogPolar(bgr_frame, logpolar_frame, cvPoint2D32f(bgr_frame->width / 2, bgr_frame->height / 2), 40, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
		//logpolar_frame = cvCreateImage(cvSize(bgr_frame->width/2, bgr_frame->height/2), bgr_frame->depth, bgr_frame->nChannels);
		cvPyrDown(bgr_frame, logpolar_frame, CV_GAUSSIAN_5x5);
		cvShowImage("OUTPUT", logpolar_frame);
		cvWaitKey(33);
		//cvCanny(bgr_frame, logpolar_frame, 10, 100, 3);
		//cvWriteFrame(writer, logpolar_frame);

		//cout << count++ << " "<< logpolar_frame->width << endl;
	}
	cout << "Write Complete." << endl;
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&logpolar_frame);
	cvReleaseCapture(&capture);

	return;
}

void displayHandle()
{
	IplImage* image = cvLoadImage("C:/Girl.jpg");
	image = doPyrDown(image, CV_GAUSSIAN_5x5);
	image = doCanny(image, 2, 10, 3);
	cvNamedWindow("Handle", CV_WINDOW_AUTOSIZE);
	cvShowImage("Handle", image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyWindow("Handle");
	return;
}

void displaySmooth()
{
	// display first image 
	IplImage* image = cvLoadImage("C:/Girl.jpg");
	cvNamedWindow("IN");
	cvNamedWindow("OUT");
	cvShowImage("IN", image);

	IplImage* out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvSmooth(image, out, CV_GAUSSIAN, 3, 3);
	cvShowImage("OUT", out);
	cvWaitKey(0);
	cvReleaseImage(&out);
	cvReleaseImage(&image);
	cvDestroyWindow("IN");
	cvDestroyWindow("OUT");
}

void OnTrackbarSlider(int pos)
{
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos); // ÉèÖÃÊôÐÔ
}
