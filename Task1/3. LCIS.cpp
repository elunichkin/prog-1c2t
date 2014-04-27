#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class LCIS
{
	vector<int> a, b;

	vector<int> lcis()
	{
		int n = a.size() - 1,
			m = b.size() - 1;
		vector<int> p(m + 1);
		vector < vector<int> > d(n + 1, vector<int>(m + 1));

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
			return *(new vector<int>);
		}
		vector <int> ans;
		while (ans_pos)
		{
			ans.push_back(b[ans_pos]);
			ans_pos = p[ans_pos];
		}
		reverse(ans.begin(), ans.end());

		return ans;
	}

public:
	LCIS(vector<int> A, vector<int> B)
		: a(A), b(B)
	{}

	vector<int> getans()
	{
		return lcis();
	}
};

int n, m;
vector <int> a, b;

void main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;
	a.resize(n+1);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> m;
	b.resize(m+1);
	for (int j = 1; j <= m; ++j)
		cin >> b[j];
	
	LCIS L(a, b);
	vector<int> ans = L.getans();

	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << " ";
}