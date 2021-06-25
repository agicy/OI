#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

const int MAXLOG2N=21;
const int MAXN=2e5+9;

int n,m,c;
int p[MAXN];
int w[MAXN],rnk[MAXN];
vector<int> G[MAXN];
int fa[3][MAXN][MAXLOG2N],dep[MAXN];

inline void dfs1(reg int u,reg int father){
	dep[u]=dep[father]+1;
	fa[0][u][0]=father;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[0][u][i]=fa[0][fa[0][u][i-1]][i-1];
	for(int v:G[u])
		if(v!=father)
			dfs1(v,u);
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[0][y][i]]>=dep[x])
			y=fa[0][y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[0][x][i]!=fa[0][y][i])
			x=fa[0][x][i],y=fa[0][y][i];
	return fa[0][x][0];
}

int col[MAXN];

inline void dfs2(reg int u,reg int father){
	reg int tmp=col[w[u]];
	col[w[u]]=u;
	fa[1][u][0]=col[w[u]+1],fa[2][u][0]=col[w[u]-1];
	for(int v:G[u])
		if(v!=father)
			dfs2(v,u);
	col[w[u]]=tmp;
	return;
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*50;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int pos;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define pos(x) unit[(x)].pos
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(void){
		reg int p=++tot;
		lson(p)=rson(p)=pos(p)=0;
		return p;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int Pos,reg int Val){
		reg int p=++tot;
		unit[p]=unit[pre],pos(p)=Val;
		if(l!=r){
			if(Pos<=mid)
				lson(p)=update(lson(pre),l,mid,Pos,Val);
			else
				rson(p)=update(rson(pre),mid+1,r,Pos,Val);
		}
		return p;
	}
	inline int query(reg int p,reg int l,reg int r,reg int Pos){
		if(!p)
			return 0;
		if(l==r)
			return pos(p);
		if(Pos<=mid)
			return query(lson(p),l,mid,Pos);
		else
			return query(rson(p),mid+1,r,Pos);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef pos
}

int rt[MAXN];

inline void dfs3(reg int u,reg int father){
	rt[u]=SegmentTree::update(rt[father],1,n,w[u],u);
	for(int v:G[u])
		if(v!=father)
			dfs3(v,u);
	return;
}

inline int trans(reg int u,reg int k,reg int f){
	if(dep[u]<k)
		return 0;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[f][u][i]]>=k)
			u=fa[f][u][i];
	return w[u];
}

inline bool check(reg int v,reg int lim,reg int k,reg int bas){
	reg int u=SegmentTree::query(rt[v],1,n,lim);
	if(dep[u]<k)
		return false;
	else
		return trans(u,k,2)<=bas+1;
}

int main(void){
	n=read(),m=read(),c=read();
	for(reg int i=1;i<=c;++i)
		p[i]=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	reg int tot=c;
	for(reg int i=1;i<=c;++i)
		rnk[p[i]]=i;
	for(reg int i=1;i<=n;++i){
		if(!rnk[w[i]])
			rnk[w[i]]=++tot;
		w[i]=rnk[w[i]];
	}
	dfs1(1,0),dfs2(1,0);
	for(reg int j=1;j<MAXLOG2N;++j)
		for(reg int i=1;i<=n;++i)
			fa[1][i][j]=fa[1][fa[1][i][j-1]][j-1],fa[2][i][j]=fa[2][fa[2][i][j-1]][j-1];
	dfs3(1,0);
	reg int q=read();
	while(q--){
		static int u,v;
		u=read(),v=read();
		reg int lca=LCA(u,v);
		reg int bas=min(trans(SegmentTree::query(rt[u],1,n,1),dep[lca],1),c);
		reg int l=bas,r=c,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(check(v,mid+1,dep[lca],bas))
				l=mid+1;
			else
				r=mid;
		}
		writeln(l);
	}
	flush();
	return 0;
}