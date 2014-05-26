#define _CRT_SECURE_NO_WARNINGS
#define DEBUG

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class ED
{
	int n, m;
	string s, t;
	vector<string> res;

	int div(const char c1, const char c2) const
	{
		return !(c1 == c2);
	}

	void Hirshberg(int s1, int s2, int t1, int t2)
	{
		if (t1 == t2)
		for (int i = s2 - 1; i >= s1; --i)
		{
			char str[100] = "";
			sprintf(str, "Insert %c to %d position", s[i], t1 + 1);
			res.push_back(str);
		}
		else if (s1 == s2 - 1)
		{
			bool flag = false;
			for (int i = t2 - 1; i >= t1; --i)
			if (flag || t[i] != s[s1])
			{
				char str[100] = "";
				sprintf(str, "Delete %d symbol", i + 1);
				res.push_back(str);
			}
			else if (t[i] == s[s1])
				flag = true;
			if (!flag)
			{
				res.pop_back();
				char str[100] = "";
				sprintf(str, "Change %d symbol to %c", t1 + 1, s[s1]);
				res.push_back(str);
			}
		}
		else
		{
			int s3 = s2 - s1 + 1,
				t3 = t2 - t1 + 1;
			vector<int> dl(t3), dr(t3), tdl(t3), tdr(t3);
			for (int i = 0; i < t3; ++i)
				tdl[i] = dl[i] = i;
			int s4 = s3 / 2;
			for (int i = 1; i <= s4; ++i)
			{
				dl[0] = i;
				for (int j = 1; j < t3; ++j)
				if (s[s1 + i - 1] == t[t1 + j - 1])
					dl[j] = tdl[j - 1];
				else
					dl[j] = 1 + min(min(tdl[j], tdl[j - 1]), dl[j - 1]);
				if (i < s4)
					tdl.swap(dl);
			}
			for (int i = 0; i < t3; ++i)
				tdr[i] = dr[i] = t3 - i - 1;
			for (int i = s3 - 1; i > s4; --i)
			{
				dr[t3 - 1] = s3 - i;
				for (int j = t3 - 2; j >= 0; --j)
				if (s[s1 + i - 1] == t[t1 + j])
					dr[j] = tdr[j + 1];
				else
					dr[j] = 1 + min(min(tdr[j], tdr[j + 1]), dr[j + 1]);
				if (i > s4 + 1)
					tdr.swap(dr);
			}
			int mn = s3 + t3,
				t4 = 0;
			for (int i = 0; i < t3; ++i)
			if (dl[i] + dr[i] < mn)
			{
				mn = dl[i] + dr[i];
				t4 = i;
			}
			s4 += s1;
			t4 += t1;
			dl.clear();
			dr.clear();
			tdl.clear();
			tdr.clear();
			Hirshberg(s4, s2, t4, t2);
			Hirshberg(s1, s4, t1, t4);
		}
	}

	int Simple() const
	{
		vector< vector<int> > d(n + 1, vector<int>(m + 1, 0));
		for (int i = 1; i <= n; ++i)
			d[i][0] = i;
		for (int j = 1; j <= m; ++j)
			d[0][j] = j;
		for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			d[i][j] = min(min(d[i][j - 1], d[i - 1][j]) + 1, d[i - 1][j - 1] + div(s[i - 1], t[j - 1]));
		return d[n][m];
	}

public:
	ED(string S, string T)
		: s(S), t(T)
	{
		n = s.length(),
			m = t.length();
	}

	void getSimple() const
	{
		cout << "SIMPLE: " << Simple() << endl;
	}

	void getHirshberg()
	{
		Hirshberg(0, n, 0, m);
		cout /*<< "HIRSHBERG: " */<< res.size() << endl;
		/*for (int i = 0; i < res.size(); ++i)
			cout << res[i] << endl;*/
	}
};

int main()
{
	string s, t;
	cin >> s >> t;
	ED ed(s, t);
	ed.getHirshberg();
}