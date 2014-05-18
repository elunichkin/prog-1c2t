#define DEBUG
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct Graph
{
	int size;
	vector< vector<int> > g;
	vector<int> degin, degout;

	Graph(vector<vector<int>> G)
		: g(G), size(G.size())
	{
		degin.resize(size);
		degout.resize(size);
		for (int i = 0; i < size; ++i)
		for (int j = 0; j < g[i].size(); ++j)
		{
			++degout[i];
			++degin[g[i][j]];
		}
	}
};

class EulerCycle
{
	Graph g;
	
	bool find(vector<int> &cycle)
	{
		int first = 0;
		for (int i = 0; i < g.size; ++i)
		{
			if (g.degin[i] != g.degout[i])
				return false;
			if (!g.degin[i])
				++first;
		}
		if (first == g.size)
			return true;
		stack<int> st;
		st.push(first);
		while (!st.empty())
		{
			int u = st.top();
			bool added = false;
			for (int i = 0; i < g.g[u].size(); ++i)
			{
				st.push(g.g[u][i]);
				g.g[u][i] = g.g[u][g.g[u].size() - 1];
				g.g[u].pop_back();
				added = true;
				break;
			}
			if (!added)
			{
				cycle.push_back(u);
				st.pop();
			}
		}
		return true;
	}

public:
	bool getcycle(vector<int> &cycle)
	{
		return find(cycle);
	}

	EulerCycle(vector<vector<int>> G)
		: g(G)
	{}
};

int main()
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;
		g[u].push_back(v);
	}
	EulerCycle ec = g;
	vector<int> cycle;
	if (!ec.getcycle(cycle))
		cout << -1;
	else
	{
		reverse(cycle.begin(), cycle.end());
		for (int i = 0; i < cycle.size(); ++i)
			cout << cycle[i] + 1 << " ";
	}

	return 0;
}