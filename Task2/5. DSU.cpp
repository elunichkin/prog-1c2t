#include <iostream>
#include <vector>
#include <set>
using namespace std;

class DSU
{
	vector<int> parent;
	vector<int> rank;

public:
	DSU(int n)
		: rank(n, 1), parent(n)
	{
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	int find(int node)
	{
		if (parent[node] == node)
			return node;
		else
			return parent[node] = find(parent[node]);
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

};
int main()
{
	int n, roads;
	cin >> n >> roads;
	DSU dsu(n + 1);
	for (int i = 0; i < roads; i++)
	{
		int s, f;
		cin >> s >> f;
		dsu.unite(s, f);
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int s, f;
		cin >> s >> f;
		if (dsu.find(s) == dsu.find(f))
			cout << "Vertices belong to one set \n";
		else
			cout << "Vertices belong to different sets";
	}

	return 0;
}