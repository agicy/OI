#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=2e5+5;
const int MAXM=4e5+5;
const int MAXV=MAXN*2;
const int MAXLOG2V=18+1;

int n,m,q;
int u[MAXM],v[MAXM];

struct Edge{
	int u,v,val;
	inline Edge(reg int u=0,reg int v=0,reg int val=0):u(u),v(v),val(val){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return val<a.val;
	}
};

Edge E[MAXM];
int cnt,head[MAXV],to[MAXV],Next[MAXV];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace UnionFind{
	int fa[MAXV];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

namespace TreeA{
	int cnt,head[MAXV],to[MAXV],Next[MAXV];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXV][MAXLOG2V];
	int lef[MAXV],rig[MAXV];
	int tim,rnk[MAXV];
	int val[MAXV];
	inline void dfs(reg int u,reg int father){
		if(u<=n){
			lef[u]=++tim;
			rnk[tim]=val[u]=u;
		}
		else
			lef[u]=tim+1;
		fa[u][0]=father;
		for(reg int i=1;i<MAXLOG2V;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			dfs(v,u);
		}
		rig[u]=tim;
		return;
	}
	inline int find(reg int x,reg int y){
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(fa[x][i]&&val[fa[x][i]]>=y)
				x=fa[x][i];
		return x;
	}
	inline void solve(void){
		UnionFind::Init(n<<1);
		for(reg int i=1;i<=m;++i)
			E[i]=Edge(u[i],v[i],-min(u[i],v[i]));
		sort(E+1,E+m+1);
		reg int tot=n;
		for(reg int i=1;i<=m;++i)
			if(!UnionFind::search(E[i].u,E[i].v)){
				++tot;
				val[tot]=abs(E[i].val);
				Add_Edge(tot,UnionFind::find(E[i].u)),Add_Edge(tot,UnionFind::find(E[i].v));
				UnionFind::merge(tot,E[i].u),UnionFind::merge(tot,E[i].v);
			}
		dfs(tot,0);
		return;
	}
}

namespace TreeB{
	int cnt,head[MAXV],to[MAXV],Next[MAXV];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXV][MAXLOG2V];
	int lef[MAXV],rig[MAXV];
	int tim,rnk[MAXV];
	int val[MAXV];
	inline void dfs(reg int u,reg int father){
		if(u<=n){
			lef[u]=++tim;
			rnk[tim]=val[u]=u;
		}
		else
			lef[u]=tim+1;
		fa[u][0]=father;
		for(reg int i=1;i<MAXLOG2V;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			dfs(v,u);
		}
		rig[u]=tim;
		return;
	}
	inline int find(reg int x,reg int y){
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(fa[x][i]&&val[fa[x][i]]<=y)
				x=fa[x][i];
		return x;
	}
	inline void solve(void){
		UnionFind::Init(n<<1);
		for(reg int i=1;i<=m;++i)
			E[i]=Edge(u[i],v[i],max(u[i],v[i]));
		sort(E+1,E+m+1);
		reg int tot=n;
		for(reg int i=1;i<=m;++i)
			if(!UnionFind::search(E[i].u,E[i].v)){
				++tot;
				val[tot]=abs(E[i].val);
				Add_Edge(tot,UnionFind::find(E[i].u)),Add_Edge(tot,UnionFind::find(E[i].v));
				UnionFind::merge(tot,E[i].u),UnionFind::merge(tot,E[i].v);
			}
		dfs(tot,0);
		return;
	}
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*30;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int siz;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int p=++tot;
		siz(p)=siz(pre)+1;
		if(l!=r){
			if(pos<=mid)
				rson(p)=rson(pre),lson(p)=update(lson(pre),l,mid,pos);
			else
				lson(p)=lson(pre),rson(p)=update(rson(pre),mid+1,r,pos);
		}
		return p;
	}
	inline bool query(reg int pre,reg int p,reg int l,reg int r,reg int lef,reg int rig){
		if(lef<=l&&r<=rig)
			return siz(p)>siz(pre);
		if(lef<=mid&&mid<rig)
			return query(lson(pre),lson(p),l,mid,lef,rig)||query(rson(pre),rson(p),mid+1,r,lef,rig);
		else if(lef<=mid)
			return query(lson(pre),lson(p),l,mid,lef,rig);
		else
			return query(rson(pre),rson(p),mid+1,r,lef,rig);
	}
}

int rt[MAXV];
int y[MAXN];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=m;++i)
		u[i]=read()+1,v[i]=read()+1;
	TreeA::solve(),TreeB::solve();
	for(reg int i=1;i<=n;++i)
		y[TreeA::rnk[i]]=i;
	for(reg int i=1;i<=n;++i)
		rt[i]=SegmentTree::update(rt[i-1],1,n,y[TreeB::rnk[i]]);
	while(q--){
		static int s,e,l,r;
		s=read()+1,e=read()+1,l=read()+1,r=read()+1;
		reg int x=TreeA::find(s,l),y=TreeB::find(e,r);
		putchar('0'|SegmentTree::query(rt[TreeB::lef[y]-1],rt[TreeB::rig[y]],1,n,TreeA::lef[x],TreeA::rig[x])),putchar('\n');
	}
	flush();
	return 0;
}