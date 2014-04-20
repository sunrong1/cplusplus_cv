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

	if(!logoImage.data ) { std::cout<<"Oh，no，读取logoImage错误~！"<<std::endl; return false; }  
	if(!srcImage.data ) { std::cout<<"Oh，no，读取srcImage错误~！"<<std::endl; return false; } 

	vector<Mat> channels;
	split(srcImage,channels);

	Mat imageBluechannel=channels.at(0);//OpenCV的BGR色彩空间（bule-0，Green，Red-2，蓝绿红)
	
	Mat imageROI=imageBluechannel(Rect(100,200,logoImage.cols,logoImage.rows));//指定图像中感兴趣位置ROI
	addWeighted(imageROI,1.0,logoImage,0.5,0,imageROI);  //一个通道进行图像融合

	merge(channels,srcImage);

	namedWindow("bluechannelmerge");
	imshow("bluechannelmerge",srcImage);

	namedWindow("channelmerge");
	imshow("channelmerge",channels.at(1));


}