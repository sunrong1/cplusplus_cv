#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main()
{
	//Mat是作为OpenCV2新纪元的重要代表“人物”,
	//它是对应于OpenCV1.0时代的IplImage的主要用来存放图像的数据结构
	Mat imageOriginal=imread("girl.jpg");//默认1
	//namewindow与imshow两者需要对应
	namedWindow("I love");
	imshow("I love",imageOriginal);
	
	Mat Me=imread("me.bmp",199);
	Mat imageMove=imread("gaara.jpg");

	namedWindow("myself");
	imshow("myself",Me);
	namedWindow("I like");
	imshow("I like",imageMove);

	Mat imageROI;
	imageROI=imageOriginal(Rect(400,30,Me.cols,Me.rows)); //定义一个感兴趣区域
	double alphaValue = 0.5;  
	double betaValue;  
	betaValue = ( 1.0 - alphaValue ); 
	addWeighted(imageROI,alphaValue,Me,betaValue,0,imageROI);//图像融合 dst = src1[I]*alpha+ src2[I]*beta + gamma;
	//将原图与掩码图进行与或运算通过像素值0、1来决定那部分绘制到屏幕，那部分不绘
	/*Mat mask=imread("me.bmp",0);
	Me.copyTo(imageROI,mask);
	namedWindow("mask");
	imshow("mask",mask);*/
	namedWindow("Final");
	imshow("Final",imageOriginal);
	waitKey();
	return 0;
}