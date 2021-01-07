#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=50+5;
const int MAXA=1e5+5;

int n;
int a[MAXN];
int dp[MAXA];

int main(void){
	n=read();
	int Max=0;
	memset(dp,0x3f,sizeof(dp));
	dp[1]=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		Max=max(Max,a[i]);
		dp[1]+=a[i];
	}
	int ans=dp[1];
	for(reg int i=1;i<=Max/2;++i){
		for(reg int j=2;j*i<=Max;++j){
			reg int sum=0;
			for(reg int k=1;k<=n;++k)
				sum+=a[k]/(i*j);
			dp[i*j]=min(dp[i*j],dp[i]-(j-1)*sum);
			ans=min(ans,dp[i*j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}