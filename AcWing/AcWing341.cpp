#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=5e5+5;

int n,m;
int val[MAXN];

struct Graph{
	int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	bool inque[MAXN];
	int dis[MAXN];
	queue<int> Q;
	inline void spfa1(reg int s){
		memset(dis,0x3f,sizeof(dis));
		inque[s]=true,dis[s]=val[s],Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]>min(dis[u],val[v])){
					dis[v]=min(dis[u],val[v]);
					if(!inque[v]){
						inque[v]=true;
						Q.push(v);
					}
				}
			}
		}
		return;
	}
	inline void spfa2(reg int s){
		memset(dis,-0x3f,sizeof(dis));
		inque[s]=true,dis[s]=val[s],Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dis[v]<max(dis[u],val[v])){
					dis[v]=max(dis[u],val[v]);
					if(!inque[v]){
						inque[v]=true;
						Q.push(v);
					}
				}
			}
		}
		return;
	}
};

Graph G1,G2;

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&val[i]);
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		G1.Add_Edge(x,y);
		G2.Add_Edge(y,x);
		if(z==2){
			G1.Add_Edge(y,x);
			G2.Add_Edge(x,y);
		}
	}
	G1.spfa1(1),G2.spfa2(n);
	int ans=0;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,G2.dis[i]-G1.dis[i]);
	printf("%d\n",ans);
	return 0;
}