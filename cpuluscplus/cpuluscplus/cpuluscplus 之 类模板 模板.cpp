// cpuluscplus.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include "string"
#include <climits>
//#include <cassert>
using namespace std;
template <class T>
T maxmy(T x,T y)
{
	return (x>y) ? x:y;
}
//static const /const static ��Ա���������г�ʼ����ʵ������������
//Ҳ���Բ���ʼ����ͬʱ��Ҫ�����ⶨ��  
//���һ���������ݳ�Ա���������Ͳ���ȷ����������ĳ����Ա�����Ĳ����򷵻�ֵ�����Ͳ���ȷ����
//�ͱ��뽫��������Ϊģ�壬���Ĵ��ڲ��Ǵ���һ������ġ�ʵ�ʵ��࣬���Ǵ�����һ���ࡣ
template <class type>
class Templatebase
{
public:
	Templatebase();
//	Templatebase(type x);
	//~Templatebase();
	void print();
private:
	type a;
	const type b;   //const ��Ա�������ó�Ա������Ĺ��캯����ʼ���б��г�ʼ�� 
	static type c; //���еľ�̬������������ģ�������ĳ������.static ��Ա�������ʼ��  

};
template <class type> 
Templatebase<type>::Templatebase():b(3)
{
}
template <class type> 
void Templatebase<type>::print()
{
	cout<<"a:"<<a<<endl;
	cout<<"b:"<<b<<endl;
	cout<<"c:"<<c++<<endl;
}
using namespace std;
template <class type> 
type Templatebase<type>::c=1;
int _tmain(int argc, _TCHAR* argv[])
{
	Templatebase<int> myfirst;
	myfirst.print();
	myfirst.print();
	int n1=1,n2=2;
	float f1=1.2,f2=0.3;
	cout<<"the bigger integer is:"<<maxmy(n1,n2)<<endl;
	cout<<"the bigger float is:"<<maxmy(f1,f2)<<endl;
	return 0;
}

