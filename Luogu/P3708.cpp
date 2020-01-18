#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000000+5;

int n;
ll tag[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i)
		for(reg int j=i;j<=n;j+=i)
			tag[j]+=i;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		ans+=n-tag[i]-1;
		printf("%lld%c",ans,i==n?'\n':' ');
	}
	return 0;
}
