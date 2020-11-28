#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e4+5;
const int inf=0x3f3f3f3f;

int n,m;
int p[MAXN],q[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int tim,dfn[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Min,tag;
		#define Min(x) unit[(x)].Min
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tag(k)=inf;
		if(l==r){
			Min(k)=inf;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void set(reg int k,reg int val){
		cMin(Min(k),val),cMin(tag(k),val);
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)!=inf){
			set(lson,tag(k));
			set(rson,tag(k));
			tag(k)=inf;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			set(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return Min(k);
		pushdown(k);
		if(pos<=mid)
			return query(lson,l,mid,pos);
		else
			return query(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void update(int x,int y,reg int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		SegmentTree::update(1,1,n,dfn[top[y]],dfn[y],val);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	if(dfn[x]<dfn[y])
		SegmentTree::update(1,1,n,dfn[x]+1,dfn[y],val);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		p[i]=read(),q[i]=read();
		Add_Edge(p[i],q[i]);
		Add_Edge(q[i],p[i]);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	SegmentTree::build(1,1,n);
	while(m--){
		static int p,q,r;
		p=read(),q=read(),r=read();
		update(p,q,r);
	}
	for(reg int i=1;i<n;++i){
		reg int son=dep[p[i]]<dep[q[i]]?q[i]:p[i];
		reg int res=SegmentTree::query(1,1,n,dfn[son]);
		printf("%d\n",res==inf?-1:res);
	}
	return 0;
}