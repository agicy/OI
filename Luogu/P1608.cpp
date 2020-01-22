#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
#define INF 0X3F3F3F3F

const int MAXN=2000+5;
const int MAXE=(MAXN*(MAXN-1))>>1;

int n,e;
int cnt,head[MAXN],to[MAXE<<1],w[MAXE<<1],Next[MAXE<<1];
int dis[MAXN],inDeg[MAXN],number[MAXN];
queue<int> Q;

void Add_Edge(int,int,int);
void Topo(int);

int main(void){
	register int i;
	scanf("%d%d",&n,&e);
	for(i=1;i<=e;++i){
		static int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		++inDeg[v];
		Add_Edge(u,v,w);
	}
	Topo(1);
	if(dis[n]!=INF)
		printf("%d %d\n",dis[n],number[n]);
	else
		puts("No answer");
	return 0;
}

void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

void Topo(int s){
	register int i,ID;
	memset(dis,0X3F,sizeof(dis));
	dis[s]=0,number[s]=1;
	Q.push(s);
	while(!Q.empty()){
		ID=Q.front();
		Q.pop();
		for(i=head[ID];i;i=Next[i]){
			if(dis[ID]+w[i]<dis[to[i]]){
				dis[to[i]]=dis[ID]+w[i];
				number[to[i]]=number[ID];
			}
			else if(dis[ID]+w[i]==dis[to[i]])
				number[to[i]]+=number[ID];
			--inDeg[to[i]];
			if(!inDeg[to[i]])
				Q.push(to[i]);
		}
	}
	return;
}

