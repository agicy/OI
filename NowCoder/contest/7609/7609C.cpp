#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(int &a,int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int inf=0x3f3f3f3f;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],siz[MAXN];

inline void dfs1(int u,int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
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
int tim,dfn[MAXN],rnk[MAXN];

inline void dfs2(int u,int father,int topf){
	top[u]=topf;
	dfn[u]=++tim;
	rnk[tim]=u;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
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
		int ans,Max,tag;
		bool cle;
		inline Node(int ans=0,int Max=0,int tag=0,bool cle=false):ans(ans),Max(Max),tag(tag),cle(cle){
			return;
		}
		#define ans(x) unit[(x)].ans
		#define Max(x) unit[(x)].Max
		#define tag(x) unit[(x)].tag
		#define cle(x) unit[(x)].cle
	};
	Node unit[MAXN<<2];
	inline void pushup(int k){
		ans(k)=min(tag(k)-2*Max(k),min(ans(lson),ans(rson)));
		return;
	}
	inline void clear(int k){
		ans(k)=tag(k)=inf;
		cle(k)=true;
		return;
	}
	inline void pushdown(int k){
		if(cle(k)){
			clear(lson),clear(rson);
			cle(k)=false;
		}
		return;
	}
	inline void build(int k,int l,int r){
		ans(k)=tag(k)=inf;
		if(l==r){
			Max(k)=dep[rnk[l]];
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void update(int k,int l,int r,int L,int R,int val){
		if(L<=l&&r<=R){
			cMin(tag(k),val);
			cMin(ans(k),tag(k)-2*Max(k));
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
	inline int query(int k,int l,int r,int L,int R,int val){
		if(L<=l&&r<=R)
			return min(ans(k),val-2*Max(k));
		pushdown(k);
		cMin(val,tag(k));
		if(L<=mid&&mid<R)
			return min(query(lson,l,mid,L,R,val),query(rson,mid+1,r,L,R,val));
		else if(L<=mid)
			return query(lson,l,mid,L,R,val);
		else
			return query(rson,mid+1,r,L,R,val);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void update(int x,int val){
	for(int u=x;u;u=fa[top[u]])
		SegmentTree::update(1,1,n,dfn[top[u]],dfn[u],val);
	return;
}

inline int query(int x,int res=inf){
	for(int u=x;u;u=fa[top[u]])
		cMin(res,SegmentTree::query(1,1,n,dfn[top[u]],dfn[u],inf));
	return res;
}

int main(void){
	n=read(),m=read();
	for(int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	SegmentTree::build(1,1,n);
	for(int i=1;i<=m;++i){
		static int opt,x;
		opt=read(),x=read();
		switch(opt){
			case 1:{
				update(x,dep[x]+i);
				break;
			}
			case 2:{
				SegmentTree::clear(1);
				break;
			}
			case 3:{
				puts(query(x)<=i-dep[x]?"wrxcsd":"orzFsYo");
				break;
			}
		}
	}
	return 0;
}