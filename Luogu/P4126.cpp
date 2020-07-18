#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=4000+5;
const int MAXM=60000+5;
const int MAXV=MAXN;
const int MAXE=2*MAXM;

int n,m,s,t;
int u[MAXM];
int id[MAXM];
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline int Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	reg int res=cnt;
	Add_Edge(v,u,0);
	return res;
}

int dep[MAXV];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]>0){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline int DFS(reg int u,reg int t,reg int lim){
	if(u==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]>0){
			reg int f=DFS(v,t,min(lim-flow,w[i]));
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

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int Tarjan_cnt,color[MAXN];

inline void Tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(w[i]<=0)
			continue;
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=S[top--];
			vis[To]=false;
			color[To]=Tarjan_cnt;
		}while(To!=u);
	}
	return;
}

int main(void){
	n=read(),m=read(),s=read(),t=read();
	for(reg int i=1;i<=m;++i){
		static int v,c;
		u[i]=read(),v=read(),c=read();
		id[i]=Add_Tube(u[i],v,c);
	}
	Dinic(s,t);
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			Tarjan(i);
	for(reg int i=1;i<=m;++i){
		reg int U=u[i],V=to[id[i]],C=w[id[i]];
		if(C==0&&color[U]!=color[V]){
			if(color[U]==color[s]&&color[V]==color[t])
				puts("1 1");
			else
				puts("1 0");
		}
		else
			puts("0 0");
	}
	return 0;
}
