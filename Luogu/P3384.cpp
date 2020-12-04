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

int n,m,r;
ll p;

inline ll add(reg ll a,reg ll b){
	a+=b;
	return a>=p?a-p:a;
}

ll a[MAXN];
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

int top[MAXN];
int tim,dfn[MAXN];
ll val[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	val[tim]=a[u];
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
		ll sum,tag;
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=add(sum(lson),sum(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			sum(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg ll val){
		sum(k)=add(sum(k),1ll*(r-l+1)*val%p);
		tag(k)=add(tag(k),val);
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			Add(lson,l,mid,tag(k));
			Add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
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
	inline ll query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return add(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void update(int x,int y,reg ll val){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		SegmentTree::update(1,1,n,dfn[top[y]],dfn[y],val);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::update(1,1,n,dfn[x],dfn[y],val);
	return;
}

inline ll query(int x,int y){
	reg ll res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res=add(res,SegmentTree::query(1,1,n,dfn[top[y]],dfn[y]));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=add(res,SegmentTree::query(1,1,n,dfn[x],dfn[y]));
	return res;
}

int main(void){
	n=read(),m=read(),r=read(),p=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read()%p;
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	dfs1(r,0);
	dfs2(r,0,r);
	SegmentTree::build(1,1,n,val);
	while(m--){
		static int opt,x,y;
		static ll z;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read(),z=read()%p;
				update(x,y,z);
				break;
			}
			case 2:{
				x=read(),y=read();
				reg ll ans=query(x,y);
				printf("%lld\n",ans);
				break;
			}
			case 3:{
				x=read(),z=read()%p;
				SegmentTree::update(1,1,n,dfn[x],dfn[x]+siz[x]-1,z);
				break;
			}
			case 4:{
				x=read();
				reg ll ans=SegmentTree::query(1,1,n,dfn[x],dfn[x]+siz[x]-1);
				printf("%lld\n",ans);
				break;
			}
		}
	}
	return 0;
}