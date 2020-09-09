#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=10000+5;
const int MAXM=50000+5;
const int MAXLOG2N=17+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int u[MAXM],v[MAXM];

namespace Graph{
	int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v){
		Add_Edge(u,v);
		Add_Edge(v,u);
		return;
	}
	int tim,dfn[MAXN],low[MAXN];
	int top,S[MAXN];
	int Tarjan_cnt,color[MAXN];
	inline void Tarjan(reg int ID,reg int fa){
		dfn[ID]=low[ID]=++tim;
		S[++top]=ID;
		for(reg int i=head[ID];i;i=Next[i])
			if(to[i]!=fa){
				if(!dfn[to[i]]){
					Tarjan(to[i],ID);
					low[ID]=min(low[ID],low[to[i]]);
				}
				else
					low[ID]=min(low[ID],dfn[to[i]]);
			}
		if(dfn[ID]==low[ID]){
			color[ID]=++Tarjan_cnt;
			while(S[top]!=ID)
				color[S[top--]]=Tarjan_cnt;
			--top;
		}
		return;
	}
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		Graph::Add_Tube(u[i],v[i]);
	}
	return;
}

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v){
		Add_Edge(u,v);
		Add_Edge(v,u);
		return;
	}
	int dep[MAXN];
	int fa[MAXN][MAXLOG2N];
	inline void DFS(reg int ID,reg int father){
		fa[ID][0]=father;
		dep[ID]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[ID][i]=fa[fa[ID][i-1]][i-1];
		for(reg int i=head[ID];i;i=Next[i])
			if(to[i]!=father)
				DFS(to[i],ID);
		return;
	}
	inline int LCA(int x,int y){
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x])
				y=fa[y][i];
		if(x==y)
			return x;
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i])
				x=fa[y][i],y=fa[y][i];
		return fa[x][0];
	}
	inline int dis(reg int u,reg int v){
		reg int lca=LCA(u,v);
		return dep[u]+dep[v]-(dep[lca]<<1)+1;
	}
}

using Graph::color;

inline void print(reg int x){
	if(!x)
		return;
	print(x/2);
	putchar(x%2+'0');
	return;
}

inline void write(reg int x){
	if(!x)
		putchar('0');
	else
		print(x);
	putchar('\n');
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::Tarjan(i,0);
	for(reg int i=1;i<=m;++i)
		if(color[u[i]]!=color[v[i]])
			Tree::Add_Tube(color[u[i]],color[v[i]]);
	for(reg int i=1;i<=Graph::Tarjan_cnt;++i)
		if(!Tree::dep[i])
			Tree::DFS(i,0);
	reg int T=read();
	while(T--){
		static int a,b;
		a=read(),b=read();
		write(Tree::dis(color[a],color[b]));
	}
	return;
}
