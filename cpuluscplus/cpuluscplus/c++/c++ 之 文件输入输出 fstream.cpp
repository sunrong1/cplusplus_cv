
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
	outf.open("a.txt",ios::app);////ios::app  �Ӻ������
	outf<<"sunrong"<<endl;//������ļ���
	outf.close();
	return 0;
}
