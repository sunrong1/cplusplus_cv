//1��break ���������ֹ����ķ��ѭ���������ڵ� switch ��䡣
//���ƴ��ݸ���ֹ���������䣨����еĻ�����
//2��continue ��佫����Ȩ���ݸ������ڵķ�յ���������һ�ε�����
#include <iostream>
#include<fstream>
#include <string>
using namespace std;
int main()
{
	string name;
	
	for (;;)
	{
		cin>>name;
		if (name=="s")
		{
			continue;
			cout<<"This is if"<<endl;
		}
		if (name=="r")
		{
			break;
		}
		cout<<"This is for"<<endl;
	}
	return 0;
}
