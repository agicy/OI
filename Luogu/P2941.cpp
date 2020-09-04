#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int inf=0x3f3f3f3f;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int tarjan_cnt,col[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++tarjan_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=tarjan_cnt;
		}while(v!=u);
	}
	return;
}

int u[MAXN],v[MAXN];
int dis[MAXN][MAXN];

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		scanf("%d%d",&u[i],&v[i]);
		Add_Edge(u[i],v[i]);
		Add_Edge(v[i],u[i]);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	memset(dis,0x3f,sizeof(dis));
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=n;++j){
			static int x;
			scanf("%d",&x);
			if(i!=j)
				dis[col[i]][col[j]]=min(dis[col[i]][col[j]],x);
		}
	}
	int ans=inf;
	for(reg int i=1;i<=tarjan_cnt;++i){
		int sum=0;
		for(reg int j=1;j<=tarjan_cnt;++j)
			if(i!=j)
				sum+=dis[i][j];
		ans=min(ans,sum);
	}
	printf("%d\n",ans<<1);
	return 0;
}