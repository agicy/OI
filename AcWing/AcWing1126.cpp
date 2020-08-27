#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e3+5;
const int MAXM=1e5+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
double w[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id;
	double val;
	inline Node(reg int id=0,reg double val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

const double inf=1e20;

bool vis[MAXN];
double dis[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int s){
	memset(vis,false,sizeof(vis));
	for(reg int i=1;i<=n;++i)
		dis[i]=inf;
	dis[s]=100,Q.push(Node(s,dis[s]));
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
			if(dis[v]>dis[u]*w[i]){
				dis[v]=dis[u]*w[i];
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
		Add_Edge(x,y,100.0/(100.0-z));
		Add_Edge(y,x,100.0/(100.0-z));
	}
	int A,B;
	scanf("%d%d",&A,&B);
	Dijkstra(A);
	printf("%.8lf\n",dis[B]);
	return 0;
}