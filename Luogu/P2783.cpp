#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void print(reg int x){
	if(x<0)
		putchar('-'),x=-x;
	if(!x)
		return;
	print(x/2);
	putchar(x%2+48);
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

const int MAXN=10000+5;
const int MAXM=50000+5;
const int MAXLOG2N=ceil(log2(MAXN))+1;

int n,m;

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	int fa[MAXN][MAXLOG2N],dep[MAXN];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void DFS(reg int ID,reg int father){
		dep[ID]=dep[father]+1;
		fa[ID][0]=father;
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
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	inline int GetDis(reg int a,reg int b){
		return dep[a]+dep[b]-2*dep[LCA(a,b)]+1;
	}
};

namespace Graph{
	int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
	int tim,dfn[MAXN],low[MAXN];
	int top,S[MAXN];
	int Tarjan_cnt,color[MAXN];
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
	inline void Tarjan(reg int ID,reg int father){
		dfn[ID]=low[ID]=++tim;
		S[++top]=ID;
		for(reg int i=head[ID];i;i=Next[i])
			if(to[i]==father)
				continue;
			else if(!dfn[to[i]]){
				Tarjan(to[i],ID);
				low[ID]=min(low[ID],low[to[i]]);
			}
			else
				low[ID]=min(low[ID],dfn[to[i]]);
		if(dfn[ID]==low[ID]){
			++Tarjan_cnt;
			while(S[top]!=ID)
				color[S[top--]]=Tarjan_cnt;
			color[S[top--]]=Tarjan_cnt;
		}
		return;
	}
};

using Graph::color;

int main(void){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Graph::Add_Tube(u,v);
	}
	for(int i=1;i<=n;i++)
		if(!Graph::dfn[i])
			Graph::Tarjan(i,0);
	for(reg int ID=1;ID<=n;++ID)
		for(reg int i=Graph::head[ID];i;i=Graph::Next[i])
			if(color[Graph::to[i]]!=color[ID])
				Tree::Add_Edge(color[Graph::to[i]],color[ID]);
	Tree::DFS(1,0);
	reg int q=read();
	while(q--){
		static int a,b;
		a=read(),b=read();
		write(Tree::GetDis(color[a],color[b]));
	}
	return 0;
}