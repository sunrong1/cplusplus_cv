//#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
void vetRectImageShow(vector<Rect> &vec, Mat &img);
int main()
{
	ifstream in("myname.txt");
	float num=0;
	float acc[4];
	vector<Rect> vecRectA;
	vector<Rect> vecRectB;
	Rect rectA;
	Mat imgA=imread("tud0.png");
	Mat imgB=imread("tud0.png");
	while (!in.eof())
	{
		for (int i=0;i<4;++i)
		{
			in>>acc[i];
		}
		for (int i=0;i<4;++i)
		{
			cout<<acc[i]<<",";
		}
		cout<<endl;
		rectA=Rect(acc[0],acc[1],acc[2],acc[3]);
		vecRectA.push_back(rectA);
		cout<<"rectA:"<<rectA<<endl;			
	}
	
		
	ifstream inB("myname1.txt");
	Rect rectB;
	while (!inB.eof())
	{
		for (int i=0;i<4;++i)
		{
			inB>>acc[i];
		}
		for (int i=0;i<4;++i)
		{
			cout<<acc[i]<<",";
		}
		cout<<endl;
		
		int temp=0;
		if (acc[2]-acc[0]<0)
		{
			if (acc[3]-acc[1]<0)
			{
				temp=acc[0];
				acc[0]=acc[2];
				acc[2]=temp;
				temp=acc[1];
				acc[1]=acc[3];
				acc[3]=temp;
			}
			else
			{
				temp=acc[0];
				acc[0]=acc[2];
				acc[2]=temp;
			}
		}
		else
			if (acc[3]-acc[1]<0)
			{
				temp=acc[1];
				acc[1]=acc[3];
				acc[3]=temp;
			}
		acc[2]=acc[2]-acc[0];
		acc[3]=acc[3]-acc[1];
		//rectB(217,208,-55,143);//rect中允许有负值
		rectB=Rect(acc[0],acc[1],acc[2],acc[3]);
		vecRectB.push_back(rectB);
		cout<<"rectB:"<<rectB<<endl;	
	}
	vetRectImageShow(vecRectA, imgA);
	vetRectImageShow(vecRectB, imgB);
	
	rectA=vecRectA.at(0);
	rectangle(imgB,rectA.tl(),rectA.br(),Scalar(255,0,0),2);
	rectB=vecRectB.at(3);
	rectangle(imgB,rectB.tl(),rectB.br(),Scalar(0,0,255),2);

	Rect rectC=vecRectA.at(0)& vecRectB.at(3);//"|"包含r1r2的最小矩形 opencv的bug，&重载是数值必须为正。
	//Rect rectD=vecRectA.at(0)& vecRectB.at(3);//简单的方法，是对数据调整。
	cout<<rectC<<endl;

	rectangle(imgB,rectC.tl(),rectC.br(),Scalar(0,255,255),1);
	if (rectC.area()>0)
	{ 
		cout<<"the area of overlap is :"<<rectC.area()<<endl;
		cout<<"the score is:"<<(double)rectC.area()/(rectA.area()+rectB.area()-rectC.area())<<endl;
	}
//	rectangle(imgB,rectD.tl(),rectD.br(),Scalar(0,255,0),1);
	imshow("tud0_bak",imgB);
	imwrite("tud0_detect_my.png",imgA);
	waitKey();
	return 0;
}
void vetRectImageShow(vector<Rect> &vec, Mat &img)
{
	cout<<vec.capacity()<<":many"<<endl;
	Rect rect;
	for(int i=0;i<vec.capacity();++i)
	{
		rect=vec.at(i);
		rectangle(img,rect.tl(),rect.br(),Scalar(255,0,0),2);
	}
	imshow("tud0",img);
}