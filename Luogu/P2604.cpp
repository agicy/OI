#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=1000+5;
const int MAXM=5000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,K,s,t;
int cnt=1,head[MAXN],to[MAXM<<2],w[MAXM<<2],p[MAXM<<2],Next[MAXM<<2];
int u[MAXM],v[MAXM],W[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

inline void Read(void){
	n=read(),m=read(),K=read();
	s=1,t=n;
	for(reg int i=1;i<=m;++i){
		static int c;
		u[i]=read(),v[i]=read(),c=read(),W[i]=read();
		Add_Tube(u[i],v[i],c,0);
	}
	return;
}

int dep[MAXN];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i])
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXN];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
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

bool inque[MAXN];
int dis[MAXN];

inline bool SPFA(int s,reg int t){
	memset(inque,false,sizeof(inque));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+p[i]&&w[i]>0){
				dis[to[i]]=dis[ID]+p[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
	}
	return dis[t]!=INF;
}

bool vis[MAXN];
int MaxCost;

inline int DFS_(reg int ID,reg int t,reg int lim){
	if(ID==t){
		MaxCost+=dis[t]*lim;
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dis[to[i]]==dis[ID]+p[i]&&w[i]>0&&!vis[to[i]]){
			reg int f=DFS_(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	vis[ID]=false;
	return flow;
}

inline int Dinic_(reg int s,reg int t){
	reg int res=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS_(s,t,INF);
	}
	return res;
}

inline void Work(void){
	reg int ans1=Dinic(s,t);
	for(reg int i=1;i<=m;++i)
		Add_Tube(u[i],v[i],INF,W[i]);
	Add_Tube(0,1,K,0);
	Dinic_(0,t);
	reg int ans2=MaxCost;
	printf("%d %d\n",ans1,ans2);
	return;
}
