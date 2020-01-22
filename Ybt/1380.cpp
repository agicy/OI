#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
#define max(a,b) ( (a) > (b) ? (a) : (b) )

const int MAXN=100000+5;
const int MAXM=100000*20;

bool inque[MAXN];
int n,p,c,m;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];
int dis[MAXN];
queue<int> Q;

void Add_Edge(int,int,int);
bool SPFA(int);

int main(void){
	register int i,ans=0;
	scanf("%d%d%d%d",&n,&p,&c,&m);
	for(i=1;i<=p;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v,1);
		Add_Edge(v,u,1);
	}
	SPFA(c);
	for(i=1;i<=n;++i)
		ans=max(ans,dis[i]+m+1);
	printf("%d\n",ans);
	return 0;
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
