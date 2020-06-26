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

const int MAXN=2000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return x==a.x?y<a.y:x<a.x;
	}
};

int n;
Node P[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		P[i].Read();
	return;
}

int cnt=1,head[MAXN<<1],to[(MAXN*MAXN/2+MAXN*3)<<1],w[(MAXN*MAXN/2+MAXN*3)<<1],p[(MAXN*MAXN/2+MAXN*3)<<1],Next[(MAXN*MAXN/2+MAXN*3)<<1];

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

bool vis[MAXN<<1];
int cur[MAXN<<1];
int MinCost;

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		MinCost+=lim*dis[t];
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

inline void Work(void){
	sort(P+1,P+n+1);
	int S=0,tempS=n+n+1,tempT=tempS+1,T=tempT+1;
	for(reg int i=1;i<=n;++i){
		Add_Tube(tempS,i,1,0);
		Add_Tube(i,i+n,1,-1);
		Add_Tube(i,i+n,1,0);
		Add_Tube(i+n,tempT,1,0);
	}
	Add_Tube(S,tempS,2,0);
	Add_Tube(tempT,T,2,0);
	for(reg int i=1;i<=n;++i){
		int Min=INF;
		for(reg int j=i+1;j<=n;++j){
			if(P[j].y<Min&&P[j].y>=P[i].y)
				Add_Tube(i+n,j,2,0);
			if(P[j].y>=P[i].y)
				Min=min(Min,P[j].y);
		}
	}
	Dinic(S,T);
	reg int ans=-MinCost;
	printf("%d\n",ans);
	return;
}
