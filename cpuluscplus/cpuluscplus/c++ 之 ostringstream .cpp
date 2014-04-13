
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

void main()
{
	ostringstream ostr1; // ���췽ʽ1
	ostringstream ostr2("abc");	// ���췽ʽ2

	/*----------------------------------------------------------------------------
	*** ����str()�������������ݸ��Ƶ�һ��string�����У�������
	----------------------------------------------------------------------------*/
	ostr1 << "ostr1" << 2012 << endl;	// ��ʽ�����˴�endlҲ����ʽ����ostr1��
	cout << ostr1.str(); 

	/*----------------------------------------------------------------------------
	*** ���飺����put()����ʱ���Ȳ鿴��ǰput pointer��ֵ����ֹ��д
	----------------------------------------------------------------------------*/
	long curPos = ostr2.tellp(); //���ص�ǰ���������λ��(��put pointer��ֵ)����0��ʼ 
	cout << "curPos = " << curPos << endl;

	ostr2.seekp(2);	// �ֶ�����put pointer��ֵ
	ostr2.put('g');		// ��put pointer��λ����д��'g'������put pointerָ����һ���ַ�λ��
	cout << ostr2.str() << endl;


	/*----------------------------------------------------------------------------
	*** �ظ�ʹ��ͬһ��ostringstream����ʱ�����飺
	*** 1������clear()�����ǰ�������״̬����ԭ��Ϊ void clear (iostate state=goodbit);
	*** 2������str("")�����������㣬���������
	----------------------------------------------------------------------------*/
	ostr2.clear();
	ostr2.str("");

	cout << ostr2.str() << endl;
	ostr2.str("_def");
	cout << ostr2.str() << endl;
	ostr2 << "gggghh";	// ����ԭ�е����ݣ����Զ����ӻ�����
	cout << ostr2.str() << endl;
}
//#include "Pedestrian.h"
//using namespace std;
//int main(int argc,char* argv[])
//{
//	//RunFiles();
//	ostringstream ost;
//	ost<<"ost1"<<2012<<endl;
//	cout<<ost.str();
//	return 0;
//}