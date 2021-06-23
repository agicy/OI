#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=152501+5;
const int MAXLOG2N=18+1;
const int MAXQ=152501+5;

int n;
int a[MAXN];

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
};

vector<Edge> G[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int w){
	G[u].push_back(Edge(v,w));
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],wson[MAXN];
int anc[MAXN][MAXLOG2N];
int Maxdep[MAXN],lson[MAXN];
ll dis[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	anc[u][0]=father;
	dep[u]=dep[father]+1;
	Maxdep[u]=dep[u];
	for(reg int i=1;anc[u][i-1];++i)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(Edge e:G[u])
		if(e.v!=father){
			dis[e.v]=dis[u]+e.w;
			dfs1(e.v,u);
			siz[u]+=siz[e.v];
			if(siz[wson[u]]<siz[e.v])
				wson[u]=e.v;
			if(Maxdep[e.v]>Maxdep[u]){
				Maxdep[u]=Maxdep[e.v];
				lson[u]=e.v;
			}
		}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];
int wtop[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	wtop[u]=topf;
	rnk[dfn[u]=++tim]=u;
	if(!wson[u])
		return;
	dfs2(wson[u],u,topf);
	for(Edge e:G[u])
		if(e.v!=father&&e.v!=wson[u])
			dfs2(e.v,u,e.v);
	return;
}

int ltop[MAXN];
vector<int> up[MAXN],dn[MAXN];

inline void dfs3(reg int u,reg int father,reg int topf){
	ltop[u]=topf;
	if(u==topf){
		up[u].resize(Maxdep[u]-dep[u]+1),dn[u].resize(Maxdep[u]-dep[u]+1);
		for(reg int i=0,v=u;i<=Maxdep[u]-dep[u];++i)
			up[u][i]=v,v=anc[v][0];
		for(reg int i=0,v=u;i<=Maxdep[u]-dep[u];++i)
			dn[u][i]=v,v=wson[v];
	}
	if(!wson[u])
		return;
	dfs3(wson[u],u,topf);
	for(Edge e:G[u])
		if(e.v!=father&&e.v!=wson[u])
			dfs3(e.v,u,e.v);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll cnt,sum;
		#define cnt(x) unit[(x)].cnt
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		cnt(k)=cnt(lson)+cnt(rson);
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[],reg ll b[]){
		if(l==r){
			cnt(k)=a[l],sum(k)=b[l];
			return;
		}
		build(lson,l,mid,a,b),build(rson,mid+1,r,a,b);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int vala,reg ll valb){
		if(l==r){
			cnt(k)=vala,sum(k)=valb;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,vala,valb);
		else
			update(rson,mid+1,r,pos,vala,valb);
		pushup(k);
		return;
	}
	inline ll queryCnt(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return cnt(k);
		if(L<=mid&&mid<R)
			return queryCnt(lson,l,mid,L,R)+queryCnt(rson,mid+1,r,L,R);
		else if(L<=mid)
			return queryCnt(lson,l,mid,L,R);
		else
			return queryCnt(rson,mid+1,r,L,R);
	}
	inline ll querySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		if(L<=mid&&mid<R)
			return querySum(lson,l,mid,L,R)+querySum(rson,mid+1,r,L,R);
		else if(L<=mid)
			return querySum(lson,l,mid,L,R);
		else
			return querySum(rson,mid+1,r,L,R);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef cnt
}

int lastx,lasty,lastlca;

inline int LCA(reg int x,reg int y){
	if(x==lastx&&y==lasty)
		return lastlca;
	lastx=x,lasty=y;
	while(wtop[x]!=wtop[y])
		if(dep[wtop[x]]>dep[wtop[y]])
			x=fa[wtop[x]];
		else
			y=fa[wtop[y]];
	lastlca=dep[x]<dep[y]?x:y;
	return lastlca;
}

inline int getPathNode(reg int x,reg int y){
	reg int lca=LCA(x,y);
	return dep[x]+dep[y]-dep[lca]-dep[fa[lca]];
}

inline ll queryCnt(reg int x,reg int y){
	reg ll res=0;
	while(wtop[x]!=wtop[y])
		if(dep[wtop[x]]>dep[wtop[y]])
			res+=SegmentTree::queryCnt(1,1,n,dfn[wtop[x]],dfn[x]),x=fa[wtop[x]];
		else
			res+=SegmentTree::queryCnt(1,1,n,dfn[wtop[y]],dfn[y]),y=fa[wtop[y]];
	res+=((dep[x]<dep[y])?SegmentTree::queryCnt(1,1,n,dfn[x],dfn[y]):SegmentTree::queryCnt(1,1,n,dfn[y],dfn[x]));
	return res;
}

inline ll querySum(reg int x,reg int y){
	reg ll res=0;
	while(wtop[x]!=wtop[y])
		if(dep[wtop[x]]>dep[wtop[y]])
			res+=SegmentTree::querySum(1,1,n,dfn[wtop[x]],dfn[x]),x=fa[wtop[x]];
		else
			res+=SegmentTree::querySum(1,1,n,dfn[wtop[y]],dfn[y]),y=fa[wtop[y]];
	res+=((dep[x]<dep[y])?SegmentTree::querySum(1,1,n,dfn[x],dfn[y]):SegmentTree::querySum(1,1,n,dfn[y],dfn[x]));
	return res;
}

int lg[MAXN];

inline int getAnc(reg int u,reg int k){
	if(!k)
		return u;
	else{
		u=anc[u][lg[k]];
		k-=(1<<lg[k])+(dep[u]-dep[wtop[u]]);
		u=wtop[u];
		return k>=0?up[u][k]:dn[u][-k];
	}
}

inline int getPoint(reg int x,reg int y,reg int k){
	reg int lca=LCA(x,y);
	if(k<=getPathNode(x,lca))
		return getAnc(x,k-1);
	else
		return getAnc(y,getPathNode(x,y)-k);
}

bool ed;

int main(void){
	n=read();
	lg[0]=-1;
	for(reg int i=1;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	dfs1(1,0),dfs2(1,0,1),dfs3(1,0,1);
	static int tmpa[MAXN];
	static ll tmpb[MAXN];
	for(reg int i=1;i<=n;++i)
		tmpa[dfn[i]]=a[i],tmpb[dfn[i]]=a[i]*dis[i];
	SegmentTree::build(1,1,n,tmpa,tmpb);
	reg int q=read();
	while(q--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 1:{
				reg int lim=(queryCnt(x,y)+1)>>1,len=getPathNode(x,y);
				reg int __l=1,__r=len,__mid;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(queryCnt(x,getPoint(x,y,__mid))>=lim)
						__r=__mid;
					else
						__l=__mid+1;
				}
				reg int pos=getPoint(x,y,__l);
				reg int lca=LCA(x,y);
				reg ll ans;
				if(lca==x){
					//puts("S1");
					ans=dis[pos]*queryCnt(pos,x)-querySum(pos,x)+querySum(pos,y)-dis[pos]*queryCnt(pos,y);
				}
				else if(lca==y){
					//puts("S2");
					swap(x,y);
					ans=dis[pos]*queryCnt(pos,x)-querySum(pos,x)+querySum(pos,y)-dis[pos]*queryCnt(pos,y);
				}
				else{
					//puts("S3");
					if(LCA(y,pos)!=lca)
						swap(x,y);
					ans=querySum(pos,x)-dis[pos]*queryCnt(pos,x)+dis[pos]*queryCnt(pos,lca)-querySum(pos,lca)+querySum(lca,y)+(dis[pos]-(dis[lca]<<1))*queryCnt(lca,y)-(dis[pos]-dis[lca])*a[lca];
				}
				writeln(ans);
				break;
			}
			case 2:{
				a[x]=y;
				SegmentTree::update(1,1,n,dfn[x],a[x],a[x]*dis[x]);
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}