// opencvTest_2.cpp : �������̨Ӧ�ó������ڵ㡣
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
    /***********��ʼ��һ������ͷ��׽��***********/
    CvCapture* capture = cvCreateCameraCapture(0);
    cvNamedWindow("Camera");

    /***********��ʼ�����������ر���***********/
    IplImage* cameraImage = NULL;
    storage = cvCreateMemStorage(0);
    cascade = (CvHaarClassifierCascade*)cvLoad(cascadePath);

    while ((cameraImage = cvQueryFrame(capture)) != NULL)
    {
        //cvShowImage("Camera",cameraImage);
        cvWaitKey(1);

        /**********�ҶȻ�***********/
        IplImage* grayImage = cvCreateImage(cvSize(cameraImage -> width, cameraImage -> height), 8, 1);
        cvCvtColor(cameraImage, grayImage, CV_BGR2GRAY);

        /**********�������***********/
        cvClearMemStorage(storage);
        CvSeq* objects = cvHaarDetectObjects(grayImage, cascade, storage, 1.1,2,0, cvSize(30,30));

        /**********���Ƽ����***********/
        for (int i = 0; i < (objects ? objects -> total : 0); i++){
            CvRect* rect = (CvRect*)cvGetSeqElem(objects,i);
            cvRectangle(cameraImage, cvPoint(rect->x, rect->y),
                cvPoint(rect -> x + rect -> width, rect -> y + rect -> height), cvScalar(0.0, 255));
        }
        cvShowImage("Camera",cameraImage);
    }
    return 0;
}
