#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=500+5;
const int MAXM=2e3+5;
const int MAXT=1e3+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
int Max[MAXN];
bool del[MAXN][MAXT];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
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

bool vis[MAXN];
int dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline int dijkstra(reg int s,reg int t){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,dis[s]));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id;
		if(u==t)
			return s.val;
		if(vis[u]||dis[u]!=s.val)
			continue;
		reg bool flag=false;
		while(dis[u]<=Max[u]&&del[u][dis[u]])
			flag=true,++dis[u];
		if(flag)
			Q.push(Node(u,dis[u]));
		else{
			vis[u]=true;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>dis[u]+w[i])
					dis[v]=dis[u]+w[i],Q.push(Node(v,dis[u]+w[i]));
			}
		}
	}
	return dis[t];
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,c;
		u=read(),v=read(),c=read();
		Add_Edge(u,v,c),Add_Edge(v,u,c);
	}
	for(reg int i=1;i<=n;++i){
		reg int k=read();
		while(k--){
			reg int t=read();
			Max[i]=max(Max[i],t);
			del[i][t]=true;
		}
	}
	printf("%d\n",dijkstra(1,n));
	return 0;
}