#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define INF 123456789123456789ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200000+5;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
ll w[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];
ll dis[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dis[to[i]]=dis[ID]+w[i];
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[son[ID]]<size[to[i]])
				son[ID]=to[i];
		}
	return;
}

int tim,dfn[MAXN];
int rnk[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++tim;
	rnk[tim]=ID;
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll a,b;
		ll lx,rx,mx;
		ll Min;
		inline ll Get(reg ll x){
			return a*x+b;
		}
		#define a(x) unit[(x)].a
		#define b(x) unit[(x)].b
		#define lx(x) unit[(x)].lx
		#define rx(x) unit[(x)].rx
		#define mx(x) unit[(x)].mx
		#define Min(x) unit[(x)].Min
		#define Get(x,y) unit[(x)].Get((y))
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min(k)=min(Min(k),min(Min(lson),Min(rson)));
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		b(k)=Min(k)=INF,lx(k)=dis[rnk[l]],rx(k)=dis[rnk[r]];
		if(l==r)
			return;
		mx(k)=dis[rnk[mid]];
		Build(lson,l,mid),Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll na,reg ll nb){
		if(L<=l&&r<=R){
			reg ll left=Get(k,lx(k)),right=Get(k,rx(k));
			ll nl=na*lx(k)+nb,nr=na*rx(k)+nb;
			if(nl>=left&&nr>=right)
				return;
			if(nl<=left&&nr<=right){
				a(k)=na,b(k)=nb;
				Min(k)=min(Min(k),min(nl,nr));
				return;
			}
			reg double p=1.0*(b(k)-nb)/(na-a(k));
			if(left<nl)
				if(p<=(double)mx(k)){
					Update(lson,l,mid,L,R,a(k),b(k));
					a(k)=na,b(k)=nb;
				}
				else
					Update(rson,mid+1,r,L,R,na,nb);
			else
				if(p<=(double)mx(k))
					Update(lson,l,mid,L,R,na,nb);
				else{
					Update(rson,mid+1,r,L,R,a(k),b(k));
					a(k)=na,b(k)=nb;
				}
			Min(k)=min(Min(k),min(nl,nr));
			pushup(k);
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R,na,nb);
		if(R>mid)
			Update(rson,mid+1,r,L,R,na,nb);
		pushup(k);
		return;
	}
	inline ll Query(reg int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return Min(k);
		ll res=INF;
		if(b(k)!=INF){
			reg ll left=max(l,L),right=min(r,R);
			res=min(Get(k,dis[rnk[left]]),Get(k,dis[rnk[right]]));
		}
		if(L<=mid)
			res=min(res,Query(lson,l,mid,L,R));
		if(R>mid)
			res=min(res,Query(rson,mid+1,r,L,R));
		return res;
	}
}

inline int LCA(int u,int v){
	while(top[u]!=top[v]) dep[top[u]]>dep[top[v]]?u=fa[top[u]]:v=fa[top[v]];
	return dep[u]>dep[v]?v:u;
}
inline void Update(int u,int w,reg ll a,reg ll b){
	while(top[u]!=top[w]){
		SegmentTree::Update(1,1,n,dfn[top[u]],dfn[u],a,b);
		u=fa[top[u]];
	}
	SegmentTree::Update(1,1,n,dfn[w],dfn[u],a,b);
	return;
}

inline ll Query(int s,int t){
	ll res=INF;
	while(top[s]!=top[t]){
		if(dep[top[s]]>dep[top[t]])
			swap(s,t);
		res=min(res,SegmentTree::Query(1,1,n,dfn[top[t]],dfn[t]));
		t=fa[top[t]];
	}
	if(dep[s]>dep[t])
		swap(s,t);
	res=min(res,SegmentTree::Query(1,1,n,dfn[s],dfn[t]));
	return res;
}

signed main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	DFS1(1,0);
	DFS2(1,0,1);
	SegmentTree::Build(1,1,n);
	while(m--){
		static int opt,s,t;
		static ll a,b;
		opt=read();
		switch(opt){
			case 1:{
				s=read(),t=read(),a=read(),b=read();
				reg int lca=LCA(s,t);
				Update(s,lca,-a,b+a*dis[s]);
				Update(t,lca,a,b+a*(dis[s]-dis[lca]*2));
				break;
			}
			case 2:{
				s=read(),t=read();
				printf("%lld\n",Query(s,t));
				break;
			}
			default:break;
		}
	}
	return 0;
}