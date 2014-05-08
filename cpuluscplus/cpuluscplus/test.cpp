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
//int truePosDetectNum=0;
//int falseNegDetectNum=0;
//float notDetectRatio=0;//漏检率
//float FPPW=0;
//int falsePosDetectNum=0;
//int overlapFlag=0;
//float areaScore=0;
//int positive=0;
const long rectNum=207620;

float thresholdScore=0.5;//0.34
Scalar color[3]={Scalar(255,0,0),Scalar(0,255,0),Scalar(0,0,255)};
int main()
{
	//for (thresholdScore;thresholdScore<0.45;thresholdScore+=0.01)
	//{
		int truePosDetectNum=0;
		int falseNegDetectNum=0;
		int trueNegDetectNum=0;
		float notDetectRatio=0;//漏检率
		float FPPW=0;
		float FPPI=0;
		int falsePosDetectNum=0;
		int overlapFlag=0;
		float areaScore=0;
		int positive=0;
		int posDection=0;

		ifstream in_detect("myname.txt");
		Rect rectDetec;
		ifstream in_anno("HOG_anno.txt");
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
				posDection++;
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
							truePosDetectNum++;
							break;
							//cout<<"the area of overlap is :"<<area<<"and score is:"<<areaScore<<endl;
						}
					}	
				}

				//if (!overlapFlag)
				//{
				//	falsePosDetectNum++;
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
			//				truePosDetectNum++;
			//				break;
			//				//cout<<"the area of overlap is :"<<area<<"and score is:"<<areaScore<<endl;
			//			}
			//		}	
			//	}
			//}
			falseNegDetectNum+=vecrectAnno.size()-thisImageDetectNum;
			falsePosDetectNum+=vecRectDetec.size()-thisImageDetectNum;
			cout<<"the true positive detection number is:"<<truePosDetectNum<<endl;
			cout<<"the don't be detected number is:"<<falseNegDetectNum<<endl;
			cout<<"the false positive detected number is:"<<falsePosDetectNum<<endl;
			//vetRectImageShow(vecRectDetec, imgA,color[1]);
			//vetRectImageShow(vecrectAnno, imgA,color[2]);
			vecrectAnno.clear();
			vecRectDetec.clear();
			waitKey();
		}
		notDetectRatio=1-(float)truePosDetectNum/positive;
		trueNegDetectNum=(rectNum-posDection)-falseNegDetectNum;
		//FPPW=(float)falsePosDetectNum/(trueNegDetectNum+falsePosDetectNum);
		FPPI=falsePosDetectNum/288.0;
		ofstream outf("result_ROC.txt",ios::app);

		cout<<"the notDetectRatio is:"<<notDetectRatio<<" ";
		//cout<<"the FPPW is:"<<FPPW<<endl;
		cout<<"the FPPI is:"<<FPPI<<endl;
		//outf<<"the thresholdScore is :"<<thresholdScore<<endl;
		//outf<<"the notDetectRatio is:"<<notDetectRatio<<" ";
		//outf<<"the FPPW is:"<<FPPW<<endl;
		//outf<<"the thresholdScore is :"<<thresholdScore<<endl;
		outf<<FPPI<<" "<<notDetectRatio<<endl;
		//cout<<"the false detected number is:"<<falsePosDetectNum<<endl;

	//}
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