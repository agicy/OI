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

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

int n,Q;
int w[MAXN],val[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])
			son[u]=v;
	}
	return;
}

int tim,dfn[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
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
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int getNear(reg int x,reg int y){
	reg int delta=dep[y]-dep[x]-1;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if((delta>>i)&1)
			y=fa[y][i];
	return y;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Min;
		#define Min(x) unit[(x)].Min
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int val[]){
		if(l==r){
			Min(k)=val[l];
			return;
		}
		build(lson,l,mid,val),build(rson,mid+1,r,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Min(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Min(k);
		if(L<=mid&&mid<R)
			return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read(),Q=read();
	for(reg int i=1;i<=n;++i){
		static int f;
		f=read(),w[i]=read();
		if(f)
			Add_Edge(f,i);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(reg int i=1;i<=n;++i)
		val[dfn[i]]=w[i];
	SegmentTree::build(1,1,n,val);
	reg int rt=1;
	while(Q--){
		static char opt;
		static int x,y;
		do{
			opt=getchar();
		}while(!isalpha(opt));
		switch(opt){
			case 'V':{
				x=read(),y=read();
				SegmentTree::update(1,1,n,dfn[x],y);
				break;
			}
			case 'E':{
				x=read();
				rt=x;
				break;
			}
			case 'Q':{
				x=read();
				reg int ans;
				if(x==rt)
					ans=SegmentTree::query(1,1,n,1,n);
				else if(LCA(rt,x)==x){
					reg int u=getNear(x,rt);
					if(1<=dfn[u]-1&&dfn[u]+siz[u]<=n)
						ans=min(SegmentTree::query(1,1,n,1,dfn[u]-1),SegmentTree::query(1,1,n,dfn[u]+siz[u],n));
					else if(1<=dfn[u]-1)
						ans=SegmentTree::query(1,1,n,1,dfn[u]-1);
					else
						ans=SegmentTree::query(1,1,n,dfn[u]+siz[u],n);
				}
				else
					ans=SegmentTree::query(1,1,n,dfn[x],dfn[x]+siz[x]-1);
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}