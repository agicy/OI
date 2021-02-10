#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)){if(ch==EOF)exit(0);ch=getchar();}
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,m;
int val[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int rt[MAXN];

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	struct Node{
		int lson,rson;
		int cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(void){
		reg int p=++tot;
		lson(p)=rson(p)=cnt(p)=0;
		return p;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos,reg int val){
		reg int p=New();
		unit[p]=unit[pre],cnt(p)+=val;
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos,val);
			else
				rson(p)=update(rson(pre),mid+1,r,pos,val);
		}
		return p;
	}
	inline int query(reg int p,reg int q,reg int pre,reg int ppre,reg int l,reg int r,reg int pos){
		if(l==r)
			return (cnt(p)+cnt(q))-(cnt(pre)+cnt(ppre));
		if(pos<=mid)
			return query(lson(p),lson(q),lson(pre),lson(ppre),l,mid,pos);
		else
			return query(rson(p),rson(q),rson(pre),rson(ppre),mid+1,r,pos);
	}
	#undef mid
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	rt[u]=SegmentTree::update(rt[father],0,n,val[u],1);
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	son[u]=0;
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

int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
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

inline int LCA(reg int x,reg int y){
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]])
			x=fa[top[x]];
		else
			y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}

int main(void){
	while(true){
		n=read(),m=read();
		cnt=0,fill(head+1,head+n+1,0);
		SegmentTree::tot=0;
		for(reg int i=1;i<=n;++i)
			val[i]=read();
		for(reg int i=1;i<n;++i){
			static int u,v;
			u=read(),v=read();
			Add_Edge(u,v),Add_Edge(v,u);
		}
		dfs1(1,0);
		dfs2(1,0,1);
		while(m--){
			static int u,v,c;
			u=read(),v=read(),c=read();
			reg int lca=LCA(u,v);
			reg int res=SegmentTree::query(rt[u],rt[v],rt[lca],rt[fa[lca]],0,n,c);
			puts(res?"Find":"NotFind");
		}
	}
	return 0;
}