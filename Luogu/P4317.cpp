#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXLOG2N=50+1;
const int p=10000007;

ll n;
ll G[MAXLOG2N];

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
	n=read();
	reg ll C=0;
	for(reg int j=MAXLOG2N-1;j>=0;--j){
		for(reg int i=MAXLOG2N-1;i;--i)
			G[i]+=G[i-1];
		if((n>>j)&1)
			++G[C++];
	}
	++G[C];
	reg ll ans=1;
	for(reg int i=1;i<MAXLOG2N;++i)
		ans=ans*pow(i,G[i],p)%p;
	printf("%lld\n",ans);
	return 0;
}