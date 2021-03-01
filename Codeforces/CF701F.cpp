#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int MAXM=3e4+5;
const int inf=2e9+1;

struct Edge{
	int v,id;
	inline Edge(reg int v=0,reg int id=0):v(v),id(id){
		return;
	}
};

int n,m,s,t;
vector<Edge> G[MAXN];
int c[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int id){
	G[u].push_back(Edge(v,id));
	return;
}

bool vis[MAXN];
vector<int> path,bri;

inline bool dfs(reg int u,reg int t){
	vis[u]=true;
	if(u==t)
		return true;
	for(Edge e:G[u]){
		reg int v=e.v;
		if(!vis[v]&&dfs(v,t)){
			path.push_back(e.id);
			return true;
		}
	}
	return false;
}

int del;
int tim,dfn[MAXN],low[MAXN];

inline bool tarjan(reg int u,reg int t,reg int id){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	reg bool res=(u==t);
	for(Edge e:G[u]){
		if(e.id==del||e.id==id)
			continue;
		reg int v=e.v;
		if(!vis[v]){
			reg bool flag=tarjan(v,t,e.id);
			res=res||flag;
			low[u]=min(low[u],low[v]);
			if(low[v]==dfn[v]&&flag)
				bri.push_back(e.id);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	return res;
}

int main(void){
	n=read(),m=read(),s=read(),t=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,w;
		x=read(),y=read(),w=read();
		Add_Edge(x,y,i),Add_Edge(y,x,i);
		c[i]=w;
	}
	if(!dfs(s,t))
		printf("0\n0\n");
	else{
		reg int Min=inf;
		vector<int> ans;
		for(int i:path){
			del=i;
			tim=0;
			bri.clear();
			memset(vis,false,sizeof(vis));
			if(!tarjan(s,t,0))
				if(Min>c[i]){
					Min=c[i];
					ans=vector<int>{i};
				}
			for(int j:bri)
				if(Min>c[i]+c[j]){
					Min=c[i]+c[j];
					ans=vector<int>{i,j};
				}
		}
		if(Min==inf)
			puts("-1");
		else{
			printf("%d\n%lu\n",Min,ans.size());
			for(reg int i=0,siz=ans.size();i<siz;++i)
				printf("%d%c",ans[i],i==siz-1?'\n':' ');
		}
	}
	return 0;
}