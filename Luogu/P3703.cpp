#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];
int tim,dfn[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	dfn[u]=++tim;
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

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,tAdd;
		#define Max(x) unit[(x)].Max
		#define tAdd(x) unit[(x)].tAdd
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			Max(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Add(reg int k,reg int val){
		Max(k)+=val,tAdd(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tAdd(k)){
			Add(lson,tAdd(k));
			Add(rson,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

namespace LCT{
	struct Node{
		int fa,ch[2];
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXN];
	inline bool get(reg int p){
		return rson(fa(p))==p;
	}
	inline bool isRoot(reg int p){
		return lson(fa(p))!=p&&rson(fa(p))!=p;
	}
	inline void rotate(reg int p){
		if(isRoot(p))
			return;
		reg int f=fa(p),ff=fa(f),dir=get(p);
		if(!isRoot(f)) ch(ff)[get(f)]=p;
		if(ch(p)[dir^1]) fa(ch(p)[dir^1])=f;
		ch(f)[dir]=ch(p)[dir^1];
		ch(p)[dir^1]=f,fa(f)=p;
		fa(p)=ff;
		return;
	}
	inline void splay(reg int p){
		for(reg int f;f=fa(p),!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		return;
	}
	inline int find(reg int p){
		while(lson(p))
			p=lson(p);
		return p;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa(p)){
			splay(p);
			if(rson(p)){
				reg int son=find(rson(p));
				SegmentTree::update(1,1,n,dfn[son],dfn[son]+siz[son]-1,1);
			}
			if(pre){
				reg int son=find(pre);
				SegmentTree::update(1,1,n,dfn[son],dfn[son]+siz[son]-1,-1);
			}
			rson(p)=pre;
		}
		return;
	}
}

inline int LCA(reg int x,reg int y){
	while(top[x]!=top[y])
		if(dep[top[x]]<dep[top[y]])
			y=fa[top[y]];
		else
			x=fa[top[x]];
	return dep[x]<dep[y]?x:y;
}

int val[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	dfs1(1,0),dfs2(1,0,1);
	for(reg int i=1;i<=n;++i)
		val[dfn[i]]=dep[i];
	SegmentTree::build(1,1,n,val);
	for(reg int i=1;i<=n;++i)
		LCT::fa(i)=fa[i];
	while(m--){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 1:{
				x=read();
				LCT::access(x);
				break;
			}
			case 2:{
				x=read(),y=read();
				reg int lca=LCA(x,y);
				reg int ans1=SegmentTree::query(1,1,n,dfn[x],dfn[x]);
				reg int ans2=SegmentTree::query(1,1,n,dfn[y],dfn[y]);
				reg int ans3=SegmentTree::query(1,1,n,dfn[lca],dfn[lca]);
				writeln(ans1+ans2-2*ans3+1);
				break;
			}
			case 3:{
				x=read();
				writeln(SegmentTree::query(1,1,n,dfn[x],dfn[x]+siz[x]-1));
				break;
			}
		}
	}
	flush();
	return 0;
}