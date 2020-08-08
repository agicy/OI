#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e5+5;

bitset<MAXSIZE> vis;
int tot,prime[MAXSIZE];
int mu[MAXSIZE];

inline void Init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			mu[i]=-1;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	return;
}

inline ll calc(reg int x,reg int y){
	reg ll res=0;
	reg int z=x<<1;
	if(!y)
		return 0;
	for(reg int i=x+1;i<z;i=x+1){
		if(!(y/i))
			return res;
		x=min(y/(y/i),z-1);
		res+=(x-i+1)*(y/i);
	}
	return res;
}

int n;

int main(void){
	Init(1e5);
	scanf("%d",&n);
	reg int m=sqrt(n);
	reg ll ans=0;
	for(reg int i=1;i<=m;++i){
		if(!mu[i])
			continue;
		reg ll sum=0;
		for(reg int j=1;j*i<=m;++j)
			sum+=calc(j,n/(i*i*j));
		ans+=sum*mu[i];
	}
	printf("%lld\n",ans);
	return 0;
}