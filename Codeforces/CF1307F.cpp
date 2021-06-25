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

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=2e5+5;
const int MAXLOG22N=19+1;

namespace UnionFind{
	int fa[MAXN<<1];
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

int n,k,r;
vector<int> G[MAXN<<1];
int _head,_tail;
int Q[MAXN<<1];
int dep[MAXN<<1];

inline void bfs(void){
	while(_head<_tail){
		reg int u=Q[_head++];
		if(dep[u]<=k)
			for(int v:G[u]){
				if(!dep[v])
					dep[v]=dep[u]+1,Q[_tail++]=v;
				UnionFind::merge(u,v);
			}
	}
	return;
}

int fa[MAXN<<1][MAXLOG22N];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG22N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:G[u])
		if(v!=father)
			dfs(v,u);
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG22N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG22N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int getFa(reg int u,reg int k){
	for(reg int i=MAXLOG22N-1;i>=0;--i)
		if((k>>i)&1)
			u=fa[u][i];
	return u;
}

int main(void){
	n=read(),k=read(),r=read();
	if(k&1){
		UnionFind::Init(n+n-1);
		for(reg int i=1;i<n;++i){
			static int u,v;
			u=read(),v=read();
			G[u].push_back(i+n),G[v].push_back(i+n);
			G[i+n].push_back(u),G[i+n].push_back(v);
		}
	}
	else{
		k>>=1;
		UnionFind::Init(n);
		for(reg int i=1;i<n;++i){
			static int u,v;
			u=read(),v=read();
			G[u].push_back(v),G[v].push_back(u);
		}
	}
	for(reg int i=1;i<=r;++i){
		static int u;
		u=read();
		dep[u]=1,Q[_tail++]=u;
	}
	bfs();
	dfs(1,0);
	reg int v=read();
	while(v--){
		static int a,b,lca;
		a=read(),b=read();
		lca=LCA(a,b);
		reg int dis=dep[a]+dep[b]-(dep[lca]<<1);
		if(dis<=(k<<1))
			writeln("YES");
		else{
			static int x,y;
			if(dep[a]-dep[lca]>=k)
				x=getFa(a,k);
			else
				x=getFa(b,dis-k);
			if(dep[b]-dep[lca]>=k)
				y=getFa(b,k);
			else
				y=getFa(a,dis-k);
			if(UnionFind::search(x,y))
				writeln("YES");
			else
				writeln("NO");
		}
	}
	flush();
	return 0;
}