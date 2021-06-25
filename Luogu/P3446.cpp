#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e3+5;
const int inf=2e9;

int n,m;
int a[MAXN];
int sum[MAXN];
int Min[MAXN];
int pre[MAXN][MAXN],suf[MAXN][MAXN];
int dp[MAXN][MAXN];

int main(void){
	m=read(),n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i]+1;
	}
	for(reg int i=0;i<=n;++i)
		Min[i]=i;
	for(reg int i=2;i<=n;++i){
		dp[0][i]=(sum[i]-1>m)?inf:0;
	 	for(reg int j=1;dp[j][i]=inf,j<i;++j)
			if(sum[i]-sum[j]-1<=m){
				reg int bas=sum[i]-(sum[j]<<1);
				reg int k=Min[j];
				while(k&&bas+sum[k-1]>=0)
					--k;
				Min[j]=k;
				if(k<j)
					dp[j][i]=suf[k][j]+bas;
				if(k)
					dp[j][i]=min(dp[j][i],pre[k-1][j]-bas);
			}
		suf[i][i]=inf;
		for(reg int j=i-1;j>=0;--j)
			suf[j][i]=min(suf[j+1][i],dp[j][i]+sum[j]);
		for(reg int j=1;j<i;++j)
			pre[j][i]=min(pre[j-1][i],dp[j][i]-sum[j]);
	}
	reg int ans=dp[0][n];
	for(reg int j=1;j<n;++j)
		ans=min(ans,dp[j][n]);
	printf("%d\n",ans);
	return 0;
}