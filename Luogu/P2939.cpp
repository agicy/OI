#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
//static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=10000+5;
const int MAXM=50000+5;
const int MAXK=20+5;

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
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	return;
}

struct Node{
	int x,y,val;
	inline Node(reg int x=0,reg int y=0,reg int val=0):x(x),y(y),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

int dis[MAXN][MAXK];
bool vis[MAXN][MAXK];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int sx,reg int sy){
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	dis[sx][sy]=0,Q.push(Node(sx,sy,0));
	while(!Q.empty()){
		reg int x=Q.top().x,y=Q.top().y;
		Q.pop();
		if(vis[x][y])
			continue;
		vis[x][y]=true;
		for(reg int i=head[x];i;i=Next[i]){
			if(dis[to[i]][y]>dis[x][y]+w[i]){
				dis[to[i]][y]=dis[x][y]+w[i];
				Q.push(Node(to[i],y,dis[to[i]][y]));
			}
			if(y<K){
				if(dis[to[i]][y+1]>dis[x][y]){
					dis[to[i]][y+1]=dis[x][y];
					Q.push(Node(to[i],y+1,dis[to[i]][y+1]));
				}
			}
		}
	}
	return;
}

inline void Work(void){
	Dijkstra(1,0);
	int ans=INF;
	for(reg int i=0;i<=K;++i)
		ans=min(ans,dis[n][i]);
	printf("%d\n",ans);
	return;
}
