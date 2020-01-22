#include<cstdio>
#define reg register

const int MAXN=1000+5;

bool vis[MAXN];
int n,k;
int ans;
int a[MAXN];

inline void DFS(reg int);

int main(void){
	scanf("%d%d",&n,&k);
	DFS(1);
	printf("%d\n",ans%2012);
	return 0;
}

inline void DFS(reg int dep){
	reg int i;
	if(dep==n+1){
		reg int sum=0;
		for(i=1;i<n;++i)
			if(a[i]<a[i+1])
				++sum;
		if(sum==k)
			++ans;
		return;
	}
	for(i=1;i<=n;++i)
		if(!vis[i]){
			vis[i]=true;
			a[dep]=i;
			DFS(dep+1);
			a[dep]=0;
			vis[i]=false;
		}
	return;
}
