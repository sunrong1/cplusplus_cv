// cpuluscplus.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include "string"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	//ofstream in("myname.txt");
	ifstream out("myname.txt");//���ļ�
	//getchar()����
	//char c;
	//c=getchar();
	//cout<<c<<endl;
	string line;
	// getline(cin,line) ��һ��ϵͳ���������������׼������,���������������κ�����һֱ��ȡ�û����벢���浽line��
	//ֱ���û����뻻�к����Ž���������ʱ�����᷵��cin�����á� 
	while (getline(out,line))
	{
		cout<<line<<endl;
	}
	//ofstream()д�ļ�����
	//for (int i=0;i<5;++i)
	//{
	//	in<<'a';
	//}
	//in<<'b'<<endl;
	//in<<"sunrong";
	return 0;
}

