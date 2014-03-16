#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string s;
vector <vector <int>> d;

int calc_d(int l, int r)
{
	if (l > r)
		return d[l][r] = 0;
	if (l == r)
		return d[l][r] = 1;
	if (l == r - 1)
		return d[l][r] = (s[l] == s[r]);
	if (d[l][r] == -1)
	{
		if (s[l] == s[r])
			d[l][r] = calc_d(l + 1, r - 1) + 2;
		else
			d[l][r] = max(calc_d(l + 1, r), calc_d(l, r - 1));
	}
	return d[l][r];
}

void main()
{
	cin >> s;
	int n = s.length();

	d.assign(n, vector<int>(n, -1));
	calc_d(0, n - 1);

	int l = 0,
		r = n - 1,
		L = 0,
		R = d[0][n - 1];
	string ans(R+1, ' ');
	while (l <= r)
	{
		if (l == r && d[l][r] == 1)
			ans[L++] = s[l++];
		else
		if (s[l] == s[r])
		{
			ans[L++] = s[l++];
			ans[R--] = s[r--];
		}
		else
		if (d[l + 1][r] > d[l][r - 1])
			++l;
		else
			--r;
	}
	cout << d[0][n-1] << endl << ans << endl;
}