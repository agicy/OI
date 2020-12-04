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

const int MAXP=1e5+5;

int n,m,p;
int fac[MAXP],invfac[MAXP];

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

inline int lucas(reg int n,reg int m){
	if(n==0||m==0)
		return 1;
	if(m<0||n<m)
		return 0;
	else
		return 1ll*binom(n%p,m%p)*lucas(n/p,m/p)%p;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read(),p=read();
		fac[0]=1;
		for(reg int i=1;i<p;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[p-1]=p-1;
		for(reg int i=p-2;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		printf("%d\n",lucas(n+m,m));
	}
	return 0;
}