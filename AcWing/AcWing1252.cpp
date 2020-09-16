#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e4+5;

int n,m,w;
int c[MAXN],d[MAXN];
int fa[MAXN],dp[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void merge(reg int a,reg int b){
	reg int ra=find(a),rb=find(b);
	if(ra!=rb){
		fa[rb]=ra;
		c[ra]+=c[rb];
		d[ra]+=d[rb];
	}
	return;
}

int main(void){
	cin>>n>>m>>w;
	for(reg int i=1;i<=n;++i)
		cin>>c[i]>>d[i];
	for(reg int i=1;i<=n;++i)
		fa[i]=i;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		cin>>u>>v;
		merge(u,v);
	}
	for(reg int i=1;i<=n;++i)
		find(i);
	for(reg int i=1;i<=n;++i)
		if(i==fa[i])
			for(reg int j=w;j>=c[i];--j)
				dp[j]=max(dp[j],dp[j-c[i]]+d[i]);
	printf("%d\n",dp[w]);
	return 0;
}