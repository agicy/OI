#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=20+5;
const int MAXM=20+5;

int n,m;
ll k,a[MAXN][MAXM];
map<ll,ll> M[MAXN][MAXM];

inline void dfs1(reg int x,reg int y,ll sum){
	if(x>n||y>m)
		return;
	if(x+y==(n+m)/2+1){
		++M[x][y][sum];
		return;
	}
	dfs1(x+1,y,a[x+1][y]^sum),dfs1(x,y+1,a[x][y+1]^sum);
	return;
}

ll ans;

inline void dfs2(reg int x,reg int y,reg ll sum){
	if(x<1||y<1)
		return;
	if(x+y==(n+m)/2+1){
		ans+=M[x][y][sum^k^a[x][y]];
		return;
	}
	dfs2(x-1,y,a[x-1][y]^sum),dfs2(x,y-1,a[x][y-1]^sum);
	return;
}

int main(void){
	scanf("%d%d%lld",&n,&m,&k);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			scanf("%lld",&a[i][j]);
	dfs1(1,1,a[1][1]),dfs2(n,m,a[n][m]);
	printf("%lld\n",ans);
	return 0;
}