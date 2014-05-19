#define DEBUG
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

class Kosaraju
{
	int size;
	vector< vector<int> > g, gt;
	vector<bool> used;
	vector<int> order, component;

	void dfs1(int u)
	{
		used[u] = true;
		for (int i = 0; i < g[u].size(); ++i)
		if (!used[g[u][i]])
			dfs1(g[u][i]);
		order.push_back(u);
	}

	void dfs2(int u)
	{
		used[u] = true;
		component.push_back(u);
		for (int i = 0; i < gt[u].size(); ++i)
		if (!used[gt[u][i]])
			dfs2(gt[u][i]);
	}

	void kosaraju()
	{
		used.assign(size, false);
		for (int i = 0; i < size; ++i)
		if (!used[i])
			dfs1(i);
		used.assign(size, false);
		int num = 0;
		cout << "KOSARAJU:\n";
		for (int i = 0; i < size; ++i)
		{
			int u = order[size - i - 1];
			if (!used[u])
			{
				dfs2(u);
				printf("Component #%d:\n", ++num);
				for (int j = 0; j < component.size(); ++j)
					cout << component[j] + 1 << " ";
				cout << endl;
				component.clear();
			}
		}
		cout << endl;
	}

public:
	void getans()
	{
		kosaraju();
	}

	Kosaraju(vector<vector<int>> G)
		: g(G), size(G.size())
	{
		gt.resize(size);
		for (int i = 0; i < size; ++i)
		for (int j = 0; j < g[i].size(); ++j)
			gt[g[i][j]].push_back(i);
	}
};

class Tarjan
{
	int size, t;
	vector< vector<int> > g, components;
	vector<bool> used;
	vector<int> low;
	stack<int> st;

	void dfs(int u)
	{
		low[u] = t++;
		used[u] = true;
		st.push(u);
		bool isroot = true;
		for (int i = 0; i < g[u].size(); ++i)
		{
			int v = g[u][i];
			if (!used[v])
				dfs(v);
			if (low[u] > low[v])
			{
				low[u] = low[v];
				isroot = false;
			}
		}
		if (isroot)
		{
			vector<int> component;
			while (true)
			{
				int k = st.top();
				st.pop();
				component.push_back(k);
				low[k] = INT_MAX;
				if (k == u)
					break;
			}
			components.push_back(component);
		}
	}

	void tarjan()
	{
		for (int i = 0; i < size; ++i)
		if (!used[i])
			dfs(i);
		cout << "TARJAN:\n";
		for (int i = 0; i < components.size(); ++i)
		{
			printf("Component #%d:\n", i + 1);
			for (int j = 0; j < components[i].size(); ++j)
				cout << components[i][j] + 1 << " ";
			cout << endl;
		}
	}

public:
	void getans()
	{
		tarjan();
	}

	Tarjan(vector<vector<int>> G)
		: g(G), size(G.size()), t(0)
	{
		used.assign(size, false);
		low.assign(size, 0);
	}
};

int main()
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;
	vector< vector<int> > g(n);
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;
		g[u].push_back(v);
	}

	Kosaraju kos = g;
	kos.getans();
	Tarjan tar = g;
	tar.getans();

	return 0;
}