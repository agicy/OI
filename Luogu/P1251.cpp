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

const int MAXN=2000+5;
const int MAXV=2*MAXN;
const int MAXE=12*MAXN;

int cnt=1,head[MAXV],to[MAXE],w[MAXE],p[MAXE],Next[MAXE];

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

bool inque[MAXV];
int dis[MAXV];
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

ll Cost;
bool vis[MAXV];
int cur[MAXV];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		Cost+=dis[t]*lim;
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dis[to[i]]==dis[ID]+p[i]&&w[i]>0&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
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

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

int n,m,t1,t2,m1,m2;

int main(void){
	n=read();
	reg int s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		Add_Tube(s,i,x,0);
		Add_Tube(i+n,t,x,0);
	}
	m=read(),t1=read(),m1=read(),t2=read(),m2=read();
	for(reg int i=1;i<=n;++i){
		if(i+1<=n)
			Add_Tube(i,i+1,INF,0);
		if(i+t1<=n)
			Add_Tube(i,i+n+t1,INF,m1);
		if(i+t2<=n)
			Add_Tube(i,i+n+t2,INF,m2);
		Add_Tube(s,i+n,INF,m);
	}
	Dinic(s,t);
	printf("%lld\n",Cost);
	return 0;
}