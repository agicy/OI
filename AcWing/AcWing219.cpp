#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=200+5;
const int MAXM=200+5;
const int MAXS=200+5;

int sg[MAXN][MAXM];

inline int dfs(reg int n,reg int m){
	if(sg[n][m]!=-1)
		return sg[n][m];
	bool vis[MAXS];
	memset(vis,0,sizeof(vis));
	for(reg int i=2;i<=n-i;++i)
		vis[dfs(i,m)^dfs(n-i,m)]=true;
	for(reg int i=2;i<=m-i;++i)
		vis[dfs(n,i)^dfs(n,m-i)]=true;
	sg[n][m]=0;
	while(vis[sg[n][m]])
		++sg[n][m];
	return sg[m][n]=sg[n][m];
}

int main(void){
	memset(sg,-1,sizeof(sg));
	sg[2][3]=sg[3][2]=sg[2][2]=0;
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
		puts(dfs(n,m)>0?"WIN":"LOSE");
	return 0;
}