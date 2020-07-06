#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200000+5;
const int MAXLOG2N=18;

vector<int> G[MAXN],T[MAXN];

bool vis[MAXN];
int tim,low[MAXN],dfn[MAXN];
int S[MAXN],*top;

int fa[MAXN][MAXLOG2N],dep[MAXN],dis[MAXN];
int c[MAXN];
int n,m,tot;

inline void Clear(void){
	top=S,tim=0;
	for(reg int i=1;i<=n;++i)
		G[i].clear();
	for(reg int i=1;i<=tot;++i)
		T[i].clear(),dfn[i]=0;
	return;
}

inline void Tarjan(reg int u,reg int fa){
	dfn[u]=low[u]=++tim,vis[u]=true,*++top=u;
	for(reg int i=0,size=G[u].size();i<size;++i){
		int v=G[u][i];
		if(v==fa||dfn[v]>dfn[u])
			continue;
		if(!dfn[v]){
			Tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
			continue;
		}
		if(low[v]==dfn[u]){
			++tot;
			T[u].push_back(tot);
			while(*top!=v){
				vis[*top]=0,
				T[tot].push_back(*top),
				--top;
			}
			T[tot].push_back(v);
			vis[v]=false;
			--top;
		}
		else if(low[v]>dfn[u])
			T[u].push_back(v),--top,vis[v]=false;
	}
}

inline void DFS(reg int u){
	dfn[u]=++tim;
	for(reg int i=0,size=T[u].size();i<size;++i){
		reg int v=T[u][i];
		dep[v]=dep[u]+1;
		dis[v]=dis[u]+(v<=n);
		fa[v][0]=u;
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[v][i]=fa[fa[v][i-1]][i-1];
		DFS(v);
	}
	return;
}

inline int LCA(int x,int y){
	if(dep[x]<dep[y])
		swap(x,y);
	for(reg int d=dep[x]-dep[y],i=0;i<MAXLOG2N;++i)
		if((d>>i)&1)
			x=fa[x][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int GetDis(reg int x,reg int y){
	reg int lca=LCA(x,y);
	return dis[x]+dis[y]-2*dis[lca];
}

inline bool cmp(reg int a,reg int b){
	return dfn[a]<dfn[b];
}

int main(void){
	reg int T=read();
	while(T--){
		Clear();
		n=read(),m=read(),tot=n;
		for(reg int i=1;i<=m;++i){
			static int x,y;
			x=read(),y=read();
			G[x].push_back(y);
			G[y].push_back(x);
		}
		Tarjan(1,-1);
		dep[1]=0,dis[1]=0,tim=0;
		DFS(1);
		reg int q=read();
		while(q--){
			reg int s=read();
			for(reg int i=0;i<s;++i)
				c[i]=read();
			sort(c,c+s,cmp);
			c[s]=c[0];
			reg int x=0;
			for(reg int i=0;i<s;++i)
				x+=GetDis(c[i],c[i+1]);
			printf("%d\n",x/2-s+(LCA(c[0],c[s-1])<= n));
		}
	}
	return 0;
}