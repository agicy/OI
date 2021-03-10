#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool dp=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))dp|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return dp?-res:res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int MAXK=100+5;
const int inf=0x3f3f3f3f;

int n,m,k;
char a[MAXN],b[MAXM];
int dp[2][MAXK<<1];

int main(void){
	n=read(),m=read(),k=read();
	if(abs(n-m)>k)
		puts("-1");
	else{
		read(a+1),read(b+1);
		fill(dp[0],dp[0]+(k<<1)+1,inf);
		dp[0][k]=0;
		for(reg int i=1;i<=n;++i){
			fill(dp[i&1],dp[i&1]+(k<<1)+1,inf);
			for(reg int j=max(k-i,0);j<=min(k+m-i,k<<1);++j){
				if(a[i]==b[i+j-k])
					dp[i&1][j]=min(dp[i&1][j],dp[(i-1)&1][j]);
				if(j>0)
					dp[i&1][j]=min(dp[i&1][j],dp[i&1][j-1]+1);
				if(j<(k<<1))
					dp[i&1][j]=min(dp[i&1][j],dp[(i-1)&1][j+1]+1);
			}
		}
		printf("%d\n",dp[n&1][k+m-n]>k?-1:dp[n&1][k+m-n]);
	}
	return 0;
}