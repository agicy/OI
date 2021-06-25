#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=100000+5;

int n;
ll a[MAXN],sum;

namespace Basis{
	const int MAXLOG2A=62;
	ll p[MAXLOG2A];
	inline void insert(reg ll x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if(!((sum>>i)&1)&&((x>>i)&1)){
				if(!p[i]){
					p[i]=x;
					return;
				}
				else
					x^=p[i];
			}
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if(((sum>>i)&1)&&((x>>i)&1)){
				if(!p[i]){
					p[i]=x;
					break;
				}
				else
					x^=p[i];
			}
		return;
	}
	inline ll query(void){
		reg ll res=0;
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if(!((sum>>i)&1)&&!((res>>i)&1))
				res^=p[i];
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if(((sum>>i)&1)&&!((res>>i)&1))
				res^=p[i];
		return res;
	}
}

using namespace Basis;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum^=a[i];
	}
	for(reg int i=1;i<=n;++i)
		insert(a[i]);
	printf("%lld\n",query()^sum);
	return 0;
}