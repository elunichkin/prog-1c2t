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
	const int white = 0,
		gray = 1,
		black = 2;

	int size;
	vector<vector<int>> g;

	vector<int> topsort()
	{
		stack<int> dfs_stack;
		vector<int> color(size, white),
			first(size, 0),
			in_stack(size, 0),
			ans;
		for (int v = 0; v < size; ++v)
		{
			if (color[v] == white)
			{
				dfs_stack.push(v);
				++in_stack[v];
			}
			else continue;
			while (!dfs_stack.empty())
			{
				int u = dfs_stack.top();
				if (color[u] == black)
				{
					dfs_stack.pop();
					--in_stack[u];
					continue;
				}
				if (color[u] == gray)
				{
					if (in_stack[u] == 1)
					{
						color[u] = black;
						dfs_stack.pop();
						--in_stack[u];
						ans.push_back(u + 1);
						continue;
					}
					else
						throw runtime_error("CYCLE!");
				}
				color[u] = gray;
				for (int i = first[u]; i < g[u].size(); ++i)
				{
					dfs_stack.push(g[u][i]);
					++in_stack[g[u][i]];
					++first[u];
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

void Test()
{
	for (int it = 0; it < 10; ++it)
	{
		cout << "Test #" << it + 1 << endl << endl;
		srand(it);
		int n = rand() % 5 + 5;
		int m = n - 1;
		vector<int> v(n);
		vector<vector<int>> graph(n);
		for (int i = 0; i < n; ++i)
			v[i] = i;
		random_shuffle(v.begin(), v.end());
		int pt = 0;
		queue<int> q;
		while (pt < n)
		{
			q.push(v[pt++]);
			while (!q.empty() && pt < n)
			{
				int u = q.front();
				int e = rand() % 3;
				for (int j = 0; j < e && pt < n; ++j)
				{
					graph[u].push_back(v[pt]);
					q.push(v[pt++]);
				}
				q.pop();
			}
		}
		cout << "GRAPH:" << endl << n << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << i + 1 << ": ";
			for (int j = 0; j < graph[i].size(); ++j)
				cout << graph[i][j] + 1 << " ";
			cout << endl;
		}
		cout << endl << "TopSort:" << endl;
		TopSort T = graph;
		try
		{
			vector<int> ans = T.get_topsort();
			for (int i = 0; i < ans.size(); ++i)
				cout << ans[i] << " ";
			cout << endl << endl;
		}
		catch (exception ex)
		{
			cout << ex.what();
		}
	}
}

void main()
{
	Test();
	system("pause");
}