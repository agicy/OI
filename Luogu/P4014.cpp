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

const int MAXN=100+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,s,t;
int cnt=1,head[MAXN<<1],to[(MAXN*MAXN+MAXN*2)<<1],w[(MAXN*MAXN+MAXN*2)<<1],p[(MAXN*MAXN+MAXN*2)<<1],Next[(MAXN*MAXN+MAXN*2)<<1];

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
	n=read();
	s=0,t=2*n+1;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=n;++j){
			static int c;
			c=read();
			Add_Tube(i,j+n,1,c);
		}
	}
	for(reg int i=1;i<=n;++i)
		Add_Tube(s,i,1,0);
	for(reg int i=1;i<=n;++i)
		Add_Tube(i+n,t,1,0);
	return;
}

bool inque[MAXN<<1];
int dis[MAXN<<1];
queue<int> Q;

inline bool SPFA_Min(int s,reg int t){
	memset(inque,false,sizeof(inque));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i]){
			if(dis[to[i]]>dis[ID]+p[i]&&w[i]>0){
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

inline bool SPFA_Max(int s,reg int t){
	memset(inque,false,sizeof(inque));
	fill(dis,dis+t+1,-INF);
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i]){
			if(dis[to[i]]<dis[ID]+p[i]&&w[i]>0){
				dis[to[i]]=dis[ID]+p[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
		}
	}
	return dis[t]!=-INF;
}

bool vis[MAXN<<1];
int cur[MAXN<<1];
int Cost;

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		Cost+=dis[t]*lim;
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i]){
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
	}
	vis[ID]=false;
	return flow;
}

inline int Dinic_Min(reg int s,reg int t){
	Cost=0;
	reg int res=0;
	while(SPFA_Min(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

inline int Dinic_Max(reg int s,reg int t){
	Cost=0;
	reg int res=0;
	while(SPFA_Max(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

inline void Work(void){
	reg int ans1,ans2;
	Dinic_Min(s,t);
	ans1=Cost;
	for(reg int i=2;i<=cnt;++i)
		w[i]=1^(i&1);
	Dinic_Max(s,t);
	ans2=Cost;
	printf("%d\n%d\n",ans1,ans2);
	return;
}
