#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=20000+5;
const int MAXLOG2N=15+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,q;
int Log[MAXN];
ll g[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),q=read();
	for(reg int i=2;i<=n;++i)
		Log[i]=Log[i>>1]+1;
	for(reg int i=1;i<=n;++i)
		g[i]=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	return;
}

const int MAXLOG2G=61;

struct Basis{
	ll p[MAXLOG2G];
	inline Basis(void){
		memset(p,0,sizeof(p));
		return;
	}
	inline void insert(reg ll x){
		for(reg int i=MAXLOG2G-1;i>=0;--i){
			if(!((x>>i)&1))
				continue;
			if(!p[i]){
				p[i]=x;
				break;
			}
			else
				x^=p[i];
		}
		return;
	}
	inline ll query(void){
		reg ll res=0;
		for(reg int i=MAXLOG2G-1;i>=0;--i)
			if((res^p[i])>res)
				res^=p[i];
		return res;
	}
};

inline Basis merge(const Basis& a,const Basis& b){
	Basis res=b;
	for(reg int i=MAXLOG2G-1;i>=0;--i)
		res.insert(a.p[i]);
	return res;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
Basis B[MAXN][MAXLOG2N];

inline void DFS(reg int ID,reg int father){
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	B[ID][0].insert(g[ID]);
	for(reg int i=1;i<=Log[dep[ID]];++i){
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
		B[ID][i]=merge(B[ID][i-1],B[fa[ID][i-1]][i-1]);
	}
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID);
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	while(dep[y]>dep[x])
		y=fa[y][Log[dep[y]-dep[x]]];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int kth(reg int x,reg int k){
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if((k>>i)&1)
			x=fa[x][i];
	return x;
}

inline ll Query(reg int x,reg int y){
	Basis ans;
	reg int lca=LCA(x,y);
	ans=merge(ans,B[lca][0]);
	reg int len=Log[dep[x]-dep[lca]];
	ans=merge(ans,B[x][len]);
	ans=merge(ans,B[kth(x,dep[x]-dep[lca]-(1<<len))][len]);
	len=Log[dep[y]-dep[lca]];
	ans=merge(ans,B[y][len]);
	ans=merge(ans,B[kth(y,dep[y]-dep[lca]-(1<<len))][len]);
	return ans.query();
}

inline void Work(void){
	DFS(1,0);
	while(q--){
		static int x,y;
		x=read(),y=read();
		printf("%lld\n",Query(x,y));
	}
	return;
}