#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
#include <climits>
#include <Windows.h>
using namespace std;

class HashTable
{
	vector< vector<string> > table;
	int elements, size;

	int Hash(const string& s) const
	{
		int p = 1,
			hash = 0;
		for (int i = 0; i < s.length(); ++i)
		{
			hash += (s[i] - 'a' + 1) * p;
			p *= 31;
		}
		if (hash < 0)
			hash += INT_MAX;
		return hash % size;
	}

	void Reallocate()
	{
		if (size >= elements || elements / size > 4)
		{
			size = elements / 2 + 1;
			vector< vector<string> > newtable(size);
			for (int i = 0; i < table.size(); ++i)
			for (int j = 0; j < table[i].size(); ++j)
				newtable[Hash(table[i][j])].push_back(table[i][j]);
			table = newtable;
		}
	}

public:
	bool Empty() const
	{
		return !elements;
	}

	bool Find(const string& s)
	{
		if (Empty())
			return false;
		int hash = Hash(s);
		for (int i = 0; i < table[hash].size(); ++i)
		{
			if (table[hash][i] == s)
				return true;
		}
		return false;
	}

	void Add(const string& s)
	{
		if (Find(s))
			return;
		Reallocate();
		table[Hash(s)].push_back(s);
		++elements;
	}

	void Remove(const string& s)
	{
		if (!Find(s))
			throw logic_error("ERROR!\nRemove: No such string!");
		int hash = Hash(s);
		for (int i = 0; i < table[hash].size(); ++i)
		{
			if (table[hash][i] == s)
			{
				table[hash][i] = table[hash][table[hash].size() - 1];
				table[hash].pop_back();
			}
		}
		--elements;
		Reallocate();
	}

	class Iterator
	{
		vector< vector<string> > *table;
		int x, y;
		const Iterator *begin, *end;

	public:
		string& operator*()
		{
			if (*this == *end)
				throw logic_error("ERROR!\nIterator: Out of range!");
			try
			{
				return table->at(x)[y];
			}
			catch (exception ex)
			{
				throw logic_error("ERROR!\nIterator: Out of range!");
			}
		}

		Iterator operator++()
		{
			++y;
			if (y == table->at(x).size())
			{
				y = 0;
				do
				{
					++x;
				} while (x < table->size() && !table->at(x).size());
			}
			if (x == table->size())
				return *this = *end;
			return *this;
		}

		Iterator operator--()
		{
			--y;
			if (y < 0)
			{
				do
				{
					--x;
				} while (x >= 0 && !table->at(x).size());
			}
			if (x < 0)
				return *this = *end;
			y = table->at(x).size();
			return *this;
		}

		string& operator->()
		{
			if (*this == *end)
				throw logic_error("ERROR!\nIterator: Out of range!");
			try
			{
				return table->at(x)[y];
			}
			catch (exception ex)
			{
				throw logic_error("ERROR!\nIterator: Out of range!");
			}
		}

		bool operator==(Iterator other)
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(Iterator other)
		{
			return (x != other.x || y != other.y);
		}

		Iterator(HashTable *h, int X, int Y)
			: table(&h->table), x(X), y(Y)
		{
			begin = &h->it_begin;
			end = &h->it_end;
		}

		Iterator(HashTable *h)
		{
			*this = h->it_begin;
		}
	};

	const Iterator begin()
	{
		int x = 0;
		while (x < table.size() && !table[x].size())
			++x;
		if (x == table.size())
			return end();
		return Iterator(this, x, 0);
	}

	const Iterator end()
	{
		return Iterator(this, INT_MAX, INT_MAX);
	}

	const Iterator it_begin = begin(),
		it_end = end();

	HashTable()
		:size(0), elements(0)
	{}
};

void Test1()
{
	HashTable hash;
	set<string> s;
	srand(time(NULL));
	int n = rand() % 100000 + 10;
	for (int i = 0; i < n; ++i)
	{
		string str;
		int size = rand() % 20 + 1;
		for (int j = 0; j < size; ++j)
			str.push_back(rand() % 26 + 'a');
		s.insert(str);
		hash.Add(str);
		printf("Added string #%d: %s\n", i + 1, str.c_str());
	}
	printf("\nList of string in table:\n");
	HashTable::Iterator it = hash.begin();
	for (int i = 0; i < s.size(); ++i)
	{
		string str = *it;
		printf("%d: %s - %s\n", i + 1, str.c_str(), (s.count(str) ? "OK" : "ERROR"));
		++it;
	}
	if (it != hash.end())
		printf("\nToo big HashTable\n");
	else
		printf("\n...OK %d strings...\n", s.size());
}

int main()
{
	Test1();

	system("pause");
	return 0;
}