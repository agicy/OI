#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=50000+5;

bool opt[MAXN];
int n,V;
int w[MAXN],v[MAXN];
int ans[MAXN],f[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID,reg int dp[]){
	int f[MAXN];
	for(reg int i=0;i<=V;++i)
		f[i]=dp[i];
	if(opt[ID])
		for(reg int i=w[ID];i<=V;++i)
			f[i]=max(f[i],f[i-w[ID]]+v[ID]);
	ans[ID]=f[V];
	for(reg int i=head[ID];i;i=Next[i])
		DFS(to[i],f);
	return;
}

int main(void){
	scanf("%d%d",&n,&V);
	stack<int> S;
	S.push(0);
	for(reg int i=1;i<=n;++i){
		static char str[128];
		scanf("%s",str);
		if(str[0]=='a'){
			opt[i]=true;
			scanf("%d%d",&w[i],&v[i]);
			Add_Edge(S.top(),i);
			S.push((int)i);
		}
		else if(str[0]=='e')
			S.pop(),Add_Edge(S.top(),i);
	}
	DFS(0,f);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}
