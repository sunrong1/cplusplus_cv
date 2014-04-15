//1、break 语句用于终止最近的封闭循环或它所在的 switch 语句。
//控制传递给终止语句后面的语句（如果有的话）。
//2、continue 语句将控制权传递给它所在的封闭迭代语句的下一次迭代。
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
