// ACM_Template.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Template.h"
#include <iostream>
int main()
{
	Template obj;
	/*unit test for Eratosthenes Sieve
	int n;
	cin >> n;
	vector<bool> prime_number_list = obj.Eratosthenes_Sieve(n);
	for (int i = 0; i <= n; i++)
	{
		if (!prime_number_list[i])
			cout << i << " ";
	}
	*/

	/*unit test for gcd
	int a, b;
	cin >> a >> b;
	cout << obj.gcd(a, b);
	*/

	/*unit test for ex_gcd
	int a, b, x, y;
	cin >> a >> b;
	obj.ex_gcd(a, b, x, y);
	cout << x << " " << y;
	*/
	int n;
	cin >> n;
	vector<int> res = obj.Prime_Factor(n);
	for (int a : res)
	{
		cout << a << " ";
	}
    return 0;
}

