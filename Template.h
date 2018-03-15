#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Template
{
public:
	vector<bool> Eratosthenes_Sieve(int n);					//Eratosthenesɸ��
	int gcd(int a, int b);									//ŷ������㷨
	void ex_gcd(int a, int b, int &x, int &y);				//��չŷ������㷨
	vector<int> Prime_Factor(int n);						//�ֽ�������
	int Longest_substring(string s);						//����ظ��Ӵ�
	void merge_sort(vector<int> &target);					//�鲢����
	void quick_sort(vector<int> &target);					//��������
private:
	void merge_sort_recursive(vector<int> &target, std::vector<int> &copy, size_t start, size_t end);
	void quick_sort_recursive(vector<int> &target, int start, int end);
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
		return;
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

/*����ظ��Ӵ�
**�ҳ���s������ظ��Ӵ� ����"abcabcbb"������ظ��Ӵ�Ϊ"abc"����Ϊ3
**���ز�����Ϊ����ظ��Ӵ��ĳ���
***
*/

int Template::Longest_substring(string s)
{
	int length = s.length(), res = 0;
	unordered_map<char, int> hash_map; 
	int low = 0;
	for (int high = 0 ; high < length; high++)
	{
		auto itr = hash_map.find(s[high]);
		if (itr != hash_map.end())
		{
			low = max(itr->second, low);
		}
		bool flag;
		flag = hash_map.insert({ s[high], high + 1 }).second;
		if (!flag)
		{
			hash_map[s[high]] = high + 1;
		}
		res = max(res, high + 1 - low);
	}
	return res;
}

/*�鲢����
**�Թ鲢����ķ�����������target
***
*/

void Template::merge_sort(vector<int> &target)
{
	vector<int> copy = target;
	merge_sort_recursive(target, copy, 0, target.size() - 1);
}
void Template::merge_sort_recursive(vector<int> &target, std::vector<int> &copy, size_t start, size_t end)
{
	if (start >= end) return;
	int mid = (end - start + 1) / 2 + start;
	merge_sort_recursive(target, copy, start, mid - 1);
	merge_sort_recursive(target, copy, mid, end);
	int start1 = start, start2 = mid, counter = start;
	while (start1 <= mid - 1 && start2 <= end)
		target[counter++] = copy[start1] < copy[start2] ? copy[start1++] : copy[start2++];
	while (start2 <= end)
		target[counter++] = copy[start2++];
	while (start1 <= mid - 1)
		target[counter++] = copy[start1++];
	for (int i = start; i <= end; i++)
	{
		copy[i] = target[i];
	}
}

/*��������
**�Կ�������ķ�����������vector
*/

void Template::quick_sort(vector<int> &target)
{
	quick_sort_recursive(target, 0, target.size() - 1);
}
void Template::quick_sort_recursive(vector<int> &target, int start, int end)
{
	if (start >= end)
		return;
	int pivot_element = target[end];
	int flag = start;
	for (int j = start; j <= end - 1; j++)
	{
		if (target[j] < pivot_element)
			std::swap(target[flag++], target[j]);
	}
	std::swap(target[flag], target[end]);
	quick_sort_recursive(target, start, flag - 1);
	quick_sort_recursive(target, flag + 1, end);
}