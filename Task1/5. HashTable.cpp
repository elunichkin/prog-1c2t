#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
#include <climits>
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
		bool Empty()
		{
			return !table->size();
		}

	public:
		string& operator*()
		{
			if (Empty())
				throw logic_error("ERROR!\nIterator: Empty!");
			return table->at(x)[y];
		}

		Iterator operator++()
		{
			if (Empty())
				throw logic_error("ERROR!\nIterator: Empty!");
			if (x == table->size() - 1 && y == table->at(x).size())
				throw logic_error("ERROR!\nIterator: Out of range!");
			if (x < table->size() - 1 && y == table->at(x).size() - 1)
			{
				++x;
				y = 0;
			}
			else
				++y;
			return *this;
		}

		Iterator operator--()
		{
			if (Empty())
				throw logic_error("ERROR!\nIterator: Empty!");
			if (!x && !y)
				throw logic_error("ERROR!\nIterator: Out of range!");
			if (!y)
			{
				--x;
				y = table->at(x).size() - 1;
			}
			else
				--y;
			return *this;
		}

		string& operator->()
		{
			if (Empty())
				throw logic_error("ERROR!\nIterator: Empty!");
			return table->at(x)[y];
		}

		bool operator==(Iterator other)
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(Iterator other)
		{
			return (x != other.x || y != other.y);
		}

		Iterator(HashTable *h)
			: table(&h->table)
		{}

		Iterator(HashTable *h, int X, int Y)
			: Iterator(h)
		{
			x = X;
			y = Y;
			if (x < 0 || y < 0)
				throw logic_error("ERROR!\nIterator: Out of range!");
			if (x >= table->size())
				throw logic_error("ERROR!\nIterator: Out of range!");
			if (y > table->at(x).size())
				throw logic_error("ERROR!\nIterator: Out of range!");
		}
	};

	Iterator begin()
	{
		return Iterator(this, 0, 0);
	}

	Iterator end()
	{
		return Iterator(this, size - 1, table[size - 1].size());
	}

	HashTable()
		:size(0), elements(0)
	{}
};

void Test1()
{
	HashTable hash;
	set<string> s;
	srand(1);
	for (int i = 0; i < 100; ++i)
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
		printf("%s: %s\n", str.c_str(), (s.count(str) ? "OK" : "ERROR"));
		++it;
	}
	if (it != hash.end())
		printf("Too big HashTable\n");
}

int main()
{
	Test1();

	system("pause");
	return 0;
}