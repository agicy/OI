#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
#define INF 0X3F3F3F3F
#define min(a,b) ( (a) < (b) ? (a) : (b) )

const int MAXN=2000+5;
const int MAXE=(MAXN*(MAXN-1))>>1;

bool inque[MAXN];
int n,m;
int G[MAXN][MAXN];
int dis[MAXN],number[MAXN];
queue<int> Q;

bool SPFA(int);

int main(void){
	register int i;
	memset(G,0X3F,sizeof(G));
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		G[v][u]=G[u][v]=1;
	}
	SPFA(1);
	for(i=1;i<=n;++i)
		printf("%d\n",number[i]);
	return 0;
}

bool SPFA(int s){
	register int i,ID;
	memset(inque,false,sizeof(inque));
	memset(dis,0X3F,sizeof(dis));
	inque[s]=true,dis[s]=0,number[s]=1;
	Q.push(s);
	while(!Q.empty()){
		ID=Q.front();
		Q.pop();
		inque[ID]=false;
		if(ID==n)
			continue;
		for(i=1;i<=n;++i){
			if(i==ID||G[ID][i]==INF)
				continue;
			if(dis[ID]+G[ID][i]==dis[i])
				number[i]+=number[ID];
			if(dis[ID]+G[ID][i]<dis[i]){
				dis[i]=dis[ID]+G[ID][i];
				number[i]=number[ID];
			}
			if(number[i]&&!inque[i]){
				inque[i]=true;
				Q.push(i);
			}
		}
	}
	return true;
}

