#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=2e4+5;
const int MAXM=2e5+5;

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

inline void dfs1(reg int u,reg int father){
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

int tim,dfn[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	dfn[u]=++tim;
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
		int sum,tag;
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		sum(k)=tag(k)=0;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg int val){
		sum(k)+=val*(r-l+1);
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			add(lson,l,mid,tag(k));
			add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return sum(k);
		pushdown(k,l,r);
		if(pos<=mid)
			return query(lson,l,mid,pos);
		else
			return query(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void add(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]])
			swap(u,v);
		SegmentTree::update(1,1,n,dfn[top[v]],dfn[v],1);
		v=fa[top[v]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
		SegmentTree::update(1,1,n,dfn[u]+1,dfn[v],1);
	return;
}

int main(void){
	reg int T=read();
	while(T--){
		cnt=tim=0,memset(head,0,sizeof(head));
		n=read(),m=read();
		for(reg int i=1;i<n;++i){
			static int u,v;
			u=read(),v=read();
			Add_Edge(u,v);
			Add_Edge(v,u);
		}
		dfs1(1,0);
		dfs2(1,0,1);
		SegmentTree::build(1,1,n);
		for(reg int i=1;i<=m-n+1;++i){
			static int u,v;
			u=read(),v=read();
			add(u,v);
		}
		int ans=m+1;
		for(reg int i=2;i<=n;++i)
			cMin(ans,SegmentTree::query(1,1,n,dfn[i]));
		printf("%d\n",ans+1);
	}
	return 0;
}