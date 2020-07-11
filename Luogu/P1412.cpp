#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,k,c,w;
int type[MAXN],a[MAXN];

inline void Read(void){
	n=read(),k=read(),c=read(),w=read();
	for(reg int i=1;i<=n;++i)
		type[i]=read(),a[i]=read();
	return;
}

double dp[MAXN];

inline void Work(void){
	for(reg int i=n;i>=1;--i)
		if(type[i]==1)
			dp[i]=max(dp[i+1],a[i]+dp[i+1]*(1-0.01*k));
		else
			dp[i]=max(dp[i+1],-a[i]+dp[i+1]*(1+0.01*c));
	printf("%.2lf\n",dp[1]*w);
	return;
}
