#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b) a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

const int MAXN=2e5+5;
const int MAXM=5e5+5;

int n,m;
int k[MAXN];
int a[MAXM],b[MAXM];

namespace Graph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	bool vis[MAXN];
	int tim,dfn[MAXN],low[MAXN];
	int top,S[MAXN];
	int scc_cnt,col[MAXN],siz[MAXN],Max[MAXN];
	inline void tarjan(reg int u){
		vis[u]=true;
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!dfn[v]){
				tarjan(v);
				cMin(low[u],low[v]);
			}
			else if(vis[v])
				cMin(low[u],dfn[v]);
		}
		if(dfn[u]==low[u]){
			++scc_cnt;
			reg int v;
			do{
				v=S[top--];
				vis[v]=false;
				col[v]=scc_cnt;
				siz[scc_cnt]+=k[v];
				cMax(Max[scc_cnt],k[v]);
			}while(v!=u);
		}
		return;
	}
}

namespace DAG{
	int indeg[MAXN];
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		++indeg[v];
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int Q[MAXN];
	int f[MAXN],g[MAXN];
	inline void topo(void){
		reg int head_=0,tail_=0;
		for(reg int i=1;i<=Graph::scc_cnt;++i)
			if(!indeg[i]){
				Q[tail_++]=i;
				f[i]=Graph::siz[i],g[i]=Graph::Max[i];
			}
		reg int ans1=0,ans2=0;
		while(head_<tail_){
			reg int u=Q[head_++];
			if(f[u]>ans1)
				ans1=f[u],ans2=g[u];
			else if(f[u]==ans1)
				ans2=g[u];
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				--indeg[v];
				if(f[v]<f[u]+Graph::siz[v]){
					f[v]=f[u]+Graph::siz[v];
					g[v]=max(g[u],Graph::Max[v]);
				}
				else if(f[v]==f[u]+Graph::siz[v])
					g[v]=max(g[u],Graph::Max[v]);
				if(!indeg[v])
					Q[tail_++]=v;
			}
		}
		printf("%d %d\n",ans1,ans2);
		return;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		k[i]=read();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read();
		Graph::Add_Edge(a[i],b[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i);
	for(reg int i=1;i<=m;++i){
		reg int u=Graph::col[a[i]],v=Graph::col[b[i]];
		if(u!=v)
			DAG::Add_Edge(u,v);
	}
	DAG::topo();
	return 0;
}