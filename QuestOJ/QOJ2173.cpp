#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int p=998244353;

int n;
ll k;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
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

int fac[MAXN],invfac[MAXN];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

int main(void){
	n=read(),k=readll();
	if(k>n)
		puts("0");
	else{
		fac[0]=1;
		for(reg int i=1;i<=n;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[n]=fpow(fac[n],p-2);
		for(reg int i=n-1;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		reg int m=n-k,ans=0;
		if(k){
			for(reg int i=0;i<=m;++i)
				if(i&1)
					ans=sub(ans,1ll*binom(m,i)*fpow(m-i,n)%p);
				else
					ans=add(ans,1ll*binom(m,i)*fpow(m-i,n)%p);
			ans=2ll*ans%p*binom(n,m)%p;
		}
		else
			ans=fac[n];
		printf("%d\n",ans);
	}
	return 0;
}