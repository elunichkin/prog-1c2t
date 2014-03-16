#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n;
vector <int> a, d;

void main()
{
	cin >> n;
	a.resize(n);
	d.assign(n + 1, INF);
	d[0] = -INF;

	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		int j = (int)(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
		if (d[j - 1] < a[i] && a[i] < d[j])
			d[j] = a[i];
	}
	
	int size = (int)(lower_bound(d.begin(), d.end(), INF) - d.begin()) - 1;
	if (size < 1)
		throw runtime_error("NO LIS!");
	cout << size << endl;
	for (int i = 1; i <= size; ++i)
		cout << d[i] << " ";
}