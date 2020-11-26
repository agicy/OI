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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=3e4+5;
const int MAXLOG2A=10;

int n,q;
int u[MAXN],v[MAXN],W[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],siz[MAXN];
int dis[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dis[v]=(dis[u]^w[i]);
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	rnk[tim]=u;
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
		int sum[MAXLOG2A];
		bool tag[MAXLOG2A];
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		for(reg int i=0;i<MAXLOG2A;++i)
			sum(k)[i]=sum(lson)[i]+sum(rson)[i];
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			reg int val=dis[rnk[l]];
			for(reg int i=0;i<MAXLOG2A;++i)
				if((val>>i)&1)
					++sum(k)[i];
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void reverse(reg int k,reg int l,reg int r,reg int id){
		sum(k)[id]=(r-l+1)-sum(k)[id];
		tag(k)[id]=!tag(k)[id];
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		for(reg int i=0;i<MAXLOG2A;++i)
			if(tag(k)[i]){
				reverse(lson,l,mid,i);
				reverse(rson,mid+1,r,i);
				tag(k)[i]=false;
			}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			for(reg int i=0;i<MAXLOG2A;++i)
				if((val>>i)&1)
					reverse(k,l,r,i);
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
	ll ans[MAXLOG2A];
	inline void query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			for(reg int i=0;i<MAXLOG2A;++i)
				ans[i]+=sum(k)[i];
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			query(lson,l,mid,L,R);
		if(R>mid)
			query(rson,mid+1,r,L,R);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

inline ll query(int x,int y){
	for(reg int i=0;i<MAXLOG2A;++i)
		SegmentTree::ans[i]=0;
	reg int lca=LCA(x,y);
	reg int dis=dep[x]+dep[y]-(dep[lca]<<1)+1;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		SegmentTree::query(1,1,n,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::query(1,1,n,dfn[x],dfn[y]);
	reg ll ans=0;
	for(reg int i=0;i<MAXLOG2A;++i)
		ans+=(1ll<<i)*SegmentTree::ans[i]*(dis-SegmentTree::ans[i]);
	return ans;
}

int val[MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read(),W[i]=read();
		Add_Edge(u[i],v[i],W[i]);
		Add_Edge(v[i],u[i],W[i]);
	}
	dfs1(1,0);
	dfs2(1,0,1);
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<n;++i){
		reg int son=dep[u[i]]<dep[v[i]]?v[i]:u[i];
		val[son]=W[i];
	}
	while(q--){
		static int opt,u,v,w;
		opt=read();
		switch(opt){
			case 1:{
				u=read(),v=read();
				printf("%lld\n",query(u,v));
				break;
			}
			case 2:{
				u=read(),v=read(),w=read();
				reg int son=dep[u]<dep[v]?v:u;
				reg int x=(w^val[son]);
				SegmentTree::update(1,1,n,dfn[son],dfn[son]+siz[son]-1,x);
				val[son]=w;
				break;
			}
		}
	}
	return 0;
}