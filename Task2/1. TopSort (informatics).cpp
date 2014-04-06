#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <random>
using namespace std;

class TopSort
{
	int size;
	vector<vector<int>> g;

	vector<int> topsort()
	{
		stack<int> dfs_stack;
		vector<int> color(size, 0),
			stack_size(size, 0),
			ans;
		for (int j = 0; j < size; ++j)
		{
			if (color[j] == 0)
			{
				dfs_stack.push(j);
				stack_size[j] = dfs_stack.size();
			}
			else continue;
			while (!dfs_stack.empty())
			{
				int u = dfs_stack.top();
				if (color[u] == 3)
				{
					dfs_stack.pop();
					continue;
				}
				if (color[u] == 2)
				{
					ans.push_back(u + 1);
					dfs_stack.pop();
					color[u] = 3;
					continue;
				}
				if (color[u] == 1)
				{
					if (dfs_stack.size() > stack_size[u])
						throw runtime_error("CYCLE!");
					color[u] = 2;
					continue;
				}
				color[u] = 1;
				stack_size[u] = dfs_stack.size();
				for (int i = 0; i < g[u].size(); ++i)
				{
					int v = g[u][i];
					dfs_stack.push(v);
				}
			}
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}

public:
	TopSort(vector<vector<int>> G)
		: g(G), size(G.size())
	{}

	vector<int> get_topsort()
	{
		return topsort();
	}
};

int main()
{
//#ifdef DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
//#endif

	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	vector<vector<bool>> used(n, vector<bool>(n, false));
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		--u; --v;
		if (used[u][v])
			continue;
		used[u][v] = true;
		g[u].push_back(v);
	}
	TopSort T = g;
	try
	{
		vector<int> ans = T.get_topsort();
		cout << "Yes" << endl;
		for (int i = 0; i < n; ++i)
			cout << ans[i] << " ";
	}
	catch (exception ex)
	{
		cout << "No";
	}
	return 0;
}