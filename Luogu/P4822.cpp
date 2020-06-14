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

const int MAXN=50+5;
const int MAXM=1000+5;
const int MAXK=50+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,K;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=m;++i){
		static int a,b,t;
		a=read(),b=read(),t=read();
		Add_Edge(a,b,t);
		Add_Edge(b,a,t);
	}
	return;
}

struct Node{
	int k,ID,dis;
	inline Node(reg int k=0,reg int ID=0,reg int dis=0):k(k),ID(ID),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

bool vis[MAXK][MAXN];
int dis[MAXK][MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int sk,reg int si){
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	dis[sk][si]=0,Q.push(Node(sk,si,0));
	while(!Q.empty()){
		reg int k=Q.top().k;
		reg int ID=Q.top().ID;
		Q.pop();
		if(vis[k][ID])
			continue;
		vis[k][ID]=true;
		for(reg int i=head[ID];i;i=Next[i]){
			if(dis[k][to[i]]>dis[k][ID]+w[i]){
				dis[k][to[i]]=dis[k][ID]+w[i];
				Q.push(Node(k,to[i],dis[k][to[i]]));
			}
			if(k+1<=K&&dis[k+1][to[i]]>dis[k][ID]+w[i]/2){
				dis[k+1][to[i]]=dis[k][ID]+w[i]/2;
				Q.push(Node(k+1,to[i],dis[k+1][to[i]]));
			}
		}
	}
	return;
}

inline void Work(void){
	Dijkstra(0,1);
	int ans=INF;
	for(reg int i=0;i<=K;++i)
		ans=min(ans,dis[i][n]);
	printf("%d\n",ans);
	return;
}