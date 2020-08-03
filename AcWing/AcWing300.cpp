#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=5000+5;

int n,s;
int t[MAXN],f[MAXN];
int sumt[MAXN],sumf[MAXN];
int dp[MAXN];

int main(void){
	n=read(),s=read();
	for(reg int i=1;i<=n;++i){
		t[i]=read(),f[i]=read();
		sumt[i]=sumt[i-1]+t[i];
		sumf[i]=sumf[i-1]+f[i];
	}
	memset(dp,0X3F,sizeof(dp));
	dp[0]=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=i;++j)
			dp[i]=min(dp[i],dp[j-1]+s*(sumf[n]-sumf[j-1])+sumt[i]*(sumf[i]-sumf[j-1]));
	printf("%d\n",dp[n]);
	return 0;
}