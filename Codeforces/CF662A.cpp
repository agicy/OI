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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXLOG2A=60;

namespace Basis{
	ll unit[MAXLOG2A];
	inline bool insert(reg ll x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					return true;
				}
				x^=unit[i];
			}
		return false;
	}
}

int n;

int main(void){
	n=read();
	reg ll res=0;
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		reg ll a=readll(),b=readll();
		res^=a,ans+=Basis::insert(a^b);
	}
	if(Basis::insert(res))
		puts("1/1");
	else
		printf("%lld/%lld\n",(1ll<<ans)-1,1ll<<ans);
	return 0;
}