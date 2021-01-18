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

const int MAXN=2e5+5;
const int MAXQ=2e5+5;

struct querys{
	int x,y,t;
	inline querys(reg int x=0,reg int y=0,reg int t=0):x(x),y(y),t(t){
		return;
	}
};

int n,q;
int cnt,head[MAXN],to[MAXN],Next[MAXN];
int rt[MAXN];
int val[MAXN];
querys Q[MAXQ];

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
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])
			son[u]=v;
	}
	return;
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*40;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int p=++tot;
		unit[p]=unit[pre],++sum(p);
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos);
			else
				rson(p)=update(rson(pre),mid+1,r,pos);
		}
		return p;
	}
	inline int query(reg int p,reg int q,reg int pre,reg int pref,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(p)+sum(q)-sum(pre)-sum(pref);
		if(L<=mid&&mid<R)
			return query(lson(p),lson(q),lson(pre),lson(pref),l,mid,L,R)+query(rson(p),rson(q),rson(pre),rson(pref),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(p),lson(q),lson(pre),lson(pref),l,mid,L,R);
		else
			return query(rson(p),rson(q),rson(pre),rson(pref),mid+1,r,L,R);
	}
	#undef mid
}

int top[MAXN];

inline void dfs2(reg int u,reg int topf){
	if(val[u])
		rt[u]=SegmentTree::update(rt[fa[u]],1,q,val[u]);
	else
		rt[u]=rt[fa[u]];
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],topf);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=son[u])
			dfs2(v,v);
	}
	return;
}

inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int main(void){
	n=read();
	int root=1;
	for(reg int i=1;i<=n;++i){
		static int p;
		p=read();
		if(p)
			Add_Edge(p,i);
		else
			root=i;
	}
	q=read();
	reg int tot=0;
	for(reg int i=1;i<=q;++i){
		static int opt,x,y,c,t;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read(),c=read();
				Q[++tot]=querys(x,y,i-c-1);
				break;
			}
			case 2:{
				t=read();
				if(!val[t])
					val[t]=i;
				break;
			}
		}
	}
	dfs1(root,0);
	dfs2(root,root);
	for(reg int i=1;i<=tot;++i){
		reg int lca=LCA(Q[i].x,Q[i].y);
		reg int res=Q[i].t>0?SegmentTree::query(rt[Q[i].x],rt[Q[i].y],rt[lca],rt[fa[lca]],1,q,1,Q[i].t):0;
		printf("%d %d\n",dep[Q[i].x]+dep[Q[i].y]-dep[lca]-dep[fa[lca]],res);
	}
	return 0;
}