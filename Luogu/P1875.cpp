#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const int MAXM=MAXN*MAXN;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

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
int dis[MAXN],f[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void dijkstra(void){
	for(reg int i=0;i<n;++i){
		Q.push(Node(i,dis[i]));
		f[i]=1;
	}
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
			if(vis[w[i]]){
				if(dis[v]>dis[u]+dis[w[i]]){
					dis[v]=dis[u]+dis[w[i]];
					f[v]=f[u]*f[w[i]];
					Q.push(Node(v,dis[v]));
				}
				else if(dis[v]==dis[u]+dis[w[i]]){
					f[v]+=f[u]*f[w[i]];
				}
			}
		}
	}
	return;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=0;i<n;++i)
		scanf("%d",&dis[i]);
	int a,b,c;
	while(scanf("%d%d%d",&a,&b,&c)!=EOF)
		if(a!=b)
			Add_Edge(a,c,b),Add_Edge(b,c,a);
		else
			Add_Edge(a,c,b);
	dijkstra();
	printf("%d %d\n",dis[0],f[0]);
	return 0;
}