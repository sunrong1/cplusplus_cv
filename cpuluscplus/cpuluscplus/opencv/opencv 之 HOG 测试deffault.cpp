
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <string>
#include<fstream>
//#include <ctype.h>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    Mat img;
    
	ifstream  fin("posbig.txt");
	string filename;
	char* savename[20];
	int detectnum=0;
	HOGDescriptor hog;         //����Ĭ�ϲ���
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector()); //�����Ѿ�ѵ���õ����˼�������

	namedWindow("people detector", 1);

	double t = (double)getTickCount(); //��¼ʱ��  exec_time = ((double)getTickCount() - exec_time)*1000./getTickFrequency();
	while(getline(fin,filename))
	{
		filename="../../../data/INRIA/INRIAPerson/Test/pos/"+filename;
		img = imread(filename);	//ÿ��ѭ�������ȡһ��ͼƬ
		if(!img.data)
			break;
		cout<<"processing:"<<filename<<endl;

		vector<Rect> found, found_filtered;

		// run the detector with default parameters. to get a higher hit-rate
		// (and more false alarms, respectively), decrease the hitThreshold and
		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
		hog.detectMultiScale(img, found, 0, Size(8,8), Size(8,8), 1.05, 2);//padding 32 32
		/*
		virtual void detectMultiScale(const Mat& img, CV_OUT vector<Rect>& foundLocations,
		double hitThreshold=0, Size winStride=Size(),
		Size padding=Size(), double scale=1.05,
		double finalThreshold=2.0, bool useMeanshiftGrouping = false) const;
		img				�C Source image. 
		found_locations �C objects boundaries(x,y,width,height).
		hit_threshold	�C Threshold for the distance between features and SVM classifying plane.
		win_stride		�C Window stride. It must be a multiple of block stride.
		padding			�C Mock parameter to keep the CPU interface compatibility. It must be (0,0).  ????
		scale0			�C Coefficient of the detection window increase.
		group_threshold	�C Coefficient to regulate the similarity threshold. When detected, some
		objects can be covered by many rectangles. 0 means not to perform grouping.  ԭ���ܼ��һ���ˣ�����Ϊ4��ʱ���Ȼû��
		*/
	

		size_t i, j;
		for( i = 0; i < found.size(); i++ )//ȥ���ռ��о������������ϵ�����򣬱������
		{
			Rect r = found[i];
			for( j = 0; j < found.size(); j++ )
				if( j != i && (r & found[j]) == r)
					break;
			if( j == found.size() )
				found_filtered.push_back(r);
		}
		for( i = 0; i < found_filtered.size(); i++ )
		{
			Rect r = found_filtered[i];
			// the HOG detector returns slightly larger rectangles than the real objects.
			// so we slightly shrink the rectangles to get a nicer output.
			r.x += cvRound(r.width*0.1);	//�������룬��������
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 3);// tl:the top-left corner,br: the bottom-right corner,
		}
		imshow("people detector", img);

		sprintf(savename,"person%06d.png",++detectnum);//���ɲü����ĸ�����ͼƬ���ļ��� ��ʽ���ַ���
		imwrite(savename, img);//�����ļ�
		waitKey(1);
	}
	t = (double)getTickCount() - t;
	printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());
    return 0;
}
