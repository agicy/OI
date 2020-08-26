#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;
const int MAXM=200+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

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
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		Add_Edge(x,y,z);
		Add_Edge(y,x,z);
	}
	Dijkstra(1);
	int ans=0;
	for(reg int i=1;i<=n;++i){
		if(dis[i]==0x3f3f3f3f){
			puts("-1");
			exit(0);
		}
		ans=max(ans,dis[i]);
	}
	printf("%d\n",ans);
	return 0;
}