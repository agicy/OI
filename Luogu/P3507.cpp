#include<cstdio>
#include<algorithm>
using std::max;
using std::sort;

const int MAXN=1000000+5;

int n;
int a[MAXN];
int f[MAXN];

int main(void){
	register int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(i=1;i<=n;++i)
		f[i]=max(f[i-1],a[i]-f[i-1]);
	printf("%d\n",f[n]);
	return 0;
}
