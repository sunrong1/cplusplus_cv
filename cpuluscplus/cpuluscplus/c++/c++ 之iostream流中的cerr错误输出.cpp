/*
��������ģʽ�¼����������� ����
test >>cout.txt
	���н���ǣ�
	�����ɵ�cout.txt�ļ��������"hello world---cout" ��
	ͬʱ����ʾ���������"hello world---cerr" ��
	Ҳ����˵cout����������ض���һ���ļ��У���cerr�����������ʾ���ϡ�
	 ��������Ŀ�ģ����Ǽ���ˢ���Ĵ���.����cerr������������Ҫ���Ľ�������£����ܵõ�������ܵ�֧�֡�
*/
#include <iostream>
using namespace std;
int main()
{
	cout << "hello world---cout" << endl ;
	cerr << "hello world---cerr" << endl ;
	return 0;
}