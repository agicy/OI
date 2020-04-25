#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int MAXM=2000+5;

int n,m;
ll a[MAXN][MAXM];
ll sum[MAXN];
ll dp[MAXN][MAXN<<1];

int main(void){
	reg ll ans=1;
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read(),sum[i]=(sum[i]+a[i][j])%MOD;
	for(reg int i=1;i<=n;++i)
		ans=ans*((sum[i]+1)%MOD)%MOD;
	--ans;
	for(reg int i=1;i<=m;++i){
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(reg int j=1;j<=n;++j)
			for(reg int k=0;k<=(n<<1);++k){
				dp[j][k]=(dp[j][k]+dp[j-1][k]*((sum[j]-a[j][i]+MOD)%MOD)%MOD)%MOD;
				dp[j][k+1]=(dp[j][k+1]+dp[j-1][k])%MOD;
				dp[j][k+2]=(dp[j][k+2]+dp[j-1][k]*a[j][i]%MOD)%MOD;
			}
		for(reg int j=n+1;j<=(n<<1);++j)
			ans=(ans+MOD-dp[n][j])%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
