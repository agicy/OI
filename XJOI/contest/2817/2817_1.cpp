#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod,exp>>=1;
	}
	return res;
}

const int MAXH=1e6+5;

int h,w;
int fac[MAXH],invfac[MAXH];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}

bool ed;

int main(void){
	scanf("%d%d",&h,&w);
	reg int g=gcd(h,w);
	fac[0]=1;
	for(reg int i=1;i<=g;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[g]=fpow(fac[g],mod-2);
	for(reg int i=g-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	reg int ans=0;
	for(reg int i=0;i<=g;++i)
		if(gcd(i,h)==1&&gcd(g-i,w)==1)
			ans=add(ans,binom(g,i));
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}