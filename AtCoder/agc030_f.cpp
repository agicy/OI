#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=300+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n;
int a[MAXN<<1],b[MAXN<<1];
int dp[MAXN<<1][MAXN][MAXN];
bool vis[MAXN<<1],used[MAXN<<1];

int main(void){
	n=read();
	reg int cnt1=0,cnt2=0;
	for(reg int i=1;i<=(n<<1);++i)
		a[i]=read();
	for(reg int i=1;i<=n<<1;i+=2)
		if(a[i]>0&&a[i+1]>0)
			vis[a[i]]=vis[a[i+1]]=true;
		else if(a[i]<0&&a[i+1]<0)
			++cnt1;
		else
			++cnt2,used[max(a[i],a[i+1])]=true;
	reg int tot=0;
	for(reg int i=(n<<1);i>=1;--i)
		if(!vis[i])
			b[++tot]=i;
	dp[0][0][0]=1;
	for(reg int i=1;i<=tot;++i)
		for(reg int j=0;j<=cnt1+cnt2;++j)
			for(reg int k=0;k<=cnt2;++k){
				if(!used[b[i]]){
					dp[i][j+1][k]=add(dp[i][j+1][k],dp[i-1][j][k]);
					if(j>0)
						dp[i][j-1][k]=add(dp[i][j-1][k],dp[i-1][j][k]);
					if(k>0)
						dp[i][j][k-1]=add(dp[i][j][k-1],1ll*k*dp[i-1][j][k]%mod);
				}
				else{
					dp[i][j][k+1]=add(dp[i][j][k+1],dp[i-1][j][k]);
					if(j>0)
						dp[i][j-1][k]=add(dp[i][j-1][k],dp[i-1][j][k]);
				}
			}
	reg int ans=dp[tot][0][0];
	for(reg int i=1;i<=cnt1;++i)
		ans=1ll*ans*i%mod;
	printf("%d\n",ans);
	return 0;
}