// cpuluscplus.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include "string"
#include "Windows.h"
//assert.h�����ڷ���ʽ��̡����ԣ�Assertions����һ������ͨ����һ�����̣�routines������һ���꣨marcos����
//ÿ������ͨ����������������һ��������ʾʽ��a boolean expression����һ����Ϣ��a message)��
//assert����Ҫһ�����ʽ��Ϊ��������assert(expr),���Ϊfalse��assert�������ֹ����
#include <cassert>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	string c;
	while(cin>>c)
	{
		assert(c=="stop");
		cout<<"You are right"<<endl;
	}
	system("pause");
	return 0;
}

