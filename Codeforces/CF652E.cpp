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

const int MAXN=3e5+5;
const int MAXM=3e5+5;

namespace Graph{
	int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int tim,dfn[MAXN],low[MAXN];
	bool bri[MAXM<<1];
	inline void tarjan(reg int u,reg int id){
		dfn[u]=low[u]=++tim;
		for(reg int i=head[u];i;i=Next[i]){
			if(i==id)
				continue;
			reg int v=to[i];
			if(!dfn[v]){
				tarjan(v,i^1);
				low[u]=min(low[u],low[v]);
				if(dfn[u]<low[v])
					bri[i]=bri[i^1]=true;
			}
			else
				low[u]=min(low[u],dfn[v]);
		}
		return;
	}
	int eDcc_cnt,col[MAXN];
	bool tag[MAXN];
	inline void dfs(reg int u,reg int color){
		col[u]=color;
		for(reg int i=head[u];i;i=Next[i])
			if(!bri[i]){
				reg int v=to[i];
				tag[color]=tag[color]||w[i];
				if(!col[v])
					dfs(v,color);
			}
		return ;
	}
}

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	bool vis[MAXN];
	inline bool dfs(reg int u,reg int t,reg bool flag){
		vis[u]=true;
		flag=flag||Graph::tag[u];
		if(u==t)
			return flag;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[v]&&dfs(v,t,flag||w[i]))
				return true;
		}
		return false;
	}
}

int n,m,a,b;
int x[MAXM],y[MAXM],z[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		x[i]=read(),y[i]=read(),z[i]=read();
		Graph::Add_Edge(x[i],y[i],z[i]),Graph::Add_Edge(y[i],x[i],z[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!Graph::dfn[i])
			Graph::tarjan(i,0);
	for(reg int i=1;i<=n;++i)
		if(!Graph::col[i])
			Graph::dfs(i,++Graph::eDcc_cnt);
	for(reg int i=1;i<=m;++i)
		if(Graph::col[x[i]]!=Graph::col[y[i]])
			Tree::Add_Edge(Graph::col[x[i]],Graph::col[y[i]],z[i]),Tree::Add_Edge(Graph::col[y[i]],Graph::col[x[i]],z[i]);
	a=read(),b=read();
	if(Tree::dfs(Graph::col[a],Graph::col[b],false))
		puts("Yes");
	else
		puts("No");
	return 0;
}