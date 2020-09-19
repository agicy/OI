#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e7+5;

int n;
bool vis[MAXN];
int tot,prime[MAXN];
int phi[MAXN];
ll sum[MAXN];

inline void Init(reg int n){
	phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	return;
}

int main(void){
	scanf("%d",&n);
	Init(n);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+phi[i];
	reg ll ans=0;
	for(reg int i=1;i<=tot;++i)
		ans+=sum[n/prime[i]]*2-1;
	printf("%lld\n",ans);
	return 0;
}