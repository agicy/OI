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

const int MAXN=1000+5;

int n;
ll ans,phi[MAXN];
ll sum[MAXN];

inline void Euler(reg int);

int main(void){
	Euler(1000);
	int C=read();
	reg int cnt=0;
	while(C--){
		n=read();
		reg ll ans=0;
		for(reg int i=2;i<=n;++i)
			ans+=(phi[i]<<1);
		printf("%d %d %lld\n",++cnt,n,n==0?0:ans+3);
	}
	return 0;
}

inline void Euler(reg int n){
	for(reg int i=1;i<=n;++i)
		phi[i]=i;
	for(reg int i=2;i<=n;++i)
		if(phi[i]==i)
			for(reg int j=i;j<=n;j+=i)
				phi[j]/=i,phi[j]*=(i-1);
	return;
}
