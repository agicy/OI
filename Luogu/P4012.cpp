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

const int MAXP=15+5;
const int MAXQ=15+5;
const int MAXA=4+5;
const int MAXB=6+5;
const int MAXV=MAXP*MAXQ;
const int MAXE=(4*MAXP*MAXQ+MAXA+MAXB)<<1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int a,b,P,Q,s,t;
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

inline int GetID(reg int i,reg int j){
	return (i-1)*Q+j;
}

inline void Read(void){
	a=read(),b=read(),P=read()+1,Q=read()+1;
	s=0,t=P*Q+1;
	for(reg int i=1;i<=P;++i)
		for(reg int j=1;j<Q;++j){
			static int x;
			reg int hh=GetID(i,j);
			reg int tt=hh+1;
			x=read();
			Add_Tube(hh,tt,1,-x);
			Add_Tube(hh,tt,INF,0);
		}
	for(reg int j=1;j<=Q;++j)
		for(reg int i=1;i<P;++i){
			static int x;
			reg int hh=GetID(i,j);
			reg int tt=hh+Q;
			x=read();
			Add_Tube(hh,tt,1,-x);
			Add_Tube(hh,tt,INF,0);
		}
	for(reg int i=1;i<=a;++i){
		static int k,x,y;
		k=read(),x=read()+1,y=read()+1;
		Add_Tube(s,GetID(x,y),k,0);
	}
	for(reg int i=1;i<=b;++i){
		static int k,x,y;
		k=read(),x=read()+1,y=read()+1;
		Add_Tube(GetID(x,y),t,k,0);
	}
	return;
}

bool inque[MAXV];
int dis[MAXV];

inline bool SPFA(int s,reg int t){
	queue<int> Q;
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

bool vis[MAXV];
int Cost;
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

inline void Work(void){
	Dinic(s,t);
	printf("%d\n",-Cost);
	return;
}