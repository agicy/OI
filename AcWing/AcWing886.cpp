#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e5+5;
const int p=1e9+7;

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

int fac[MAXSIZE];
int invfac[MAXSIZE];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=pow(fac[n],p-2,p);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	return;
}

inline int binom(reg int n,reg int m){
	return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

int n;

int main(void){
	scanf("%d",&n);
	Init(1e5);
	for(reg int i=1;i<=n;++i){
		static int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",binom(a,b));
	}
	return 0;
}