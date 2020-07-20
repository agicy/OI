#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=300+5;

int n;
int a[MAXN],sum[MAXN];
int dp[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	memset(dp,0X3F,sizeof(dp));
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i],dp[i][i]=0;
	for(reg int len=2;len<=n;++len)
		for(reg int l=1;l<=n-len+1;++l){
			reg int r=l+len-1;
			for(reg int i=l;i<r;++i)
				dp[l][r]=min(dp[l][r],dp[l][i]+dp[i+1][r]);
			dp[l][r]+=sum[r]-sum[l-1];
		}
	printf("%d\n",dp[1][n]);
	return 0;
}
