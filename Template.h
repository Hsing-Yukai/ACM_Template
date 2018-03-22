#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <list>
#include <queue>
#include <utility>
#include <unordered_map>
#include <iostream>
using namespace std;

class Template
{
public:
	vector<bool> Eratosthenes_Sieve(int n);                                     /* Eratosthenesɸ�� */
	int gcd(int a, int b);                                                      /* ŷ������㷨 */
	void ex_gcd(int a, int b, int &x, int &y);                                  /* ��չŷ������㷨 */
	vector<int> Prime_Factor(int n);                                            /* �ֽ������� */
	void merge_sort(vector<int> &target);                                       /* �鲢���� */
	void quick_sort(vector<int> &target);                                       /* �������� */
	vector<int> topological_sort(vector<list<int>> adjacency_list);             /* �������� */
	int Longest_substring(string s);                                            /* ����ظ��Ӵ� */
	pair<int, int> manacher(string &s);                                         /* Manacher�㷨(�����)*/
	int KMP(string a, string b);                                                /* KMP(�ַ���ƥ��)*/
	class union_find                                                            /* ���鼯(��Ȩ�Ż�)*/
	{
	public:
		union_find(int n);				//��ʼ��(������n����)
		int find(int x);				//��ȡ��x��������ͨ������id
		void Union(int x1, int x2);		//���ӵ�x1��x2
	private:
		vector<int> id;					//ÿ������������ͨ������id
		vector<int> weight;				//ÿ����ͨ���������ĵ���(Ȩ��)
	};
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

/*��������
**�Դ����еķ�ʽ��ͼ������������
**���ز���Ϊ����󶥵��˳��
***���ͣ�0�����������Ϊ0�Ķ���������
***		1�����ϵĵ��������еĶ���Ԫ�أ�ÿ����һ������Ԫ�أ���Ǵ˶��㲢����������1��Ȼ��ͨ���ڽ��б���ʴ˶���ָ������ж���
***		3����ÿ���������ȼ�1������1�����Ϊ0�򽫴˶��������� ���ص�0��
*/

vector<int> Template::topological_sort(vector<list<int>> adjacency_list)
{
	map<int, int> vertices_indgree;										//ȫ���������ȱ� firstΪ�������� secondΪ�˶�������
	vector<int> res;													//������������ж�����±�� firstΪ�������� secondΪ�˶���������λ��
	bool cycle_found = false;											//����⵽ͼ���л���cycle_found = true��

	//������ȱ�
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		vertices_indgree.insert({ i,0 });
	}
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		for (auto itr = adjacency_list[i].begin(); itr != adjacency_list[i].end(); itr++)
		{
			vertices_indgree[*itr]++;
		}
	}
	//�������

	queue<pair<int, int>> que;
	int counter = 0;
	for (int i = 0; i < vertices_indgree.size(); i++)
	{
		if (vertices_indgree[i] == 0)
		{
			que.push({ i,vertices_indgree[i] });
		}
	}
	while (!que.empty())
	{
		pair<int, int> vertice = que.front();
		que.pop();
		res.push_back(vertice.first);
		counter++;
		vertices_indgree[vertice.first] = -1;						//��Ǵ˶������Ϊ-1��ȷ�������ڷ��ʴ˶���
		for (auto itr = adjacency_list[vertice.first].begin(); itr != adjacency_list[vertice.first].end(); itr++)
		{
			if (--vertices_indgree[*itr] == 0)
			{
				que.push({ *itr,vertices_indgree[*itr] });
			}
		}
	}
	if (counter != vertices_indgree.size())
	{
		cycle_found = true;
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
	for (int high = 0; high < length; high++)
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

/*Mannacher�㷨(�����)
**���ز�����first��������ĳ���, second��������ĵĶԳƵ�λ��
***���ͣ�0��ͨ�����ַ����в��������������ĳ�����ż�Ե�����(��ʱ���ĵĳ��ȱض�Ϊ����)
***     1��ͨ��radius[i]��ʾ�Ե�i���ַ�Ϊ�Գ���ʱ���ĵİ뾶������ #a#a#�İ뾶Ϊ3,�Զ��׼��뾶�ĳ���-1��Ϊ��ȥ������Ļ��ĵĳ���, aa��Ϊ2
***     2��ͨ��max_right��ʾ���������ʹ��Ļ����ַ������ܽӴ��������Ҷ˵�λ�ã�max_right_pos��ʾ�˻��ĶԳ������ڵ�λ��
***     3����i>max_right�������λ�ô�δ��̽�������ʱ��radius[i]Ϊ1
***        ��i<max_right���ʱ�۲�i����max_right_pos�ĶԳƵ�j��2*max_right_pos-i)
***            �� ��jΪ��Ĵ�������� �� ��max_right_posΪ��Ĵ�������� ���ұߴ�ʱ��radius[i]Ϊradius[j]
***            �� ��jΪ��Ĵ�������� �� ��max_right_posΪ��Ĵ�������� ����ߴ�ʱ��radius[i]Ϊmax_right-i
***            ��ʱ�ɵ����radius[i] = min(radius[2*max_right_pos-i],max_right-i);
***     4�����radius[i]�������iΪ�����̽�⣬�����������ַ������ʱ��ֹ��ÿ��̽��ɹ����radius[i]++
***     5��̽����Ϻ��Ը���max_right,max_right_pos��res
*/

pair<int, int> Template::manacher(string &s)
{
	//���ַ���������
	char spliter = 1;
	string s_new;
	for (int i = 0; i < s.length(); i++)
	{
		s_new.push_back(spliter);
		s_new.push_back(s[i]);
	}
	s_new.push_back(spliter);
	s = s_new;
	vector<int> radius(s.length(), 0);
	//�������
	pair<int, int> res = { 0,0 }; 
	int max_right = 0;
	int max_right_pos = 0;
	for (int i = 0; i < s.length(); i++)
	{
		i < max_right ? radius[i] = min(radius[2 * max_right_pos - i], max_right - i) : radius[i] = 1;
		while (i - radius[i] >= 0 && i + radius[i] < s.length() && s[i - radius[i]] == s[i + radius[i]])
			radius[i]++;
		if (radius[i] + i - 1 > max_right)
		{
			max_right = radius[i] + i - 1;
			max_right_pos = i;
		}
		if (res.first < radius[i] - 1)
		{
			res.first = radius[i] - 1;
			res.second = i;
		}
	}
	return res;
}

/*KMP�㷨(�ַ���ƥ��)
**
*/

int Template::KMP(string a, string b)
{
	//��������ƥ���
	int b_length = b.length();
	vector<int> partial_match_table(b_length, 0);
	partial_match_table[0] =  -1;
	int j = -1;
	for (int i = 1; i < b_length; i++)
	{
		while (j > -1 && b[j + 1] != b[i])
			j = partial_match_table[j];
		if (b[j + 1] == b[i])
			j = j + 1;
		partial_match_table[i] = j;
	}
	//�������
	int a_length = a.length();
	j = -1;
	for (int i = 0; i < a_length; i++)
	{
		while (j >-1 && b[j + 1] != a[i])
			j = partial_match_table[j];
		if (b[j + 1] == a[i])
			j = j + 1;
		if (j == b_length - 1)
			return i - b_length + 1;
	}
	return -1;
}

/*���鼯
**ͨ����Ȩ���ķ��������Ż���ʹʱ�临�ӶȽ������
***���ͣ�1.�������Ľṹ������ʾ��ͨ��������ʼʱ��n����(n����ͨ����)
***     2.ÿ�ν���Union����ʱ��С���ĸ��ڵ�ϲ��������ĸ��ڵ��ϣ�ͬʱҲҪ���Ӵ�����Ȩֵ
***       �Ǹ��ڵ��id����������ͨ������id�����丸�ڵ������
***       ֻ�и��ڵ��id���ڸ��ڵ�����ƣ�ͬʱҲ������������ͨ������id
***     3.ÿ�ν���find����ʱ���˽ڵ�Ǹ��ڵ㣬�򲻶ϵ���ֱ���ҳ����ڵ㣬�ҳ����ڵ�󼴿ɻ�ȡ������ͨ������id
*/

Template::union_find::union_find(int n)
{
	id.resize(n);
	weight.resize(n);
	for (int i = 0; i < n; i++)
	{
		id[i] = i;
		weight[i] = 1;
	}
}
int Template::union_find::find(int x)
{
	while (x != id[x])
	{
		x = id[x];
	}
	return x;
}
void Template::union_find::Union(int x1, int x2)
{
	int x1_id = find(x1);
	int x2_id = find(x2);
	if (x1_id == x2_id)
		return;
	if (weight[x1_id] > weight[x2_id])
	{
		id[x2_id] = x1_id;
		weight[x1_id] += weight[x2_id];
	}
	else
	{
		id[x1_id] = x2_id;
		weight[x2_id] += weight[x1_id];
	}
}
