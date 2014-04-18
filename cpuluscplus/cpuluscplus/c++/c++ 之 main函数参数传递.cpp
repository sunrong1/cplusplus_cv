#include <iostream>
using namespace std;
void main(int argc, char *argv[])
{
	cout<<"The number of command line arguments is:"<<argc<<endl;
	cout<<"The program name is:"<<argv[0]<<endl;
	if (argc>1)
	{ cout<<"The command line arguments:\n";
	for (int i=1; i<argc; i++)
		cout<<argv[i]<<endl;
	}
}