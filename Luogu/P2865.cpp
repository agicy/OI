#include<bits/stdc++.h>
using namespace std;
#define register
typedef long long ll;

const int MAXN=5e3+5;
const int MAXR=1e5+5;

int n,r;
int cnt,head[MAXN],to[MAXR<<1],Next[MAXR<<1];
ll w[MAXR<<1];

inline void Add_Edge(int u,int v,ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXN];
ll dis[MAXN][2];
queue<int> Q;

inline void spfa(int s){
	memset(inque,false,sizeof(inque));
	memset(dis,0x3f,sizeof(dis));
	inque[s]=true,dis[s][0]=0,Q.push(s);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v][0]>dis[u][0]+w[i]){
				dis[v][1]=dis[v][0];
				dis[v][0]=dis[u][0]+w[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
			if(dis[v][1]>dis[u][0]+w[i]&&dis[v][0]<dis[u][0]+w[i]){
				dis[v][1]=dis[u][0]+w[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
			if(dis[v][1]>dis[u][1]+w[i]&&dis[v][0]<dis[u][1]+w[i]){
				dis[v][1]=dis[u][1]+w[i];
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
	scanf("%d%d",&n,&r);
	for(int i=1;i<=r;++i){
		static int a,b,d;
		scanf("%d%d%d",&a,&b,&d);
		Add_Edge(a,b,d);
		Add_Edge(b,a,d);
	}
	spfa(1);
	printf("%lld\n",dis[n][1]);
	return 0;
}