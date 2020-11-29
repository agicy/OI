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

const int p=1e5+3;

int fac[p],invfac[p];

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

inline int binom(reg int n,reg int m){
	if(m<0||m>n)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

inline int f(reg int n,reg int m,reg int k){
	return 1ll*binom(n,k)*binom(m,k)%p*fac[k]%p;
}

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int main(void){
	fac[0]=1;
	for(reg int i=1;i<p;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[p-1]=fpow(fac[p-1],p-2);
	for(reg int i=p-2;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	reg int a=read(),b=read(),c=read(),d=read(),k=read();
	reg int ans=0;
	for(reg int i=0;i<=k;++i)
		ans=add(ans,1ll*f(a,b,i)*f(a+c-i,d,k-i)%p);
	printf("%d\n",ans);
	return 0;
}