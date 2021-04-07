#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline double max(reg double a,reg double b){
	return a>b?a:b;
}

const int MAXN=100+5;
const double inf=1e100;
const double eps=1e-10;

int n,m,v0;
double w[MAXN];
double p;
double dp[2][MAXN][MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=0;i<n;++i)
		scanf("%lf",&w[i]);
	scanf("%d",&v0);
	--v0;
	scanf("%lf",&p);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			dp[0][i][j]=(i==j)?0:-inf;
	for(reg int i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		--x,--y;
		dp[0][x][y]=p*w[y];
	}
	reg int ptr=1;
	while(true){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				dp[ptr][i][j]=-inf;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<n;++k){
				reg double r=dp[ptr^1][i][k];
				for(reg int j=0;j<n;++j)
					dp[ptr][i][j]=max(dp[ptr][i][j],r+p*dp[ptr^1][k][j]);
			}
		if(p<eps)
			break;
		ptr^=1,p=p*p;
	}
	reg double ans=-inf;
	for(reg int i=0;i<n;++i)
		ans=max(ans,dp[ptr][v0][i]);
	printf("%.1lf\n",ans+w[v0]);
	return 0;
}