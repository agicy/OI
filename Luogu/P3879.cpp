#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::cin;
using std::map;
using std::string;
using std::vector;

bool T[1001];
int n, m, l;
string temp;
map<string, vector<int> /* */> M;

int main(void)
{
	register int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i)
	{
		scanf("%d", &l);
		while (l--)
		{
			cin >> temp;
			M[temp].push_back((int)i);
		}
	}
	scanf("%d", &m);
	while (m--)
	{
		memset(T, false, sizeof(T));
		cin >> temp;
		for (i = 0; i < (int)M[temp].size(); ++i)
		{
			if (!T[M[temp][i]])
			{
				T[M[temp][i]] = true;
				printf("%d ", M[temp][i]);
			}
		}
		putchar('\n');
	}
	return 0;
}