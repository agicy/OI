#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;
const int MAXK=2e3+5;

int n,m,k;
int cnt,head[MAXN],to[MAXK],Next[MAXK];
int mat[MAXN];
bool vis[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			vis[v]=true;
			if(!mat[v]||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	while(scanf("%d",&n)!=EOF&&n!=0){
		cnt=0,memset(head,0,sizeof(head));
		memset(mat,0,sizeof(mat));
		scanf("%d%d",&m,&k);
		for(reg int i=1;i<=k;++i){
			static int u,v;
			scanf("%*d%d%d",&u,&v);
			if(u&&v)
				Add_Edge(u,v);
		}
		reg int ans=0;
		for(reg int i=1;i<n;++i){
			memset(vis,false,sizeof(vis));
			if(dfs(i))
				++ans;
		}
		printf("%d\n",ans);
	}
	return 0;
}