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

	void fordbellman(int u)
	{
		vector<int> d(n, 0), p(n, -1);
		d[u] = 1;
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
		cout << "FORD-BELLMAN: ";
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
		reverse(path.begin(), path.end());
		cout << "NEGATIVE CYCLE FOUND!\n";
		cout << "CYCLE:\n";
		for (int i = 0; i < path.size(); ++i)
			cout << path[i] + 1 << ' ';
		cout << endl;
	}

public:
	void getans()
	{
		fordbellman(0);
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

	void floyd(int u)
	{
		vector<int> cycle;
		int start;
		bool has_cycle = false;
		for (int t = 0; t < n && !has_cycle; ++t)
		for (int i = 0; i < n && !has_cycle; ++i)
		for (int j = 0; j < n && !has_cycle; ++j)
		if (a[i][t] < DBL_MAX && a[t][j] < DBL_MAX && a[i][t] * a[t][j] < a[i][j] - DBL_EPSILON)
		{
			a[i][j] = min(DBL_MAX, a[i][t] * a[t][j]);
			p[i][j] = t;
			if (i == j && a[i][j] < 1)
			{
				has_cycle = true;
				break;
			}
		}
		cout << "FLOYD: ";
		if (a[u][u] < 1)
			cout << "NEGATIVE CYCLE FOUND!\n";
		else
			cout << "NO NEGATIVE CYCLE!\n";
	}

public:
	void getans()
	{
		floyd(0);
	}

	Floyd(vector<vector<double>> A)
		: a(A), n(A.size())
	{
		for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			a[i][j] = -(1 / a[i][j]);
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