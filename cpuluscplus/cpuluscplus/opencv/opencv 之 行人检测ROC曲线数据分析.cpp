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
//int rightDetectNum=0;
//int trueNegative=0;
//float notDetectRatio=0;//漏检率
//float FPPW=0;
//int falseDetectNum=0;
//int overlapFlag=0;
//float areaScore=0;
//int positive=0;
float thresholdScore=0.24;//0.34
Scalar color[3]={Scalar(255,0,0),Scalar(0,255,0),Scalar(0,0,255)};
int main()
{
	for (thresholdScore;thresholdScore<0.45;thresholdScore+=0.01)
	{
		int rightDetectNum=0;
		int trueNegative=0;
		float notDetectRatio=0;//漏检率
		float FPPW=0;
		int falseDetectNum=0;
		int overlapFlag=0;
		float areaScore=0;
		int positive=0;

		ifstream in_detect("myname.txt");
		Rect rectDetec;
		ifstream in_anno("myname1.txt");
		Rect rectAnno;
		Rect rectOverlap;
		float acc[4];
		vector<Rect> vecRectDetec;
		vector<Rect> vecrectAnno;

		//Mat imgA=imread("tud1.png");
		//Mat imgB=imread("tud0.png");
		while (!in_detect.eof())
		{
			for (;;)
			{
				for (int i=0;i<4;++i)
				{
					in_detect>>acc[i];
				}
				if (acc[0]==0||in_detect.eof())
				{
					break;
				}
				rectDetec=Rect(acc[0],acc[1],acc[2],acc[3]);
				vecRectDetec.push_back(rectDetec);
				//cout<<"rectDetec:"<<rectDetec<<endl;
			}
			for (;;)
			{
				for (int i=0;i<4;++i)
				{
					in_anno>>acc[i];
				}
				if (acc[0]==0||in_anno.eof())
				{
					break;
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
					acc[2]=acc[2]-acc[0];
					acc[3]=acc[3]-acc[1];

					rectAnno=Rect(acc[0],acc[1],acc[2],acc[3]);//rectAnno(217,208,-55,143);//rect中允许有负值
					vecrectAnno.push_back(rectAnno);
					positive++;

			}
			//vetRectImageShow(vecRectDetec, imgA,color[1]);
			//vetRectImageShow(vecrectAnno, imgA,color[2]);
			int thisImageDetectNum=0;
			for(int detectnum=0;detectnum<vecRectDetec.size();++detectnum)
			{
				float area=0;
				for(int i=0;i<vecrectAnno.size();++i)
				{
					rectOverlap=vecrectAnno.at(i) & vecRectDetec.at(detectnum);//"|"包含r1r2的最小矩形 opencv的bug，&重载是数值必须为正。
					area=rectOverlap.area();

					if (area>0)
					{ 
						overlapFlag=1;
						areaScore=area/(vecrectAnno.at(i).area()+vecRectDetec.at(detectnum).area()-area);
						if (areaScore>=thresholdScore)
						{
							thisImageDetectNum++;
							rightDetectNum++;
							break;
							//cout<<"the area of overlap is :"<<area<<"and score is:"<<areaScore<<endl;
						}
					}	
				}

				//if (!overlapFlag)
				//{
				//	falseDetectNum++;
				//}
				//else overlapFlag=0;
			}
			//#差别！
			//for(int i=0;i<vecrectAnno.size();++i)
			//{
			//	float area;
			//	int score;
			//	for(int detectnum=0;detectnum<vecRectDetec.size();++detectnum)
			//	{
			//		rectOverlap=vecrectAnno.at(i) & vecRectDetec.at(detectnum);//"|"包含r1r2的最小矩形 opencv的bug，&重载是数值必须为正。
			//		area=rectOverlap.area();

			//		if (area>0)
			//		{ 
			//			overlapFlag=1;
			//			areaScore=area/(vecrectAnno.at(i).area()+vecRectDetec.at(detectnum).area()-area);
			//			if (areaScore>=thresholdScore)
			//			{
			//				thisImageDetectNum++;
			//				rightDetectNum++;
			//				break;
			//				//cout<<"the area of overlap is :"<<area<<"and score is:"<<areaScore<<endl;
			//			}
			//		}	
			//	}
			//}
			trueNegative+=vecrectAnno.size()-thisImageDetectNum;
			falseDetectNum+=vecRectDetec.size()-thisImageDetectNum;
			cout<<"the right detection number is:"<<rightDetectNum<<endl;
			cout<<"the don't be detected number is:"<<trueNegative<<endl;
			cout<<"the false detected number is:"<<falseDetectNum<<endl;
			//vetRectImageShow(vecRectDetec, imgA,color[1]);
			//vetRectImageShow(vecrectAnno, imgA,color[2]);
			vecrectAnno.clear();
			vecRectDetec.clear();
			waitKey();
		}
		notDetectRatio=1-(float)rightDetectNum/positive;
		FPPW=(float)falseDetectNum/(trueNegative+falseDetectNum);
		ofstream outf("result_ROC.txt",ios::app);

		cout<<"the notDetectRatio is:"<<notDetectRatio<<" ";
		cout<<"the FPPW is:"<<FPPW<<endl;
		//outf<<"the thresholdScore is :"<<thresholdScore<<endl;
		//outf<<"the notDetectRatio is:"<<notDetectRatio<<" ";
		//outf<<"the FPPW is:"<<FPPW<<endl;
		//outf<<"the thresholdScore is :"<<thresholdScore<<endl;
		outf<<FPPW<<" "<<notDetectRatio<<endl;
		//cout<<"the false detected number is:"<<falseDetectNum<<endl;
		
	}
	waitKey();
	return 0;
}
void vetRectImageShow(vector<Rect> &vec, Mat &img,Scalar &color_rect)
{
	cout<<vec.size()<<":many"<<endl;
	Rect rect;
	for(int i=0;i<vec.size();++i)
	{
		rect=vec.at(i);
		rectangle(img,rect.tl(),rect.br(),color_rect,2);
	}
	imshow("tud0",img);
}