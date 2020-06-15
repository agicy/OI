#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 104857601

const int MAXN=1000000+5;
const int MAXSIZE=1000000+5;

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x,reg int mod){
	return pow(x,mod-2,mod);
}

bitset<MAXSIZE> vis;
int tot,prime[80000];
int phi[MAXSIZE];

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

int n;

int main(void){
	scanf("%d",&n);
	Init(n);
	for(reg int i=1;i<=n;++i)
		phi[i]=(0ll+phi[i-1]+2ll*phi[i])%(MOD-1);
	reg int ans1=1;
	for(reg int i=1;i<=n;++i)
		ans1=1ll*ans1*i%MOD;
	ans1=pow(ans1,2*n,MOD);
	reg int ans2=1;
	for(reg int i=2;i<=n;++i)
		ans2=1ll*ans2*pow(i,phi[n/i]-1,MOD)%MOD;
	printf("%lld\n",1ll*ans1*inv(1ll*ans2*ans2%MOD,MOD)%MOD);
	return 0;
}