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

const int MAXN=100+5;
const int MAXLOG2N=20+1;
const int MAXW=40000+5;

int n,W;
int v[MAXN*MAXLOG2N],w[MAXN*MAXLOG2N],cnt[MAXN*MAXLOG2N];
int dp[MAXW];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),W=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read(),w[i]=read(),cnt[i]=read();
	return;
}

inline void Work(void){
	reg int tot=n;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=cnt[i];j<<=1){
			cnt[i]-=j;
			v[++tot]=v[i]*j;
			w[tot]=w[i]*j;
		}
		if(cnt[i]){
			v[++tot]=v[i]*cnt[i];
			w[tot]=w[i]*cnt[i];
		}
	}
	for(reg int i=n+1;i<=tot;++i)
		for(reg int j=W;j>=w[i];--j)
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
	printf("%d\n",dp[W]);
	return;
}