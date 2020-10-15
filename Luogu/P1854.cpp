#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXF=100+5;
const int MAXV=100+5;

int f,v;
int a[MAXF][MAXV];
int dp[MAXF][MAXV],from[MAXF][MAXV];

int main(void){
	f=read(),v=read();
	for(reg int i=1;i<=f;++i)
		for(reg int j=1;j<=v;++j)
			a[i][j]=read();
	memset(dp,-0x3f,sizeof(dp));
	for(reg int i=1;i<=v-f+1;++i)
		dp[1][i]=a[1][i];
	for(reg int i=2;i<=f;++i)
		for(reg int j=i;j<=v-f+i;++j)
			for(reg int k=1;k<j;++k)
				if(dp[i][j]<dp[i-1][k]+a[i][j]){
					dp[i][j]=dp[i-1][k]+a[i][j];
					from[i][j]=k;
				}
	reg int ans=0,pos=-1;
	for(reg int i=f;i<=v;++i)
		if(dp[f][i]>ans){
			ans=dp[f][i];
			pos=i;
		}
	printf("%d\n",ans);
	static int S[MAXF];
	for(reg int i=f;i>=1;--i){
		S[i]=pos;
		pos=from[i][pos];
	}
	for(reg int i=1;i<=f;++i)
		printf("%d%c",S[i],i==f?'\n':' ');
	return 0;
}