#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
#include<queue>
using std::queue;
#define INF 0X3F3F3F3F

const int MAXN=50000+5;

bool inque[MAXN];
int n;
int cnt,head[MAXN],to[MAXN*3],w[MAXN*3],Next[MAXN*3];
int dis[MAXN];
queue<int> Q;

void Add_Edge(int,int,int);
bool SPFA(int);

int main(void){
	register int i,Min=INF,Max=0;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		++a,++b;
		Add_Edge(a-1,b,c);
		Min=min((int)Min,a-1);
		Max=max((int)Max,b);
	}
	for(i=Min;i<=Max;++i){
		Add_Edge(i,i+1,0);
		Add_Edge(i+1,i,-1);
	}
	SPFA(Min);
	printf("%d\n",dis[Max]);
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
	memset(dis,-0X3F,sizeof(dis));
	while(!Q.empty())
		Q.pop();
	inque[s]=true,dis[s]=0;
	Q.push(s);
	while(!Q.empty()){
		ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(i=head[ID];i;i=Next[i]){
			if(dis[ID]+w[i]>dis[to[i]]){
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
