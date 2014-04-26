//#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
void vetRectImageShow(vector<Rect> &vec, Mat &img,Scalar &color_rect);
int rightDetectNum=0;
int notDetectNum=0;
int falseDetectNum=0;
float areaScore=0;
Scalar color[3]={Scalar(255,0,0),Scalar(0,255,0),Scalar(0,0,255)};
int main()
{
	ifstream in("myname.txt");
	float num=0;
	float acc[4];
	vector<Rect> vecRectA;
	vector<Rect> vecRectB;
	Rect rectA;
	Mat imgA=imread("tud0.png");
	//Mat imgB=imread("tud0.png");
	while (!in.eof())
	{
		for (int i=0;i<4;++i)
		{
			in>>acc[i];
		}
		//for (int i=0;i<4;++i)
		//{
		//	cout<<acc[i]<<",";
		//}
		//cout<<endl;
		rectA=Rect(acc[0],acc[1],acc[2],acc[3]);
		vecRectA.push_back(rectA);
		//cout<<"rectA:"<<rectA<<endl;			
	}
	
		
	ifstream inB("myname1.txt");
	Rect rectB;
	while (!inB.eof())
	{
		for (int i=0;i<4;++i)
		{
			inB>>acc[i];
		}
		
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
		//for (int i=0;i<4;++i)
		//{
		//	cout<<acc[i]<<",";
		//}
		//cout<<endl;
		acc[2]=acc[2]-acc[0];
		acc[3]=acc[3]-acc[1];
		//rectB(217,208,-55,143);//rect中允许有负值
		rectB=Rect(acc[0],acc[1],acc[2],acc[3]);
		vecRectB.push_back(rectB);
		cout<<"rectB:"<<rectB<<endl;	
	}
	vetRectImageShow(vecRectA, imgA,color[1]);
	vetRectImageShow(vecRectB, imgA,color[2]);
	
	Rect rectC;
	for(int i=0;i<vecRectB.capacity();++i)
	{
		float area;
		int score;
		for(int detectnum=0;detectnum<vecRectA.capacity();++detectnum)
		{
			rectC=vecRectB.at(i) & vecRectA.at(detectnum);//"|"包含r1r2的最小矩形 opencv的bug，&重载是数值必须为正。
			area=rectC.area();
			
			if (area>0)
			{ 
				areaScore=area/(vecRectB.at(i).area()+vecRectA.at(detectnum).area()-area);
				if (areaScore>=0.5)
				{
					rightDetectNum++;
					cout<<"the area of overlap is :"<<area<<"and score is:"<<areaScore<<endl;
				}
			}	
		}
	}
	cout<<"the right detection number is:"<<rightDetectNum<<endl;
    //rectC=vecRectA.at(0)& vecRectB.at(3);//"|"包含r1r2的最小矩形 opencv的bug，&重载是数值必须为正。
	//Rect rectD=vecRectA.at(0)& vecRectB.at(3);//简单的方法，是对数据调整。
	//cout<<rectC<<endl;

	//rectangle(imgB,rectC.tl(),rectC.br(),Scalar(0,255,255),1);
	
//	rectangle(imgB,rectD.tl(),rectD.br(),Scalar(0,255,0),1);
	imshow("tud0_bak",imgB);
	imwrite("tud0_detect_my.png",imgA);
	waitKey();
	return 0;
}
void vetRectImageShow(vector<Rect> &vec, Mat &img,Scalar &color_rect)
{
	cout<<vec.capacity()<<":many"<<endl;
	Rect rect;
	for(int i=0;i<vec.capacity();++i)
	{
		rect=vec.at(i);
		rectangle(img,rect.tl(),rect.br(),color_rect,2);
	}
	imshow("tud0",img);
}