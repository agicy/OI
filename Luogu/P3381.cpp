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
int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1],p[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read(),s=read(),t=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w,f;
		u=read(),v=read(),w=read(),f=read();
		Add_Edge(u,v,w,f);
		Add_Edge(v,u,0,-f);
	}
	return;
}

bool inque[MAXN];
int dis[MAXN];
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

bool vis[MAXN];
int Cost=0;
int cur[MAXN];

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
	reg int ans=Dinic(s,t);
	printf("%d %d\n",ans,Cost);
	return;
}
