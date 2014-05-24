#define _CRT_SECURE_NO_WARNINGS
#define DEBUG

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Assignment
{
	int n, cost;
	vector< vector<int> > a;
	vector<int> ans;

	void assignment()
	{
		vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
		for (int i = 0; i <= n; ++i)
		{
			p[0] = i;
			int j0 = 0;
			vector<int> minv(n + 1, INT_MAX);
			vector<bool> used(n + 1, false);
			do
			{
				used[j0] = true;
				int i0 = p[j0],
					delta = INT_MAX,
					j1;
				for (int j = 1; j <= n; ++j)
				if (!used[j])
				{
					int cur = a[i0][j] - u[i0] - v[j];
					if (cur < minv[j])
						minv[j] = cur,
						way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j],
						j1 = j;
				}
				for (int j = 0; j <= n; ++j)
				if (used[j])
					u[p[j]] += delta,
					v[j] -= delta;
				else
					minv[j] -= delta;
				j0 = j1;
			} while (p[j0]);
			do
			{
				int j1 = way[j0];
				p[j0] = p[j1];
				j0 = j1;
			} while (j0);
		}
		for (int j = 1; j <= n; ++j)
			ans[p[j]] = j;
		cost = -v[0];
	}

public:
	void getans()
	{
		assignment();
		for (int i = 1; i <= n; ++i)
			printf("%d - %d\n", i, ans[i]);
	}

	Assignment(vector<vector<int>> A)
		: a(A), n(A.size() - 1), ans(A.size()), cost(0)
	{}
};

int main()
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;
	vector< vector<int> > a(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
		cin >> a[i][j];
	Assignment as = a;
	as.getans();

	return 0;
}