// cpuluscplus.cpp : 定义控制台应用程序的入口点。
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
//static const /const static 成员可以在类中初始化（实际上是申明）
//也可以不初始化，同时需要在类外定义  
//如果一个类中数据成员的数据类型不能确定，或者是某个成员函数的参数或返回值的类型不能确定，
//就必须将此类声明为模板，它的存在不是代表一个具体的、实际的类，而是代表着一类类。
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
	const type b;   //const 成员（及引用成员）在类的构造函数初始化列表中初始化 
	static type c; //类中的静态变量是属于类的，不属于某个对象.static 成员在类外初始化  

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

