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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=800+1;
const int MAXM=800+1;
const int MAXK=15+2;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int n,m,k;
int a[MAXN][MAXM];
int dp[MAXN][MAXM][MAXK][2];

int main(void){
	n=read(),m=read(),k=read()+1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			a[i][j]=read()%k;
			dp[i][j][a[i][j]][0]=1;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			for(reg int h=0;h<=k;++h){
				dp[i][j][h][0]=add(dp[i][j][h][0],add(dp[i-1][j][(h-a[i][j]+k)%k][1],dp[i][j-1][(h-a[i][j]+k)%k][1]));
				dp[i][j][h][1]=add(dp[i][j][h][1],add(dp[i-1][j][(h+a[i][j])%k][0],dp[i][j-1][(h+a[i][j])%k][0]));
			}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			ans=add(ans,dp[i][j][0][1]);
	printf("%d\n",ans);
	return 0;
}