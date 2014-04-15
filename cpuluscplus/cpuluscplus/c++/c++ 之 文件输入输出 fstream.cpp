
#include <iostream>
#include<fstream>
#include <string>
using namespace std;
int main()
{

	ifstream inf("myname.txt");
	
	string line;
	while (getline(inf,line))
	{
		cout<<line<<endl;
	}
	inf.close();
	ofstream outf;
	outf.open("a.txt",ios::app);////ios::app  从后面添加
	outf<<"sunrong"<<endl;//输出到文件中
	outf.close();
	return 0;
}
