#include <bits/stdc++.h>
using namespace std;
int open[200005]; 
int prime[200005]; 
int yes[200005]; 
int isit[200005];
int line[700005];
int to[700005];
void push(int a, int b)
{
	to[++to[0]] = b;
	line[++line[0]] = isit[a];
	isit[a] = line[0];
}
void start(void)
{
	for (int i = 2; i <= 200000; ++i)
	{
		if (isit[i])
			continue;
		prime[++prime[0]] = i;
		for (int j = 1; i * j <= 200000; ++j)
			push(i * j, prime[0]);
	}
}
int add(int k)
{
	if (open[k])
		return -1;
	int minx = 0;
	int j = isit[k];
	while (j)
	{
		if (yes[to[j]])
			minx = max(minx, yes[to[j]]);
		j = line[j];
	} 
	if (minx > 0)
		return minx;
	j = isit[k];
	while (j)
	{
		yes[to[j]] = k;
		j = line[j];
	} 
	open[k] = 1;
	return 0;
}
int close(int k)
{
	if (!open[k])
		return -2;
	int j = isit[k];
	while (j)
	{
		yes[to[j]] = 0;
		j = line[j];
	}
	open[k] = 0;
	return 0;
}

int main()
{
	start();
	int n = 0, m = 0, ans = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		char input = '\0';
		int k = 0;
		while (input = getchar())
			if (input == '+' || input == '-')
			{
				scanf("%d", &k);
				switch (input)
				{
				case '+':
					ans = add(k);
				case '-':
					ans = close(k);
				}
			}
		else if (ans == -2)
			printf("Already off\n");
		else if (ans == -1)
			printf("Already on\n");
		else if (ans == 0)
			printf("Success\n");
		else
			printf("Conflict with %d\n", ans);
	}
	return 0;
}