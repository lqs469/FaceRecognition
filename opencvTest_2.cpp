// opencvTest_2.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace cv;
using namespace std;

static CvMemStorage* storage            = NULL;
static CvHaarClassifierCascade* cascade = NULL;
const char* cascadePath                 = "C:\\opencv\\sources\\data\
\\haarcascades\\haarcascade_frontalface_alt_tree.xml";

int _tmain(int argc, _TCHAR* argv[])
{
    /***********初始化一个摄像头捕捉器***********/
    CvCapture* capture = cvCreateCameraCapture(0);
    cvNamedWindow("Camera");

    /***********初始化人脸检测相关变量***********/
    IplImage* cameraImage = NULL;
    storage = cvCreateMemStorage(0);
    cascade = (CvHaarClassifierCascade*)cvLoad(cascadePath);

    while ((cameraImage = cvQueryFrame(capture)) != NULL)
    {
        //cvShowImage("Camera",cameraImage);
        cvWaitKey(1);

        /**********灰度化***********/
        IplImage* grayImage = cvCreateImage(cvSize(cameraImage -> width, cameraImage -> height), 8, 1);
        cvCvtColor(cameraImage, grayImage, CV_BGR2GRAY);

        /**********人脸检测***********/
        cvClearMemStorage(storage);
        CvSeq* objects = cvHaarDetectObjects(grayImage, cascade, storage, 1.1,2,0, cvSize(30,30));

        /**********绘制检测结果***********/
        for (int i = 0; i < (objects ? objects -> total : 0); i++){
            CvRect* rect = (CvRect*)cvGetSeqElem(objects,i);
            cvRectangle(cameraImage, cvPoint(rect->x, rect->y),
                cvPoint(rect -> x + rect -> width, rect -> y + rect -> height), cvScalar(0.0, 255));
        }
        cvShowImage("Camera",cameraImage);
    }
    return 0;
}
