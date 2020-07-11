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

const int MAXN=200+5;
const int MAXM=20000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,s,t;
int cnt=1,head[MAXN*2],to[MAXM*2+MAXN*2],w[MAXM*2+MAXN*2],Next[MAXM*2+MAXN*2],p[MAXM*2+MAXN*2];

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
	n=read(),m=read(),s=n+1,t=n;
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Add_Tube(a+n,b,1,c);
	}
	for(reg int i=1;i<=n;++i)
		Add_Tube(i,i+n,1,0);
	return;
}

bool inque[MAXN*2];
int dis[MAXN*2];
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

bool vis[MAXN*2];
int Cost=0;
int cur[MAXN*2];

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
