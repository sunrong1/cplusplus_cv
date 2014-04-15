// cpuluscplus.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include "string"
#include "Windows.h"
//assert.h常用于防御式编程。断言（Assertions），一个断言通常是一个例程（routines）或者一个宏（marcos）。
//每个断言通常含有两个参数：一个布尔表示式（a boolean expression）和一个消息（a message)。
//assert宏需要一个表达式作为它的条件assert(expr),如果为false，assert输出并终止程序。
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

