#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const int MAXM=1e4+5;

int n,m;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

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
int dis[MAXN][2];
int sum[MAXN][2];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Dijkstra(reg int s){
	memset(dis,0x3f,sizeof(dis));
	memset(sum,0x00,sizeof(sum));
	dis[s][0]=0,sum[s][0]=1,Q.push(Node(s,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		reg int u=s.id,k=-1;
		if(dis[u][0]==s.val)
			k=0;
		if(dis[u][1]==s.val)
			k=1;
		if(k==-1)
			continue;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			reg int val=s.val+w[i];
			if(dis[v][0]>val){
				dis[v][1]=dis[v][0],sum[v][1]=sum[v][0];
				dis[v][0]=val,sum[v][0]=sum[u][k];
				Q.push(Node(v,val));
			}
			else if(dis[v][0]==val)
				sum[v][0]+=sum[u][k];
			else if(dis[v][1]>val){
				dis[v][1]=val;
				sum[v][1]=sum[u][k];
				Q.push(Node(v,val));
			}
			else if(dis[v][1]==val)
				sum[v][1]+=sum[u][k];
		}
	}
	return;
}

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		scanf("%d%d",&n,&m);
		for(reg int i=1;i<=m;++i){
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			Add_Edge(a,b,c);
		}
		int S,T;
		scanf("%d%d",&S,&T);
		Dijkstra(S);
		if(dis[T][0]==dis[T][1]-1)
			printf("%d\n",sum[T][0]+sum[T][1]);
		else
			printf("%d\n",sum[T][0]);
	}
	return 0;
}