#define DEBUG
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Cubes
{
	int n, k;
	vector< vector<int> > g;
	vector<int> mt;
	vector<bool> used;

	bool dfs(int u)
	{
		if (used[u])
			return false;
		used[u] = true;
		for (int i = 0; i < g[u].size(); ++i)
		{
			int v = g[u][i];
			if (mt[v] == -1 || dfs(mt[v]))
			{
				mt[v] = u;
				return true;
			}
		}
		return false;
	}

	void kuhn()
	{
		if (n > k)
		{
			cout << "NO\n";
			return;
		}
		for (int i = 0; i < n; ++i)
		{
			used.assign(n, false);
			dfs(i);
		}
		vector< pair<int, int> > ans;
		for (int i = 0; i < k; ++i)
		if (mt[i] != -1)
			ans.push_back(make_pair(mt[i], i));
		if (ans.size() < k)
		{
			cout << "NO\n";
			return;
		}
		cout << "YES\n";
		sort(ans.begin(), ans.end());
		for (int i = 0; i < k; ++i)
			cout << ans[i].second + 1 << ' ';
		cout << endl;
	}

public:
	void getans()
	{
		kuhn();
	}

	Cubes(int N, int K, vector<vector<int>> G)
		: n(N), k(K), g(G)
	{
		mt.assign(k, -1);
	}
};

int main()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<char> word;
	for (int i = 0; i < s.size(); ++i)
		word.push_back(s[i]);
	int k = word.size();
	vector< vector<int> > g(k);
	vector< vector<char> > cubes(n);
	for (int i = 0; i < n; ++i)
	{
		string t;
		cin >> t;
		for (int j = 0; j < t.size(); ++j)
			cubes[i].push_back(t[j]);
	}

	for (int i = 0; i < n; ++i)
	for (int j = 0; j < cubes[i].size(); ++j)
	for (int h = 0; h < k; ++h)
	if (cubes[i][j] == word[h])
		g[h].push_back(i);
	Cubes c(k, n, g);
	c.getans();

	return 0;
}