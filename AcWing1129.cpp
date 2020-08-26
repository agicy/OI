#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXT=2.5e3+5;
const int MAXC=6.2e3+5;

int T,C,Ts,Te;
int cnt,head[MAXT],to[MAXC<<1],w[MAXC<<1],Next[MAXC<<1];

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

bool vis[MAXT];
int dis[MAXT];
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
	return;
}

int main(void){
	scanf("%d%d%d%d",&T,&C,&Ts,&Te);
	for(reg int i=1;i<=C;++i){
		static int s,e,c;
		scanf("%d%d%d",&s,&e,&c);
		Add_Edge(s,e,c);
		Add_Edge(e,s,c);
	}
	Dijkstra(Ts);
	printf("%d\n",dis[Te]);
	return 0;
}