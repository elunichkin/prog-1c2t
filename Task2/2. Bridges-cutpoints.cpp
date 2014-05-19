#define DEBUG
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BC
{
	int size, t;
	vector< vector<int> > g;
	vector<bool> used;
	vector<int> tin, fup;
	vector< pair<int, int> > br;
	vector<int> cutp;

	void dfs(int u, int p = -1)
	{
		used[u] = true;
		tin[u] = fup[u] = t++;
		int children = 0;
		for (int i = 0; i < g[u].size(); ++i)
		{
			int v = g[u][i];
			if (v == p)
				continue;
			if (used[v])
				fup[u] = min(fup[u], tin[v]);
			else
			{
				dfs(v, u);
				fup[u] = min(fup[u], fup[v]);
				if (fup[v] > tin[u])
					br.push_back(make_pair(u, v));
				if (fup[v] >= tin[u] && p != -1)
					cutp.push_back(u);
				++children;
			}
		}
		if (p == -1 && children > 1)
			cutp.push_back(u);
	}

	void bc()
	{
		for (int i = 0; i < size; ++i)
		if (!used[i])
			dfs(i);
		cout << "BRIDGES:\n";
		for (int i = 0; i < br.size(); ++i)
			cout << br[i].first + 1 << " " << br[i].second + 1 << endl;
		cout << "\nCUTPOINTS:\n";
		for (int i = 0; i < cutp.size(); ++i)
			cout << cutp[i] + 1 << endl;
	}

public:
	void getans()
	{
		bc();
	}

	BC(vector<vector<int>> G)
		: g(G), size(G.size()), t(0)
	{
		used.assign(size, false);
		tin.assign(size, 0);
		fup.assign(size, 0);
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
		g[v].push_back(u);
	}

	BC bc = g;
	bc.getans();

	return 0;
}