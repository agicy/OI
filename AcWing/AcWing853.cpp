#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int MAXM=1e5+5;
const int MAXK=500+5;

int n,m,k;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

struct Node{
	int id,dep;
	inline Node(reg int id=0,reg int dep=0):id(id),dep(dep){
		return;
	}
};

bool inque[MAXN][MAXK];
int dis[MAXN][MAXK];
queue<Node> Q;

inline void spfa(reg int s){
	memset(dis,0x3f,sizeof(dis));
	inque[s][0]=true,dis[s][0]=0,Q.push(Node(s,0));
	while(!Q.empty()){
		static Node s;
		s=Q.front();
		Q.pop();
		reg int u=s.id,dep=s.dep;
		inque[u][dep]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep<k&&dis[v][dep+1]>dis[u][dep]+w[i]){
				dis[v][dep+1]=dis[u][dep]+w[i];
				if(!inque[v][dep+1]){
					inque[v][dep+1]=true;
					Q.push(Node(v,dep+1));
				}
			}
		}
	}
	return;
}

int main(void){
	scanf("%d%d%d",&n,&m,&k);
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		Add_Edge(x,y,z);
	}
	spfa(1);
	int ans=0x3f3f3f3f;
	for(reg int i=0;i<=k;++i)
		ans=min(ans,dis[n][i]);
	if(ans==0x3f3f3f3f)
		puts("impossible");
	else
		printf("%d\n",ans);
	return 0;
}