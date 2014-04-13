/*
OpenCV�ṩ��һЩ�����Ļ�ͼ������
���续Բ������Բ�����ߣ������Σ���ͼ����������ֵȹ��ܡ�
*/
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat image=imread("you1.jpg");


	Point center = Point(255,255);	//Բ��
	int r = 100; 	//�뾶
	//����Ϊ�����ص�ͼ��Բ�ġ��뾶����ɫ����ϸ������
	circle(image,center,r,Scalar(255,0,0));
	imshow("circle",image);

	Rect found(10,10,100,200); 
	// tl:the top-left corner,br: the bottom-right corner,
	//����Ϊ�����ص�ͼ�񡢶��㡢�Խǵ㡢��ɫ�����̺죩����ϸ����С  
	rectangle(image,found.tl(),found.br(),Scalar(200,255,255),3);

	Rect found_com(20,20,50,50);
	if ((found & found_com)==found_com)
	{
		cout<<"There are common"<<endl;
	}
	//Point add=Point(50,50);
	//found=found+add; //ƽ�Ʋ���

	//rectangle(image,found.tl(),found.br(),Scalar(0,0,200),4);
	//Size scale=Size(100,100);
	//found=found+scale; //���Ų���
	//rectangle(image,found.tl(),found.br(),Scalar(0,0,200),4);

	found=found | found_com;

	rectangle(image,found.tl(),found.br(),Scalar(0,255,0),4);
	cout<<found_com.size()<<endl;

	namedWindow("Naruto");
	imshow("Naruto",image);
	waitKey();

	return 0;
}