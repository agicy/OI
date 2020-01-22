#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
using std::queue;
#define INF 1e9
#define max(a,b) ( (a) > (b) ? (a) : (b) )

const int MAXN=200+5;
const int MAXM=(MAXN*(MAXN-1))>>1;

bool flag,inque[MAXN],cut[MAXN][MAXN];
int n,m,p,q;
int x[MAXN],y[MAXN];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
int road[MAXN];
double w[MAXM<<1],dis[MAXN];
queue<int> Q;

void Add_Edge(int,int,double);
bool SPFA(int);
double len(int,int);

int main(void){
	register int i;
	register double ans;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		scanf("%d%d",&x[i],&y[i]);
	for(i=1;i<=m;++i){
		scanf("%d%d",&p,&q);
		Add_Edge(p,q,len(p,q));
		Add_Edge(q,p,len(q,p));
	}
	SPFA(1);
	flag=true,ans=dis[n];
	for(i=n;i!=1;i=road[i]){
		cut[i][road[i]]=cut[road[i]][i]=true;
		SPFA(1);
		cut[i][road[i]]=cut[road[i]][i]=false;
		ans=max(ans,dis[n]);
	}
	if(ans==INF)
		puts("-1");
	else
		printf("%.2f\n",ans);
	return 0;
}

void Add_Edge(int u,int v,double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool SPFA(int s){
	register int i,ID;
	memset(inque,false,sizeof(inque));
	for(i=1;i<=n;++i)
		dis[i]=INF;
	inque[s]=true,dis[s]=0;
	Q.push(s);
	while(!Q.empty()){
		ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(i=head[ID];i;i=Next[i]){
			if(!cut[ID][to[i]]&&dis[ID]+w[i]<dis[to[i]]){
				if(!flag)
					road[to[i]]=ID;
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

double len(int p,int q){
	return sqrt((x[p]-x[q])*(x[p]-x[q])+(y[p]-y[q])*(y[p]-y[q]));
}

