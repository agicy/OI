#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1010000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=500+5;
const int MAXV=MAXN*MAXN;
const int MAXE=4*MAXV;

int n;
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline int getId(reg int i,reg int j){
	if(1<=i&&i<=n&&1<=j&&j<=n)
		return (i-1)*n+j;
	else if(i<1||j>n)
		return 0;
	else
		return n*n+1;
}

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

bool vis[MAXV];
int dis[MAXV];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline int dijkstra(reg int s,reg int t){
	memset(vis,false,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,dis[s]));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(vis[u])
			continue;
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				Q.push(Node(v,dis[v]));
			}
		}
	}
	return dis[t];
}

int main(void){
	n=read();
	for(reg int i=1;i<=n+1;++i)
		for(reg int j=1;j<=n;++j){
			static int x;
			x=read();
			Add_Edge(getId(i-1,j),getId(i,j),x);
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n+1;++j){
			static int x;
			x=read();
			Add_Edge(getId(i,j),getId(i,j-1),x);
		}
	for(reg int i=1;i<=n+1;++i)
		for(reg int j=1;j<=n;++j){
			static int x;
			x=read();
			Add_Edge(getId(i,j),getId(i-1,j),x);
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n+1;++j){
			static int x;
			x=read();
			Add_Edge(getId(i,j-1),getId(i,j),x);
		}
	printf("%d\n",dijkstra(0,n*n+1));
	return 0;
}