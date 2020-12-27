#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXK=1e7+5;
const int p=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int n,k;
int fac[MAXK],invfac[MAXK],inv[MAXK];
// inv[i]=\frac{1}{i}
int binom[MAXK];
// binom[i]=\binom{n}{i}
int tot,prime[MAXK];
int idk[MAXK];

inline void Init(reg int k){
	fac[0]=1;
	for(reg int i=1;i<=k+1;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[k+1]=fpow(fac[k+1],p-2);
	for(reg int i=k;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	for(reg int i=1;i<=k+1;++i)
		inv[i]=1ll*invfac[i]*fac[i-1]%p;
	binom[0]=1;
	for(reg int i=1;i<=k+1;++i)
		binom[i]=1ll*binom[i-1]*inv[i]%p*(n-i+1)%p;
	idk[1]=1;
	for(reg int i=2;i<=k+1;++i){
		if(!idk[i]){
			prime[++tot]=i;
			idk[i]=fpow(i,k);
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=k;++j){
			idk[i*prime[j]]=1ll*idk[i]*idk[prime[j]]%p;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

inline int solve1(void){
	reg int res=0;
	for(reg int i=1;i<=n;++i)
		res=add(res,1ll*binom[i]*idk[i]%p);
	return res;
}

int f[MAXK];

inline int solve2(void){
	reg int bas=p-fpow(2,p-2);
	f[k]=1;
	for(reg int i=k-1,pow=1,c=1;i>=1;--i){
		c=1ll*c*(n-i-1)%p*inv[k-i]%p;
		pow=1ll*pow*bas%p;
		f[i]=add((bas+1ll)*f[i+1]%p,1ll*c*pow%p);
	}
	reg int res=0;
	for(reg int i=1,pow=p-bas;i<=k;++i){
		res=add(res,1ll*idk[i]*binom[i]%p*pow%p*f[i]%p);
		pow=1ll*pow*(p-bas)%p;
	}
	return 1ll*res*fpow(2,n)%p;
}

int main(void){
	scanf("%d%d",&n,&k);
	Init(k);
	if(n<=k+1)
		printf("%d\n",solve1());
	else
		printf("%d\n",solve2());
	return 0;
}