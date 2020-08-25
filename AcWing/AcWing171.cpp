#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=46+5;

int n;
ll w,g[MAXN];
int cnt;
ll V[1<<23];
int p,q;
ll ans=0;

inline void dfs1(reg int dep,reg ll sum){
	if(dep>p){
		V[++cnt]=sum;
		return;
	}
	dfs1(dep+1,sum);
	if(sum+g[dep]<=w)
		dfs1(dep+1,sum+g[dep]);
	return;
}

inline void dfs2(reg int dep,reg ll sum){
	if(dep>n){
		reg int l=1,r=cnt,mid;
		while(l<r){
			mid=(l+r+1)>>1;
			if(V[mid]<=w-sum)
				l=mid;
			else
				r=mid-1;
		}
		ans=max(ans,V[l]+sum);
		return;
	}
	dfs2(dep+1,sum);
	if(sum+g[dep]<=w)
		dfs2(dep+1,sum+g[dep]);
	return;
}

int main(void){
	scanf("%d%lld",&w,&n);
	for(reg int i=1;i<=n;++i)
		scanf("%lld",&g[i]);
	p=n/2,q=n-p;
	dfs1(1,0);
	sort(V+1,V+cnt+1);
	dfs2(p+1,0);
	printf("%lld\n",ans);
	return 0;
}