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

const int MAXN=2e5+5;

int n;
ll t;
int cnt,head[MAXN],to[MAXN],Next[MAXN];
ll w[MAXN];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

namespace Heap{
	struct Node{
		int lson,rson,dep;
		int siz;
		ll val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define dep(x) unit[(x)].dep
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXN];
	inline void pushup(reg int p){
		dep(p)=dep(rson(p))+1;
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline int New(reg ll Val){
		reg int p=++tot;
		lson(p)=rson(p)=dep(p)=0;
		siz(p)=1;
		val(p)=Val;
		return p;
	}
	inline int merge(int x,int y){
		if(!x||!y)
			return x|y;
		if(val(x)<val(y))
			swap(x,y);
		rson(x)=merge(rson(x),y);
		if(dep(lson(x))<dep(rson(x)))
			swap(lson(x),rson(x));
		pushup(x);
		return x;
	}
	inline ll top(reg int p){
		return val(p);
	}
	inline int pop(reg int p){
		return merge(lson(p),rson(p));
	}
	inline int size(reg int p){
		return siz(p);
	}
}

int rt[MAXN];
ll dis[MAXN];
int ans[MAXN];

inline void dfs(reg int u){
	rt[u]=Heap::New(dis[u]);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dis[v]=dis[u]+w[i];
		dfs(v);
		rt[u]=Heap::merge(rt[u],rt[v]);
		while(Heap::top(rt[u])>dis[u]+t)
			rt[u]=Heap::pop(rt[u]);
	}
	ans[u]=Heap::size(rt[u]);
	return;
}

int main(void){
	n=read(),t=readll();
	for(reg int i=2;i<=n;++i){
		static int p;
		static ll w;
		p=read(),w=readll();
		Add_Edge(p,i,w);
	}
	dfs(1);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}