#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
typedef long long ll;

const int MAXN=1000000+5;
const int MAXM=1000000+5;

struct Graph{
	bool inque[MAXN];
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	ll w[MAXM],dis[MAXN];
	queue<int> Q;

	Graph(void){
		cnt=0;
		return;
	}
	void Add_Edge(int u,int v,int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	bool SPFA(int s){
		register int i,ID;
		memset(inque,false,sizeof(inque));
		memset(dis,0X3F,sizeof(dis));
		inque[s]=true,dis[s]=0;
		Q.push(s);
		while(!Q.empty()){
			ID=Q.front();
			Q.pop();
			inque[ID]=false;
			for(i=head[ID];i;i=Next[i]){
				if(dis[ID]+w[i]<dis[to[i]]){
					dis[to[i]]=dis[ID]+w[i];
					if(!inque[to[i]]){
						inque[to[i]]=true;
						Q.push(to[i]);
					}
				}
			}
		}
		return true;
	}
};

int n,m;
Graph G,ReG;

int main(void){
	register int i;
	register ll ans=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i){
		static int u,v;
		static ll w;
		scanf("%d%d%lld",&u,&v,&w);
		G.Add_Edge(u,v,w);
		ReG.Add_Edge(v,u,w);
	}
	G.SPFA(1);
	ReG.SPFA(1);
	for(i=1;i<=n;++i)
		ans+=G.dis[i]+ReG.dis[i];
	printf("%lld\n",ans);
	return 0;
}

