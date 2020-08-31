#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool flag;
bool vis[MAXN];
int col[MAXN];

inline void dfs(int u,int c){
	vis[u]=true,col[u]=c;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(!vis[v])
			dfs(v,c^1);
		else if(vis[v]&&col[v]==c)
			flag=true;
	}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])
			dfs(i,0);
	puts(flag?"No":"Yes");
	return 0;
}