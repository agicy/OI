#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define eps 1e-10

const int MAXN=2000+100;

int n,a,b;
double P[MAXN],Q[MAXN];
int cnt=1,head[MAXN],to[(MAXN*5)<<1],w[(MAXN*5)<<1],Next[(MAXN*5)<<1];
double p[(MAXN*5)<<1];

inline void Add_Edge(reg int u,reg int v,reg int len,reg double val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg double val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXN];
double dis[MAXN];

inline bool SPFA(int s,reg int t){
	queue<int> Q;
	memset(inque,false,sizeof(inque));
	fill(dis+s,dis+t+1,-1e20);
	while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i])
			if(w[i]&&dis[to[i]]+eps<dis[ID]+p[i]){
				dis[to[i]]=dis[ID]+p[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
	}
	return dis[t]>eps;
}

double Cost;
bool vis[MAXN];
int cur[MAXN];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		Cost+=lim*dis[t];
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(w[i]&&fabs(dis[to[i]]-(dis[ID]+p[i]))<eps&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	vis[ID]=false;
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

int main(void){
	scanf("%d%d%d",&n,&a,&b);
	for(reg int i=1;i<=n;++i)
		scanf("%lf",&P[i]);
	for(reg int i=1;i<=n;++i)
		scanf("%lf",&Q[i]);
	reg int s=0,A=n+1,B=n+2,t=n+3;
	Add_Tube(s,A,a,0);
	Add_Tube(s,B,b,0);
	for(reg int i=1;i<=n;++i){
		Add_Tube(A,i,1,P[i]);
		Add_Tube(B,i,1,Q[i]);
		Add_Tube(i,t,1,0);
		Add_Tube(i,t,1,-P[i]*Q[i]);
	}
	Dinic(s,t);
	printf("%.10lf\n",Cost);
	return 0;
}