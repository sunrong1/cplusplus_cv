/*
OpenCV提供了一些基本的绘图操作，
比如画圆，画椭圆，画线，画矩形，在图像里插入文字等功能。
*/
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat image=imread("you1.jpg");


	Point center = Point(255,255);	//圆心
	int r = 100; 	//半径
	//参数为：承载的图像、圆心、半径、颜色、粗细、线型
	circle(image,center,r,Scalar(255,0,0));
	imshow("circle",image);

	Rect found(10,10,100,200); 
	// tl:the top-left corner,br: the bottom-right corner,
	//参数为：承载的图像、顶点、对角点、颜色（蓝绿红）、粗细、大小  
	rectangle(image,found.tl(),found.br(),Scalar(200,255,255),3);

	Rect found_com(20,20,50,50);
	if ((found & found_com)==found_com)
	{
		cout<<"There are common"<<endl;
	}
	//Point add=Point(50,50);
	//found=found+add; //平移操作

	//rectangle(image,found.tl(),found.br(),Scalar(0,0,200),4);
	//Size scale=Size(100,100);
	//found=found+scale; //缩放操作
	//rectangle(image,found.tl(),found.br(),Scalar(0,0,200),4);

	found=found | found_com;

	rectangle(image,found.tl(),found.br(),Scalar(0,255,0),4);
	cout<<found_com.size()<<endl;

	namedWindow("Naruto");
	imshow("Naruto",image);
	waitKey();

	return 0;
}