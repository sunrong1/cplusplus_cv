//#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main()
{
	ifstream in("myname.txt");
	float num=0;
	float acc[4];
	vector<Rect> vecRect;
	Rect rectA;
	Mat imgA=imread("tud0.png");
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
		vecRect.push_back(rectA);
		cout<<"rectA:"<<rectA<<endl;			
	}
	cout<<vecRect.capacity()<<"many"<<endl;

	for(int i=0;i<vecRect.capacity();++i)
	{
		rectA=vecRect.at(i);
		rectangle(imgA,rectA.tl(),rectA.br(),Scalar(255,0,0),2);
	}
		
	imshow("show",imgA);
	waitKey(100);	
	imwrite("tud0_detect_std.png",imgA);
	ifstream inB("myname1.txt");
	Mat imgB=imread("tud0_bak.png");
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
		acc[2]=abs(acc[2]-acc[0]);
		acc[3]=abs(acc[3]-acc[1]);
		Rect rectB(acc[0],acc[1],acc[2],acc[3]);;
		cout<<"rectB:"<<rectB<<endl;
		rectangle(imgB,rectB.tl(),rectB.br(),Scalar(0,255,0),2);
		imshow("tud0",imgB);
		waitKey(10);
	}
	imwrite("tud0_detect_my.png",imgB);
	waitKey();
	return 0;
}