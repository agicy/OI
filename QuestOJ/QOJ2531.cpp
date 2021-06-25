#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=20;
const int MAXM=1e6;

namespace Poly{
	typedef vector<ll> poly;
	inline void FWT_or(poly& a){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=i<<1)
				for(reg int k=0;k<i;++k)
					a[i+j+k]+=a[j+k];
		return;
	}
}

using namespace Poly;

int n,m;
int a[MAXN][MAXM];
int del[MAXM];
poly f[MAXN],sum;

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j){
			a[i][j]=read();
			if(!(~a[i][j]))
				del[j]|=1<<i;
		}
	for(reg int i=0;i<n;++i){
		f[i].resize(1<<n);
		for(reg int j=0;j<m;++j)
			if(~a[i][j])
				f[i][del[j]]+=a[i][j];
		FWT_or(f[i]);
	}
	sum.resize(1<<n);
	for(reg int i=0,U=(1<<(n-1))-1;i<n;++i)
		for(reg int S=0,p=(1<<i)-1,T;S<=U;++S){
			T=(S&p)|((S&(U^p))<<1);
			sum[T]+=f[i][T];
		}
	reg ll ans=0;
	for(reg int S=0;S<(1<<n);++S)
		ans=max(ans,sum[S]);
	printf("%lld\n",ans);
	return 0;
}