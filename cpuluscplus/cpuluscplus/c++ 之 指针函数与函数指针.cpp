//#include <iostream>
//#include <string>
//using namespace std;
////����һ������ָ�����ͣ����ڱ�����Ҫָ��ĺ�����ַ
////����ָ��ı�����һ��ָ�룬ָ��ָ�����һ��������ָ�뺯���ı�����һ���������亯���ķ���ֵ��һ��ָ�롣
//typedef int (*pfun)(int ,int );//����ָ�� pfun��һ��ָ�򷵻�ֵΪint�ĺ�����ָ�롣
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
����1
��ʹ��typedef��������PF�ͳ�Ϊ��һ������ָ�롰���͡�������

typedef int (*PF)(int *, int);

�����Ͷ����˷���ֵ�����͡�Ȼ������PF��Ϊ����ֵ����������:

PF ff(int);
*/
#include <stdio.h>
using namespace std;
int* lpfun1(int,int);  //����һ������ָ��Ϊint���͵ĺ���
int lpfun2(int,int);//��ͨ����
typedef int (*lpfunPointer)(int,int);
//����һ������ָ�����ͣ����ڱ�����Ҫָ��ĺ�����ַ,lpfunPointer��Ϊ��һ������
void main()
{
  int *result=lpfun1(10,20);
  printf("%d\n",*result);
  delete result;//ɾ�����е�ָ��
  result=0;//ʹָ����Ч

  lpfunPointer p=lpfun2; //����lpfun2�����ĵ�ַ��������Ҳ��һ��ָ��
  printf("%d\n",p(12,60));  //���ô��εĺ���

}
/***********************************************************************************************
  lpfun1����˵����
����������������ڴ˺���������д����int *p=NULL;
                             *p=x+y;
                             return p;
  ������д���Ǵ���ģ���Ϊ�ں����������ı����ں���ִ�����Ͳ����ˣ�������p�����ˣ��Ǹ���Чָ�룬�Ͳ��ܵõ��������ֵ��
��������ڶ��п���һС�ڴ�����ţ�������ɺ����ֹ����ͷţ������ǿ�����int* p=new int;��������������ʹ����û�ˣ���
���p���Ǵ����ڶ��еģ��ɴ����ǻῴ����main()������һ��int *result=lpfun1(10,20)�Ѷ��е�pָ��ָ��resultָ�룬��
�ֹ��ͷš��������Ͳ����ڴ�й¶�ˡ�

���ǣ���Զ��Ҫ�Ӻ����з��ؾֲ��Զ������ĵ�ַ��
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
����2 typedef��ʹ��
/*
/*ԭ������void (*b[10]) (void (*)());

������Ϊb�����滻�ұ߲���������ģ�pFunParamΪ����һ��

	typedef void (*pFunParam)();

���滻��ߵı���b��pFunxΪ��������

	typedef void (*pFunx)(pFunParam);

ԭ��������򻯰棺

	pFunx b[10];
*/