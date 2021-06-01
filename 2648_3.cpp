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
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e5+5;

struct Node{
	ll s,t;
	inline bool operator<(const Node& a)const{
		return t<a.t;
	}
};

int n;
Node a[MAXN];

namespace Subtask2{
	inline ll getVal(reg int id,reg int tim){
		return a[id].s+a[id].t*(tim-1);
	}
	ll f[MAXN];
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			for(reg int tim=i;tim>=1;--tim)
				f[tim]=max(f[tim],f[tim-1]+getVal(i,tim));
		for(reg int i=1;i<=n;++i)
			writeln(f[i]);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].s=readll(),a[i].t=readll();
	sort(a+1,a+n+1);
	if(n<=1e4)
		Subtask2::Solve();
	flush();
	return 0;
}