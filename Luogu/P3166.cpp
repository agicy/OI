#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;

ll n,m;
bool vis[MAXN];
int tot,prime[MAXN];
int phi[MAXN];

inline ll C3(reg ll x){
	return x*(x-1)/2*(x-2)/3;
}

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
	scanf("%lld%lld",&n,&m);
	if(n>m)
		swap(n,m);
	Init(n);
	reg ll sum=0;
	for(reg int d=2;d<=n;++d)
		sum+=1ll*phi[d]*(n-d+n%d+2)*(n/d)*(m-d+m%d+2)*(m/d)/2;
	printf("%lld\n",C3((n+1)*(m+1))-(m+1)*C3(n+1)-(n+1)*C3(m+1)-sum);
	return 0;
}