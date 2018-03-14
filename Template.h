#pragma once
#include <vector>
using namespace std;

class Template
{
public:
	vector<bool> Eratosthenes_Sieve(int n);					//Eratosthenesɸ��
	int gcd(int a, int b);									//ŷ������㷨
	void ex_gcd(int a, int b, int &x, int &y);				//��չŷ������㷨
	vector<int> Prime_Factor(int n);						//�ֽ�������
};

/*Eratosthenesɸ��
**ɸѡ��n���ڵ���������
**���ز���res�����res[i] == false��iΪ����
***����:����p<=n && p>1����������p,�������1p,2p,3p,4p......��δ��ǵ�����Ϊ����
***    !res[i]:ֻ���ж�pΪ�������������p��������p��p�ı�����֮ǰ��ѭ���Ѿ���ǹ�
***    i * i:�ڲ�ѭ��ֻ���i*i��ʼ��Ϊ֮ǰ��ѭ���Ѿ���ǹ�i * x(x<i)�����
*/

vector<bool> Template::Eratosthenes_Sieve(int n)
{
	vector<bool> res(n+1, false);
	res[0] = true;
	res[1] = true;
	for (int i = 2; i <= n; i++)
	{
		if (!res[i])
		{
			for (int j = i * i; j <= n; j += i)
			{
				res[j] = true;
			}
		}
	}
	return res;
}

/*ŷ������㷨��շת�������
**�ҳ�a��b�����Լ��
**���ز���Ϊa��b�����Լ��
*/

int Template::gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a%b);
}

/*��չŷ������㷨
**�ҳ�ax + by = gcd(a,b)��һ��x,y������
**����x,y��Ϊ����������һ��������
***���ͣ�
***		����1����b = 0ʱax + by = gcd(a,b) = a,��ʱx = 1,ȡy = 0;
***		����2����ax1 + by1 = gcd(a,b), bx2 + a%by2 = gcd(b,a%b) ��ŷ������㷨�ݹ��֪gcd(a,b) = gcd(b,a%b)
***			  ��ɵõ�ʽa(x1) + b(y1) = a(y2) + b(x2 - (a/b)*y2)��a,bΪδ֪���ɵ�ʽ��ȶ���ɵ�
***		   	  ���ƹ�ϵ x1 = y2 , y1 = x2 - (a/b)*y2;
*/

void Template::ex_gcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return; p;.gy
	}
	int x1, y1;
	ex_gcd(b, a%b, x1, y1);
	x = y1;
	y = x1 - (a / b)*y1;
}

/*�ֽ���������Ψһ�ֽⶨ��
**������n�ö��������˵���ʽ��ʾ
**���ز���res�е�Ԫ�ؼ�Ϊn����������
***������������ɱ���Ϊ���κ�һ������1����Ȼ�� N,���N��Ϊ��������ôN����Ψһ�ֽ�����޸������ĳ˻�;
*/

vector<int> Template::Prime_Factor(int n)
{
	vector<int> res;
	for (int i = 2; i <= n; i++)
	{
		while (n%i == 0)
		{
			res.push_back(i);
			n /= i;
		}
	}
	return res;
}