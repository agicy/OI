#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e3+5;
const int MAXE=3e4+5;

int n,ml,md;
int cnt,head[MAXN],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
bool inque[MAXN];
int dis[MAXN];
int dep[MAXN];
queue<int> Q;

inline int spfa(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,Q.push(s);
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		inque[u]=false,vis[u]=true;
		for(int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				dep[v]=dep[u]+1;
				if(dep[v]>n)
					return -1;
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return dis[n]==dis[0]?-2:dis[n];
}

int main(void){
	scanf("%d%d%d",&n,&ml,&md);
	for(int i=1;i<n;++i)
		Add_Edge(i+1,i,0);
	for(int i=1;i<=ml;++i){
		static int a,b,l;
		scanf("%d%d%d",&a,&b,&l);
		Add_Edge(a,b,l);
	}
	for(int i=1;i<=md;++i){
		static int a,b,d;
		scanf("%d%d%d",&a,&b,&d);
		Add_Edge(b,a,-d);
	}
	bool flag=false;
	int ans=0;
	for(int i=1;i<=n;++i)
		if(!vis[i]){
			ans=spfa(i);
			if(flag)
				ans=(ans==-1)?-1:-2;
				if(ans!=-2)
					break;
				else
					flag=true;
		}
	printf("%d\n",ans);
	return 0;
}