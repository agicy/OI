#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=2e5+5;

int t,n,m;
int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXM<<1];
int tot,ans[MAXM];

inline void dfs(int u){
	for(int &i=head[u];i;){
		if(vis[i]){
			i=Next[i];
			continue;
		}
		vis[i]=true;
		if(t==1)
			vis[i^1]=true;
		int v=to[i],id=w[i];
		i=Next[i];
		dfs(v);
		ans[++tot]=id;
	}
	return;
}

int inDeg[MAXN],outDeg[MAXN];

int main(void){
	scanf("%d%d%d",&t,&n,&m);
	for(int i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		++inDeg[y],++outDeg[x];
		Add_Edge(x,y,i);
		if(t==1)
			Add_Edge(y,x,-i);
	}
	if(t==1){
		for(int i=1;i<=n;++i)
			if((inDeg[i]+outDeg[i])&1){
				puts("NO");
				return 0;
			}
	}
	else
		for(int i=1;i<=n;++i)
			if(inDeg[i]!=outDeg[i]){
				puts("NO");
				return 0;
			}
	for(int i=1;i<=n;++i)
		if(head[i]){
			dfs(i);
			break;
		}
	if(tot<m){
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=tot;i>=1;--i)
		printf("%d%c",ans[i],i==1?'\n':' ');
	return 0;
}
