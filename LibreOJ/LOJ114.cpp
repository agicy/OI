#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXLOG2S=60;

int n,m;

namespace Basis{
	ll unit[MAXLOG2S];
	inline void insert(reg ll x){
		for(reg int i=MAXLOG2S-1;i>=0;--i)
			if((x>>i)&1){
				if(unit[i])
					x^=unit[i];
				else{
					unit[i]=x;
					break;
				}
			}
		return;
	}
	int tot;
	ll bas[MAXLOG2S];
	inline void build(void){
		for(reg int i=MAXLOG2S-1;i>=0;--i)
			for(reg int j=i-1;j>=0;--j)
				if((unit[i]>>j)&1)
					unit[i]^=unit[j];
		for(reg int i=0;i<MAXLOG2S;++i)
			if(unit[i])
				bas[tot++]=unit[i];
		return;
	}
	inline ll query(reg ll k){
		if(tot!=n)
			--k;
		if((1ll<<tot)<=k)
			return -1;
		else{
			reg ll res=0;
			for(reg int i=0;i<tot;++i)
				if((k>>i)&1)
					res^=bas[i];
			return res;
		}
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		Basis::insert(readll());
	Basis::build();
	m=read();
	for(reg int i=1;i<=m;++i)
		writeln(Basis::query(readll()));
	flush();
	return 0;
}