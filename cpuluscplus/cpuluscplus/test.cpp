
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
	outf.open("result.txt",ios::app); //ios::app  �Ӻ������
	outf<<"sunrong1"<<endl;//������ļ���
	outf.close();
	return 0;
}