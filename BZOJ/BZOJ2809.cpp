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

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

namespace Heap{
	struct Node{
		int lson,rson,dis;
		int siz;
		int sum,val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define dis(x) unit[(x)].dis
		#define siz(x) unit[(x)].siz
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXN];
	inline int New(reg int v){
		reg int p=++tot;
		siz(p)=1;
		sum(p)=val(p)=v;
		return p;
	}
	inline void pushup(reg int p){
		dis(p)=dis(rson(p))+1;
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
		return;
	}
	inline int merge(int p,int q){
		if(!p||!q)
			return p|q;
		if(val(p)<val(q))
			swap(p,q);
		rson(p)=merge(rson(p),q);
		if(dis(lson(p))<dis(rson(p)))
			swap(lson(p),rson(p));
		pushup(p);
		return p;
	}
	inline int top(reg int p){
		return sum(p);
	}
	inline void pop(reg int& p){
		p=merge(lson(p),rson(p));
		pushup(p);
		return;
	}
}

int n,m;
int b[MAXN],c[MAXN],l[MAXN];
int rt[MAXN];

int main(void){
	n=read(),m=read();
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		b[i]=read(),c[i]=read(),l[i]=read();
		ans=max(ans,0ll+l[i]);
		rt[i]=Heap::New(c[i]);
	}
	for(reg int i=n;i>1;--i){
		reg int fa=b[i];
		rt[fa]=Heap::merge(rt[i],rt[fa]);
		while(Heap::top(rt[fa])>m)
			Heap::pop(rt[fa]);
		ans=max(ans,1ll*l[fa]*Heap::siz(rt[fa]));
	}
	printf("%lld\n",ans);
	return 0;
}