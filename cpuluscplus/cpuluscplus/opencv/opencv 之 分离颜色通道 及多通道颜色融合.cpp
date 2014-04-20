#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
bool MultiChannelBlending();
int main()
{

//	 system("color5E");  
	MultiChannelBlending();
	waitKey();
	return 0;
}
bool MultiChannelBlending()
{
	Mat srcImage;
	Mat logoImage;

	srcImage=imread("girl.jpg");
	logoImage=imread("gaara.jpg",0);

	if(!logoImage.data ) { std::cout<<"Oh��no����ȡlogoImage����~��"<<std::endl; return false; }  
	if(!srcImage.data ) { std::cout<<"Oh��no����ȡsrcImage����~��"<<std::endl; return false; } 

	vector<Mat> channels;
	split(srcImage,channels);

	Mat imageBluechannel=channels.at(0);//OpenCV��BGRɫ�ʿռ䣨bule-0��Green��Red-2�����̺�)
	
	Mat imageROI=imageBluechannel(Rect(100,200,logoImage.cols,logoImage.rows));//ָ��ͼ���и���Ȥλ��ROI
	addWeighted(imageROI,1.0,logoImage,0.5,0,imageROI);  //һ��ͨ������ͼ���ں�

	merge(channels,srcImage);

	namedWindow("bluechannelmerge");
	imshow("bluechannelmerge",srcImage);

	namedWindow("channelmerge");
	imshow("channelmerge",channels.at(1));


}