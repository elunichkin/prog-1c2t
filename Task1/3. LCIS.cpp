#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector <int> a, b, p;
vector <vector <int>> d;

void main()
{
	cin >> n;
	a.resize(n+1);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> m;
	b.resize(m+1);
	for (int j = 1; j <= m; ++j)
		cin >> b[j];
	p.resize(m+1);
	d.resize(n+1, vector<int>(m+1));
	
	for (int i = 1; i <= n; ++i)
	{
		int last = 0,
			pos = 0;
		for (int j = 1; j <= m; ++j)
		{
			d[i][j] = d[i - 1][j];
			if (a[i] == b[j] && d[i - 1][j] < last + 1)
			{
				d[i][j] = last + 1;
				p[j] = pos;
			}
			if (a[i] > b[j] && d[i - 1][j] > last)
			{
				last = d[i - 1][j];
				pos = j;
			}
		}
	}
	int ans_pos = 1;
	for (int j = 2; j <= m; ++j)
	{
		if (d[n][j] > d[n][ans_pos])
			ans_pos = j;
	}
	if (!d[n][ans_pos])
	{
		cout << 0 << endl;
		return;
	}
	vector <int> ans;
	while (ans_pos)
	{
		ans.push_back(b[ans_pos]);
		ans_pos = p[ans_pos];
	}
	reverse(ans.begin(), ans.end());

	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << " ";
}