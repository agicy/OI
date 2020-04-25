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

const int MAXN=2000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int a,b;
	inline void Read(void){
		a=read(),b=read();
		return;
	}
	inline bool operator<(const Node& x)const{
		return a+b<x.a+x.b;
	}
};

int n;
Node a[MAXN];
int h;
int dp[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	h=read();
	return;
}

inline void Work(void){
	sort(a+1,a+n+1);
	memset(dp,-0X3F,sizeof(dp));
	dp[0]=0;
	for(reg int i=1;i<=n;++i)
		dp[0]+=a[i].a;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j>=1;--j)
			if(dp[j-1]+a[i].b>=h)
				dp[j]=max(dp[j],dp[j-1]-a[i].a);
	for(reg int i=n;i>=0;--i)
		if(dp[i]>=0){
			printf("%d\n",i);
			break;
		}
	return;
}
