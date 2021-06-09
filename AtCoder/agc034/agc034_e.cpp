#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e3+5;
const int inf=0x3f3f3f3f;

int n;
char s[MAXN];
int a[MAXN];
vector<int> G[MAXN];
int f[MAXN],sum[MAXN];

inline void dfs1(reg int u,reg int father){
	sum[u]=a[u];
	f[u]=0;
	for(int v:G[u])
		if(v!=father){
			dfs1(v,u);
			sum[u]+=sum[v];
			f[u]+=f[v]+sum[v];
		}
	return;
}

inline int dfs2(reg int u,reg int father){
	reg int Max=0;
	for(int v:G[u])
		if(v!=father)
			if(!Max||f[v]>f[Max])
				Max=v;
	if(!Max)
		return 0;
	reg int k=dfs2(Max,u)+sum[Max];
	if(f[u]-(f[Max]+sum[Max])>=k)
		return f[u]&1;
	else
		return k-(f[u]-(f[Max]+sum[Max]));
}

int main(void){
	scanf("%d%s",&n,s+1);
	for(reg int i=1;i<=n;++i)
		a[i]=s[i]^'0';
	for(reg int i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	reg int ans=inf;
	for(reg int i=1;i<=n;++i){
		dfs1(i,0);
		if(!dfs2(i,0))
			ans=min(ans,f[i]>>1);
	}
	printf("%d\n",ans==inf?-1:ans);
	return 0;
}