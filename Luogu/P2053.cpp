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

const int MAXN=60+5;
const int MAXM=9+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int m,n;
int T[MAXN][MAXM];

inline void Read(void){
	m=read(),n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			T[i][j]=read();
	return;
}

int cnt=1,head[MAXN*MAXM],to[(MAXN*MAXM+MAXN*MAXN*MAXM+MAXN)*2],w[(MAXN*MAXM+MAXN*MAXN*MAXM+MAXN)*2],p[(MAXN*MAXM+MAXN*MAXN*MAXM+MAXN)*2],Next[(MAXN*MAXM+MAXN*MAXN*MAXM+MAXN)*2];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int c){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=c;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int c){
	Add_Edge(u,v,len,c);
	Add_Edge(v,u,0,-c);
	return;
}

bool inque[MAXN*MAXM];
int dis[MAXN*MAXM];
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
			if(w[i]>0&&dis[to[i]]>dis[ID]+p[i]){
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

bool vis[MAXN*MAXM];
int cur[MAXN*MAXM];
int MinCost;

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		MinCost+=dis[t]*lim;
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i]){
		if(w[i]>0&&dis[to[i]]==dis[ID]+p[i]&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	vis[ID]=false;
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

inline void Work(void){
	reg int V=n*m;
	reg int s=0,t=V+n+1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			for(reg int k=1;k<=n;++k)
			Add_Tube(V+i,(k-1)*m+j,1,k*T[i][j]);
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,V+i,1,0);
	for(reg int i=1;i<=V;++i)
		Add_Tube(i,t,1,0);
	Dinic(s,t);
	printf("%.2f\n",1.0*MinCost/n);
	return;
}
