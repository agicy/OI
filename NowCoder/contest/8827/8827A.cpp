#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;

int n;
bool vis[MAXN];
int tot,prime[MAXN];
int mu[MAXN];
int F[MAXN];

inline int f(int x){
	int res=0;
	while(x){
		res+=(x%10);
		x/=10;
	}
	return res;
}

inline void Init(int n){
	mu[1]=1;
	for(int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=n;++i)
		F[i]=f(i);
	return;
}

int main(void){
	Init(1e5);
	scanf("%d",&n);
	ll ans=0;
	for(int d=1;d<=n;++d)
		if(mu[d]){
			ll m=n/d,sum=0;
			for(int i=d;i<=n;i+=d)
				sum+=F[i]*(m--);
			ans+=sum*mu[d];
		}
	printf("%lld\n",ans);
	return 0;
}