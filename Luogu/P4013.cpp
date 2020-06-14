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
	while('0'<=ch&&ch<='9')res=res*10+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=20+5;
const int MAXM=20+5;
const int MAXV=(MAXM*2+MAXN-1)*MAXN;
const int MAXE=MAXV*3+MAXM*2+MAXN;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int s,t,S;
int cnt,head[MAXV],to[MAXE<<1],w[MAXE<<1],p[MAXE<<1],Next[MAXE<<1];
int a[MAXN][MAXM+MAXN],ID[MAXN][MAXM+MAXN];

inline void Init(void){
	cnt=1;
	memset(head,0,sizeof(head));
	return;
}

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
	m=read(),n=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m+i-1;++j){
			a[i][j]=read();
			ID[i][j]=++tot;
		}
	S=tot;
	s=0,t=(S<<1)+1;
	return;
}

bool inque[MAXV];
int dis[MAXV];
queue<int> Q;

inline bool SPFA(int s,reg int t){
	memset(inque,false,sizeof(inque));
	fill(dis,dis+t+1,-INF);
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]<dis[ID]+p[i]&&w[i]>0){
				dis[to[i]]=dis[ID]+p[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
	}
	return dis[t]!=-INF;
}

bool vis[MAXV];
int cur[MAXV];
int Cost;

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
	Cost=0;
	reg int res=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

inline void Solve1(void){
	Init();
	for(reg int i=1;i<=m;++i)
		Add_Tube(s,ID[1][i],1,0);
	for(reg int i=1;i<=m+n-1;++i)
		Add_Tube(ID[n][i]+S,t,INF,0);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m+i-1;++j)
			Add_Tube(ID[i][j],ID[i][j]+S,1,a[i][j]);
	for(reg int i=1;i<n;++i)
		for(reg int j=1;j<=m+i-1;++j){
			Add_Tube(ID[i][j]+S,ID[i+1][j],1,0);
			Add_Tube(ID[i][j]+S,ID[i+1][j+1],1,0);
		}
	Dinic(s,t);
	printf("%d\n",Cost);
	return;
}

inline void Solve2(void){
	Init();
	for(reg int i=1;i<=m;++i)
		Add_Tube(s,ID[1][i],1,0);
	for(reg int i=1;i<=m+n-1;++i)
		Add_Tube(ID[n][i],t,INF,a[n][i]);
	for(reg int i=1;i<n;++i)
		for(reg int j=1;j<=m+i-1;++j){
			Add_Tube(ID[i][j],ID[i+1][j],1,a[i][j]);
			Add_Tube(ID[i][j],ID[i+1][j+1],1,a[i][j]);
		}
	Dinic(s,t);
	printf("%d\n",Cost);
	return;
}

inline void Solve3(void){
	Init();
	for(reg int i=1;i<=m;++i)
		Add_Tube(s,ID[1][i],1,0);
	for(reg int i=1;i<=m+n-1;++i)
		Add_Tube(ID[n][i],t,INF,a[n][i]);
	for(reg int i=1;i<n;++i)
		for(reg int j=1;j<=m+i-1;++j){
			Add_Tube(ID[i][j],ID[i+1][j],INF,a[i][j]);
			Add_Tube(ID[i][j],ID[i+1][j+1],INF,a[i][j]);
		}
	Dinic(s,t);
	printf("%d\n",Cost);
	return;
}

inline void Work(void){
	Solve1();
	Solve2();
	Solve3();
	return;
}