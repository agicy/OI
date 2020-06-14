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
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000+5;

namespace Basis{
	const int MAXLOG2A=63;
	ll p[MAXLOG2A];
	inline bool insert(reg ll x){
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			if(!((x>>i)&1))
				continue;
			if(!p[i]){
				p[i]=x;
				break;
			}
			else
				x^=p[i];
		}
		return x;
	}
}

using namespace Basis;

struct Stone{
	ll n;
	int m;
	inline void Read(void){
		n=read(),m=read();
		return;
	}
	inline bool operator<(const Stone& a){
		return m>a.m;
	}
};

int n;
Stone S[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		S[i].Read();
	sort(S+1,S+n+1);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(insert(S[i].n))
			ans+=S[i].m;
	printf("%d\n",ans);
	return 0;
}