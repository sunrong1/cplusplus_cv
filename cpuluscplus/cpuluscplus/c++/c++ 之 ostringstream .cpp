
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

void main()
{
	ostringstream ostr1; // 构造方式1
	ostringstream ostr2("abc");	// 构造方式2

	/*----------------------------------------------------------------------------
	*** 方法str()将缓冲区的内容复制到一个string对象中，并返回
	----------------------------------------------------------------------------*/
	ostr1 << "ostr1" << 2012 << endl;	// 格式化，此处endl也将格式化进ostr1中
	cout << ostr1.str(); 

	/*----------------------------------------------------------------------------
	*** 建议：在用put()方法时，先查看当前put pointer的值，防止误写
	----------------------------------------------------------------------------*/
	long curPos = ostr2.tellp(); //返回当前插入的索引位置(即put pointer的值)，从0开始 
	cout << "curPos = " << curPos << endl;

	ostr2.seekp(2);	// 手动设置put pointer的值
	ostr2.put('g');		// 在put pointer的位置上写入'g'，并将put pointer指向下一个字符位置
	cout << ostr2.str() << endl;


	/*----------------------------------------------------------------------------
	*** 重复使用同一个ostringstream对象时，建议：
	*** 1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
	*** 2：调用str("")将缓冲区清零，清除脏数据
	----------------------------------------------------------------------------*/
	ostr2.clear();
	ostr2.str("");

	cout << ostr2.str() << endl;
	ostr2.str("_def");
	cout << ostr2.str() << endl;
	ostr2 << "gggghh";	// 覆盖原有的数据，并自动增加缓冲区
	cout << ostr2.str() << endl;
}
//#include "Pedestrian.h"
//using namespace std;
//int main(int argc,char* argv[])
//{
//	//RunFiles();
//	ostringstream ost;
//	ost<<"ost1"<<2012<<endl;
//	cout<<ost.str();
//	return 0;
//}