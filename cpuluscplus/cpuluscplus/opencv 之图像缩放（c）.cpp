//ֽ���Ŀ�����
#include <iostream>
#include "StdAfx.h"
#include <opencv2/opencv.hpp>
using namespace std;
int main()
{
	const char *pstrImageName="girl.jpg";          //ͼ�����Ƶ�ָ������
	const char *pstrSaveImageName="girl_scale.jpg";
	const char *pstrWindowsSrcTitle="The original image";//����ָ������
	const char *pstrWindowsDstTitle="Scaled image";

	double fScale=0.314;
	CvSize whSize;   //������ȡ��߶�
	//IplImage�ṹ��������OpenCV������Ļ������ڶ���ýṹ����ʱ��Ҫ�õ�����cvCreatImage cvLoadImage
	IplImage *pSrcImage= cvLoadImage(pstrImageName,CV_LOAD_IMAGE_UNCHANGED); //����Դͼ�����ƶ�ȡ��ȡԴͼ��
	IplImage *PDstImage=NULL;

	whSize.width=pSrcImage->width*fScale;
	whSize.height=pSrcImage->height*fScale;
	//��ɫ�����ָ����ͨ�������ݱ���Ϊ�ı������ͣ�����RGB24��ʽ�����ݣ�ͨ����Ϊ3����ɫ���ΪIPL_DEPTH_8U
	PDstImage=cvCreateImage(whSize,pSrcImage->depth,pSrcImage->nChannels);  //�������� ��ͼ��ߴ硢ͼ��ͨ����
	cvResize(pSrcImage,PDstImage,CV_INTER_AREA); //�߶ȱ仯 ��ʽ

	cvNamedWindow(pstrWindowsSrcTitle,CV_WINDOW_AUTOSIZE);   //��������
	cvNamedWindow(pstrWindowsDstTitle,CV_WINDOW_AUTOSIZE);

	cvShowImage(pstrWindowsSrcTitle,pSrcImage);  //�ڴ�������ʾ��ʾͼƬ����
	cvShowImage(pstrWindowsDstTitle,PDstImage);

	cvWaitKey(); //�ȴ������¼�

	cvSaveImage(pstrSaveImageName,PDstImage); //����ͼƬ

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsDstTitle);
	cvReleaseImage(&pSrcImage);  //�ͷ�IPLͼ��ͷ������
	cvReleaseImage(&PDstImage);

	return 0;

}