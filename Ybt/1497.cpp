#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
#define max(a,b) ( (a) > (b) ? (a) : (b) )

const int MAXN=1000+5;
const int MAXM=100000+5;

struct Graph{
	bool inque[MAXN];
	int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
	int dis[MAXN];
	queue<int> Q;
	Graph(void){
		cnt=0;
		memset(head,0,sizeof(head));
		while(!Q.empty())
			Q.pop();
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

int n,m,x;
Graph G1,G2;

int main(void){
	register int i,ans=0;
	scanf("%d%d%d",&n,&m,&x);
	for(i=1;i<=m;++i){
		static int a,b,t;
		scanf("%d%d%d",&a,&b,&t);
		G1.Add_Edge(a,b,t);
		G2.Add_Edge(b,a,t);
	}
	G1.SPFA(x);
	G2.SPFA(x);
	for(i=1;i<=n;++i)
		ans=max(ans,G1.dis[i]+G2.dis[i]);
	printf("%d\n",ans);
	return 0;
}
