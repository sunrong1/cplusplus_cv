#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main()
{
	//Mat����ΪOpenCV2�¼�Ԫ����Ҫ�������,
	//���Ƕ�Ӧ��OpenCV1.0ʱ����IplImage����Ҫ�������ͼ������ݽṹ
	Mat imageOriginal=imread("girl.jpg");//Ĭ��1
	//namewindow��imshow������Ҫ��Ӧ
	namedWindow("I love");
	imshow("I love",imageOriginal);
	
	Mat Me=imread("me.bmp",199);
	Mat imageMove=imread("gaara.jpg");

	namedWindow("myself");
	imshow("myself",Me);
	namedWindow("I like");
	imshow("I like",imageMove);

	Mat imageROI;
	imageROI=imageOriginal(Rect(400,30,Me.cols,Me.rows)); //����һ������Ȥ����
	double alphaValue = 0.5;  
	double betaValue;  
	betaValue = ( 1.0 - alphaValue ); 
	addWeighted(imageROI,alphaValue,Me,betaValue,0,imageROI);//ͼ���ں� dst = src1[I]*alpha+ src2[I]*beta + gamma;
	//��ԭͼ������ͼ�����������ͨ������ֵ0��1�������ǲ��ֻ��Ƶ���Ļ���ǲ��ֲ���
	/*Mat mask=imread("me.bmp",0);
	Me.copyTo(imageROI,mask);
	namedWindow("mask");
	imshow("mask",mask);*/
	namedWindow("Final");
	imshow("Final",imageOriginal);
	waitKey();
	return 0;
}