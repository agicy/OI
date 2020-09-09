#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=5e4+5;
const int inf=0x3f3f3f3f;

int n;
int cnt,head[MAXN],to[MAXN*3],w[MAXN*3],Next[MAXN*3];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXN];
int dis[MAXN];
queue<int> Q;

inline void spfa(reg int s){
	memset(dis,-0x3f,sizeof(dis));
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]<dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return;
}

int main(void){
	scanf("%d",&n);
	int Max=-inf,Min=inf;
	for(reg int i=1;i<=n;++i){
		static int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		++a,++b;
		Add_Edge(a-1,b,c);
		Max=max(Max,b),Min=min(Min,a-1);
	}
	for(reg int i=Min;i<=Max;++i){
		Add_Edge(i,i+1,0);
		Add_Edge(i+1,i,-1);
	}
	spfa(Min);
	printf("%d\n",dis[Max]);
	return 0;
}