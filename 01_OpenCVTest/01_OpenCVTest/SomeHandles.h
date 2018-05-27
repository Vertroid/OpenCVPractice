#pragma once

#include <opencv2\opencv.hpp>

#ifndef _SOME_HANDLES_H_
#define _SOME_HANDLES_H_

extern IplImage* doPyrDown(IplImage* in, int filter = CV_GAUSSIAN_5x5);
extern IplImage* doCanny(IplImage* in, double lowT, double highT, double aperture);
extern float sum();
extern void saturate_sv(IplImage* in);
extern void save_xml();
extern void save_fileStorage();
extern void load_fileStorage();

#endif