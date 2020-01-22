#include<cstdio>
#include<algorithm>
using std::max;
#include<queue>
using std::queue;

const int MAXN=1000000+5;
const int MAXT=20+1;

bool vis[MAXN];
int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int dis[MAXN],f[MAXN];
queue<int> Q;

void Add_Edge(int,int,int);
void dp(int);

int main(void){
	register int i;
	scanf("%d",&n);
	for(i=1;i<n;++i){
		static int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		Add_Edge(u,v,d);
		Add_Edge(v,u,d);
	}
	dp(1);
	for(i=1;i<=n;++i)
		printf("%d\n",f[i]);
	return 0;
}

void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}
void dp(int ID){
	register int i;
	vis[ID]=true;
	for(i=head[ID];i;i=Next[i]){
		if(!vis[to[i]]){
			dp(to[i]);
			f[ID]=max(f[ID],dis[ID]+dis[to[i]]+w[i]);
			dis[ID]=max(dis[ID],dis[to[i]]+w[i]);
		}
	}
	return;
}
