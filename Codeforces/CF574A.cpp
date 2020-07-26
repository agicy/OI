#include <cstdio>
#include <algorithm>
using std::sort;

int n, vote, a[101];

int main(void){
	register int i, ans = 0;
	scanf("%d%d", &n, &vote);
	for (i=1; i<n; ++i)
		scanf("%d", &a[i]);
	sort(a+1,a+n);
	while (a[n - 1] >= vote)
	{
		--a[n-1];
		sort(a+1,a+n);
		++vote;
		++ans;
	}
	printf("%d\n", ans);
	return 0;
}