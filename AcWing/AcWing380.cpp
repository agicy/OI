#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e4+5;
const int MAXM=1e4+5;
const int MAXT=1e5+5;
const int MAXV=2*MAXN;
const int MAXE=(MAXN*2+MAXT)*2;
const int inf=0x3f3f3f3f;

int n,m,T;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
int id[MAXE];
vector<int> G[MAXV];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

int dep[MAXV];
queue<int> Q;

inline bool bfs(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]){
			reg int f=dfs(v,t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline int dinic(reg int s,reg int t){
	reg int res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int scc_cnt,col[MAXV];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=0,siz=G[u].size();i<siz;++i){
		reg int v=G[u][i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++scc_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(u!=v);
	}
	return;
}

int main(void){
	n=read(),m=read(),T=read();
	int s=0,t=n+m+1;
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,1);
	for(reg int i=1;i<=m;++i)
		Add_Tube(i+n,t,1);
	for(reg int i=1;i<=T;++i){
		static int x,y;
		x=read(),y=read();
		Add_Tube(x,n+y,1);
		id[i]=cnt;
	}
	dinic(s,t);
	for(reg int i=1;i<=T;++i)
		if(!w[id[i]]){
			int u=to[id[i]],v=to[id[i]^1];
			G[u].push_back(v);
		}
		else{
			int u=to[id[i]^1],v=to[id[i]];
			G[u].push_back(v);
		}
	for(int i=1;i<=n;++i)
		if(!w[2*i])
			G[i].push_back(s);
		else
			G[s].push_back(i);
	for(reg int i=1;i<=m;++i)
		if(!w[2*(n+i)])
			G[t].push_back(n+i);
		else
			G[n+i].push_back(t);
	for(reg int i=s;i<=t;++i)
		if(!dfn[i])
			tarjan(i);
	reg int top=0;
	for(reg int i=1;i<=T;++i)
		if(!w[id[i]]&&col[to[id[i]]]!=col[to[id[i]^1]])
			S[++top]=i;
	printf("%d\n",top);
	if(!top)
		puts("");
	else
		for(reg int i=1;i<=top;++i)
			printf("%d%c",S[i],i==top?'\n':' ');
	return 0;
}