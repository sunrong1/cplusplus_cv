//纸包的口香糖
#include <iostream>
#include "StdAfx.h"
#include <opencv2/opencv.hpp>
using namespace std;
int main()
{
	const char *pstrImageName="girl.jpg";          //图像名称的指针数组
	const char *pstrSaveImageName="girl_scale.jpg";
	const char *pstrWindowsSrcTitle="The original image";//标题指针数组
	const char *pstrWindowsDstTitle="Scaled image";

	double fScale=0.314;
	CvSize whSize;   //包含宽度、高度
	//IplImage结构体是整个OpenCV函数库的基础，在定义该结构变量时需要用到函数cvCreatImage cvLoadImage
	IplImage *pSrcImage= cvLoadImage(pstrImageName,CV_LOAD_IMAGE_UNCHANGED); //根据源图像名称读取获取源图像
	IplImage *PDstImage=NULL;

	whSize.width=pSrcImage->width*fScale;
	whSize.height=pSrcImage->height*fScale;
	//颜色深度是指单个通道的数据保存为的变量类型，例如RGB24格式的数据，通道数为3，颜色深度为IPL_DEPTH_8U
	PDstImage=cvCreateImage(whSize,pSrcImage->depth,pSrcImage->nChannels);  //三个参数 ，图像尺寸、图像通道数
	cvResize(pSrcImage,PDstImage,CV_INTER_AREA); //尺度变化 方式

	cvNamedWindow(pstrWindowsSrcTitle,CV_WINDOW_AUTOSIZE);   //创建窗口
	cvNamedWindow(pstrWindowsDstTitle,CV_WINDOW_AUTOSIZE);

	cvShowImage(pstrWindowsSrcTitle,pSrcImage);  //在窗口中显示显示图片内容
	cvShowImage(pstrWindowsDstTitle,PDstImage);

	cvWaitKey(); //等待按键事件

	cvSaveImage(pstrSaveImageName,PDstImage); //保存图片

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsDstTitle);
	cvReleaseImage(&pSrcImage);  //释放IPL图像头和数据
	cvReleaseImage(&PDstImage);

	return 0;

}