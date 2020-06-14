#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

ll x,y;

const int MAXSIZE=100000+5;

bool vis[MAXSIZE];
int tot,prime[MAXSIZE];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&(ll)i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

inline ll mu(reg ll x){
	reg int sum=0;
	for(reg int i=1;i<=tot&&(ll)prime[i]*prime[i]<=x;++i)
		if(x%prime[i]==0){
			reg int cnt=0;
			while(x%prime[i]==0)
				x/=prime[i],++cnt;
			if(cnt>1)
				return 0;
			sum+=cnt;
		}
	if(x>1)
		++sum;
	return (sum&1)?(MOD-1):(1);
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

int main(void){
	scanf("%lld%lld",&x,&y);
	if(y%x!=0){
		puts("0");
		return 0;
	}
	Init(1e5);
	reg int n=y/x;
	ll ans=0;
	for(reg int i=1;(ll)i*i<=n;++i)
		if(n%i==0){
			ans=(ans+(ll)mu(n/i)*pow(2,i-1,MOD)%MOD)%MOD;
			if(i*i!=n)
				ans=(ans+(ll)mu(i)*pow(2,n/i-1,MOD)%MOD)%MOD;
		}
	printf("%lld\n",ans);
	return 0;
}