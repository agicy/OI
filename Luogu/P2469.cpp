#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=5000+5;
const int MAXM=50000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,s,t;
int a[MAXN];
int cnt=1,head[MAXN<<1],to[MAXN*6+MAXM*2],w[MAXN*6+MAXM*2],Next[MAXN*6+MAXM*2],p[MAXN*6+MAXM*2];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read(),s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		if(u>v)
			swap(u,v);
		if(w<a[v]){
			Add_Edge(u,v+n,1,w);
			Add_Edge(v+n,u,0,-w);
		}
	}
	for(reg int i=1;i<=n;++i){
		Add_Edge(s,i,1,0);
		Add_Edge(i,s,0,-0);
		Add_Edge(i+n,t,1,0);
		Add_Edge(t,i+n,0,-0);
		Add_Edge(s,i+n,1,a[i]);
		Add_Edge(i+n,s,0,-a[i]);
	}
	return;
}

bool inque[MAXN<<1];
int dis[MAXN<<1];
queue<int> Q;

inline bool SPFA(int s,reg int t){
	memset(inque,false,sizeof(inque));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i]){
			if(w[i]&&dis[to[i]]>dis[ID]+p[i]){
				dis[to[i]]=dis[ID]+p[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
		}
	}
	return dis[t]!=INF;
}

bool vis[MAXN<<1];
int Cost=0;
int cur[MAXN<<1];

inline int DFS(reg int ID,reg int t,reg int flow){
	if(ID==t){
		Cost+=flow*dis[t];
		return flow;
	}
	vis[ID]=true;
	reg int res=0;
	for(reg int &i=cur[ID];i;i=Next[i]){
		if(w[i]&&dis[to[i]]==dis[ID]+p[i]&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(flow-res,w[i]));
			if(f){
				res+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow-res==0)
					break;
			}
		}
	}
	vis[ID]=false;
	return res;
}

inline int Dinic(reg int s,reg int t){
	reg int MaxFlow=0;
	while(SPFA(s,t)){
		memset(vis,false,sizeof(vis));
		memcpy(cur,head,sizeof(head));
		MaxFlow+=DFS(s,t,INF);
	}
	return MaxFlow;
}

inline void Work(void){
	Dinic(s,t);
	printf("%d\n",Cost);
	return;
}
