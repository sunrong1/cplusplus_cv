/*
在命令行模式下键入下面的命令： 　　
test >>cout.txt
	运行结果是：
	在生成的cout.txt文件中输出了"hello world---cout" ，
	同时在显示器上输出了"hello world---cerr" ，
	也就是说cout的输出可以重定向到一个文件中，而cerr必须输出在显示器上。
	 缓冲区的目的，就是减少刷屏的次数.有了cerr就是在你最需要它的紧急情况下，还能得到输出功能的支持。
*/
#include <iostream>
using namespace std;
int main()
{
	cout << "hello world---cout" << endl ;
	cerr << "hello world---cerr" << endl ;
	return 0;
}