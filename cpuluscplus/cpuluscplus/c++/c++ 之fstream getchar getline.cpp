// cpuluscplus.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include "string"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	//ofstream out("myname.txt");
	ifstream in("myname.txt");//读文件
	//getchar()测试
	//char c;
	//c=getchar();
	//cout<<c<<endl;
	string line;
	// getline(cin,line) 是一个系统函数，可以输入标准行内容,这个函数不会忽略任何内容一直读取用户输入并保存到line，
	//直到用户输入换行函数才结束，结束时函数会返回cin的引用。 
	while (getline(in,line))
	{
		cout<<line<<endl;
	}
	//ofstream()写文件测试
	//for (int i=0;i<5;++i)
	//{
	//	out<<'a';
	//}
	//out<<'b'<<endl;
	//out<<"sunrong";
	return 0;
}

