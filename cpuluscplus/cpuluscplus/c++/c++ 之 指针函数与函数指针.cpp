//#include <iostream>
//#include <string>
//using namespace std;
////声明一个函数指针类型，用于保存它要指向的函数地址
////函数指针的本身是一个指针，指针指向的是一个函数。指针函数的本身是一个函数，其函数的返回值是一个指针。
//typedef int (*pfun)(int ,int );//函数指针 pfun是一个指向返回值为int的函数的指针。
//int main()
//{
//	char *p,m;
//	char k='k';
//	p=&k;
//	m='m';
//	cout<<*p<<endl;
//	cout<<m<<endl;
//	return 0;
//}


/*
例子1
当使用typedef声明后，则PF就成为了一个函数指针“类型”，即：

typedef int (*PF)(int *, int);

这样就定义了返回值的类型。然后，再用PF作为返回值来声明函数:

PF ff(int);
*/
#include <stdio.h>
using namespace std;
int* lpfun1(int,int);  //声明一个返回指针为int类型的函数
int lpfun2(int,int);//普通函数
typedef int (*lpfunPointer)(int,int);
//声明一个函数指针类型，用于保存它要指向的函数地址,lpfunPointer成为了一种类型
void main()
{
  int *result=lpfun1(10,20);
  printf("%d\n",*result);
  delete result;//删除堆中的指针
  result=0;//使指针无效

  lpfunPointer p=lpfun2; //保存lpfun2函数的地址，函数名也是一种指针
  printf("%d\n",p(12,60));  //调用带参的函数

}
/***********************************************************************************************
  lpfun1过程说明：
　　　　如果我们在此函数中这样写：　int *p=NULL;
                             *p=x+y;
                             return p;
  这样的写法是错误的，因为在函数中声明的变量在函数执行完后就不存了，即此是p不存了，是个无效指针，就不能得到这个返回值。
　而如果在堆中开辟一小内存来存放，并在完成后由手工来释放，则我们可以用int* p=new int;来创建，这样即使函数没了，但
这个p还是存在于堆中的，由此我们会看到在main()中用了一个int *result=lpfun1(10,20)把堆中的p指针指向result指针，再
手工释放。　这样就不会内存泄露了。

谨记：永远不要从函数中返回局部自动变量的地址。
******************************************/
int* lpfun1(int x,int y)
{
    int *p=new int(0);
    *p=x+y;
    return p;
}

int lpfun2(int x,int y) 
{
    return x+y;
}

/*
例子2 typedef的使用
/*
/*原声明：void (*b[10]) (void (*)());

变量名为b，先替换右边部分括号里的，pFunParam为别名一：

	typedef void (*pFunParam)();

再替换左边的变量b，pFunx为别名二：

	typedef void (*pFunx)(pFunParam);

原声明的最简化版：

	pFunx b[10];
*/