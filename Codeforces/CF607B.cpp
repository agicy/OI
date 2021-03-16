#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=500+5;

int n;
int c[MAXN];
int dp[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	memset(dp,0x3f,sizeof(dp));
	for(reg int i=1;i<=n;++i)
		dp[i][i]=1;
	for(reg int i=1;i<n;++i)
		dp[i][i+1]=1+(c[i]!=c[i+1]);
	for(reg int len=3;len<=n;++len)
		for(reg int l=1;l+len-1<=n;++l){
			reg int r=l+len-1;
			if(c[l]==c[r])
				dp[l][r]=dp[l+1][r-1];
			for(reg int k=l;k<r;++k)
				dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
		}
	printf("%d\n",dp[1][n]);
	return 0;
}