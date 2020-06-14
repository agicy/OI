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

const int MAXLOG2A=63;

namespace Basis{
	ll p[MAXLOG2A];
	inline void insert(reg ll x){
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
		return;
	}
	inline ll Query(void){
		reg ll res=0;
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((res^p[i])>res)
				res^=p[i];
		return res;
	}
}

using namespace Basis;

int n;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static ll a;
		a=read();
		insert(a);
	}
	printf("%lld\n",Query());
	return 0;
}