// cpuluscplus.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include "string"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	//ofstream out("myname.txt");
	ifstream in("myname.txt");//���ļ�
	//getchar()����
	//char c;
	//c=getchar();
	//cout<<c<<endl;
	string line;
	// getline(cin,line) ��һ��ϵͳ���������������׼������,���������������κ�����һֱ��ȡ�û����벢���浽line��
	//ֱ���û����뻻�к����Ž���������ʱ�����᷵��cin�����á� 
	while (getline(in,line))
	{
		cout<<line<<endl;
	}
	//ofstream()д�ļ�����
	//for (int i=0;i<5;++i)
	//{
	//	out<<'a';
	//}
	//out<<'b'<<endl;
	//out<<"sunrong";
	return 0;
}

