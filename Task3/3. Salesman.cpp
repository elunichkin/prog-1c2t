#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Salesman
{
	class DSU
	{
		vector<int> parent, rank;

	public:
		int find(int a)
		{
			if (parent[a] == a)
				return a;
			return parent[a] = find(parent[a]);
		}

		void unite(int a, int b)
		{
			a = find(a);
			b = find(b);
			if (a != b)
			{
				if (rank[a] < rank[b])
					swap(a, b);
				parent[b] = a;
				if (rank[a] == rank[b])
					++rank[a];
			}
		}

		DSU(int size)
			: parent(size),
			rank(size, 1)
		{
			for (int i = 0; i < size; ++i)
				parent[i] = i;
		}
	};

	struct edge
	{
		int a, b;
		double len;
		bool operator< (const edge &other)
		{
			return len < other.len;
		}
	};

	struct point
	{
		double x, y;
		point& operator+= (const point& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
	};

	static double sqr(const double a)
	{
		return a*a;
	}

	static double dist(const double x, const double y)
	{
		return sqrt(sqr(x) + sqr(y));
	}

	static double dist(point a, point b)
	{
		return sqrt(sqr(b.x - a.x) + sqr(b.y - a.y));
	}

	const static int
		S1 = 100,
		S2 = 10,
		N = 20,
		M = 20;

	int n;
	vector<edge> e, anse;
	vector<point> v;
	vector <vector<int> > g;
	vector<int> ansv;
	vector<bool> used;
	DSU dsu;

	point rand_point(int sigma)
	{
		double x, y, d;
		do
		{
			x = (double)rand() / RAND_MAX * 2 - 1;
			y = (double)rand() / RAND_MAX * 2 - 1;
			d = dist(x, y);
		} while (d > 1 || !d);;
		double t = sqrt(-2 * log(d) / d);
		return{ x*t*sigma, x*t*sigma };
	}

	void generate()
	{
		for (int i = 0; i < N; ++i)
		{
			point centre = rand_point(S1);
			for (int j = 0; j < M; ++j)
			{
				point city = rand_point(S2);
				city += centre;
				v.push_back(city);
			}
		}
	}

	void dfs(int u)
	{
		if (!used[u])
		{
			used[u] = true;
			ansv.push_back(u);
			for (int i = 0; i < g[u].size(); ++i)
				dfs(g[u][i]);
		}
	}

	void solve()
	{
		generate();

		for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		if (i != j)
		{
			double d = dist(v[j].x - v[i].x, v[j].y - v[i].y);
			e.push_back({ i, j, d });
		}
		sort(e.begin(), e.end());
		for (int i = 0; i < e.size(); ++i)
		if (dsu.find(e[i].a) != dsu.find(e[i].b))
		{
			dsu.unite(e[i].a, e[i].b);
			anse.push_back(e[i]);
		}

		for (int i = 0; i < anse.size(); ++i)
		{
			g[anse[i].a].push_back(anse[i].b);
			g[anse[i].b].push_back(anse[i].a);
		}
		dfs(e[0].a);

		double ans = 0;
		for (int i = 1; i < ansv.size(); ++i)
			ans += dist(v[ansv[i]], v[ansv[i - 1]]);
		ans += dist(v[ansv.back()], v[ansv.front()]);

		double simple_ans = 0;
		for (int i = 1; i < v.size(); ++i)
			simple_ans += dist(v[i], v[i - 1]);
		simple_ans += dist(v.back(), v.front());

		cout.precision(16);
		cout << "Simple distance: " << fixed << simple_ans << endl;
		cout << "Your distance: " << fixed << ans << endl;
		if (ans <= simple_ans)
			cout << "OK!\n";
		else
			cout << "FUCKED UP!\n";
		for (int i = 0; i < ansv.size(); ++i)
			cout << ansv[i] + 1 << ' ';
		cout << endl;
	}

	Salesman(int N)
		: n(N),
		dsu(n),
		g(n, vector<int>(n, 0)),
		used(n, false)
	{}

public:
	void getans()
	{
		solve();
	}

	Salesman()
		: Salesman(N*M)
	{}
};

void main()
{
	Salesman s;
	s.getans();
	system("pause");
}