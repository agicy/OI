#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const int MAXM=2e4+5;
const int inf=0x3f3f3f3f;

int n,m,t;
int cnt,head[MAXN],to[MAXM+MAXN],w[MAXM+MAXN],Next[MAXM+MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
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

inline void Dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(Node(s,0));
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
}

int main(void){
	while(scanf("%d%d%d",&n,&m,&t)!=EOF){
		cnt=0,memset(head,0,sizeof(head));
		for(reg int i=1;i<=m;++i){
			static int p,q,t;
			scanf("%d%d%d",&p,&q,&t);
			Add_Edge(p,q,t);
		}
		int W;
		scanf("%d",&W);
		reg int s=0;
		for(reg int i=1;i<=W;++i){
			static int x;
			scanf("%d",&x);
			Add_Edge(s,x,0);
		}
		Dijkstra(s);
		printf("%d\n",dis[t]==inf?-1:dis[t]);
	}
	return 0;
}