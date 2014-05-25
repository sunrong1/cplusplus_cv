#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
void salt(Mat &img_origin,int num)
{
	for (int i=0;i<num;++i)
	{
		int row=rand()%img_origin.rows;
		int col=rand()%img_origin.cols;

		if (img_origin.channels()==1)
		{
			img_origin.at<uchar>(row,col)=255;
		}
		else
		{
			if (img_origin.channels()==3)
			{
				img_origin.at<cv::Vec3b>(row,col)[0]=255;
				img_origin.at<cv::Vec3b>(row,col)[1]=255;
				img_origin.at<cv::Vec3b>(row,col)[2]=255;
			}
		}
	}
}
int main()
{
    Mat img = imread("one.jpg");
    if(img.empty())
    {
        cout<<"error";
        return -1;
    }
	salt(img,1000);
    imshow("qi'eµÄö¦ÕÕ",img);
    waitKey();

    return 0;
}