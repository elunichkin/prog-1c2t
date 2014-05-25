#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cfloat>
#include <algorithm>
using namespace std;

class FordBellman
{
	struct edge
	{
		int u, v;
		double cost;
	};

	int n, m;
	vector<edge> e;

	void fordbellman()
	{
		vector<int> d(n, 0), p(n, -1);
		d[0] = 1;
		int x;
		for (int i = 0; i < n; ++i)
		{
			x = -1;
			for (int j = 0; j < m; ++j)
			if (d[e[j].u] > 0 && d[e[j].v] < d[e[j].u] * e[j].cost)
			{
				d[e[j].v] = min(DBL_MAX, d[e[j].u] * e[j].cost);
				p[e[j].v] = e[j].u;
				x = e[j].v;
			}
		}
		cout << "FORD-BELLMAN:\n";
		if (x == -1)
		{
			cout << "NO NEGATIVE CYCLE!\n";
			return;
		}
		for (int i = 0; i < n; ++i)
			x = p[x];
		vector<int> path;
		for (int i = x;; i = p[i])
		{
			path.push_back(i);
			if (i == x && path.size() > 1)
				break;
		}
		cout << "NEGATIVE CYCLE FOUND:\n";
		for (int i = 0; i < path.size(); ++i)
			cout << path[i] + 1 << ' ';
		cout << endl;
	}

public:
	void getans()
	{
		fordbellman();
	}

	FordBellman(vector<vector<double>> a)
		: n(a.size())
	{
		for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			e.push_back({ i, j, a[i][j] });
		m = e.size();
	}
};

class Floyd
{
	int n;
	vector< vector<double> > a;
	vector< vector<int> > p;

	void floyd()
	{
		vector<int> cycle;
		int start = -1;
		bool has_cycle = false;
		for (int t = 0; t < n && start < 0; ++t)
		for (int i = 0; i < n && start < 0; ++i)
		for (int j = 0; j < n && start < 0; ++j)
		if (a[i][t] * a[t][j] < a[i][j])
		{
			a[i][j] = a[i][t] * a[t][j];
			p[i][j] = t;
			if (i == j && a[i][j] < 1)
			{
				start = i;
				break;
			}
		}
		cout << "FLOYD:\n";
		if (start >= 0)
		{
			cout << "NEGATIVE CYCLE FOUND:\n";
			findpath(start, start);
			cout << start + 1 << endl;
		}
		else
			cout << "NO NEGATIVE CYCLE!\n";
	}

	void findpath(int x, int y)
	{
		if (p[x][y] == -1 || (x == p[x][y] && y == p[x][y]))
			cout << x + 1 << ' ';
		else
		{
			findpath(x, p[x][y]);
			findpath(p[x][y], y);
		}
	}

public:
	void getans()
	{
		floyd();
	}

	Floyd(vector<vector<double>> A)
		: a(A), n(A.size())
	{
		p.assign(n, vector<int>(n, -1));
	}
};

void main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;
	vector< vector<double> > a(n, vector<double>(n));
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
		cin >> a[i][j];
	
	Floyd fl = a;
	fl.getans();
	FordBellman fb = a;
	fb.getans();
}