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

const int MAXN=100+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
ll a[MAXN];
ll sum,s[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),sum+=a[i];
	return;
}

inline void Work(void){
	sum/=n;
	for(reg int i=1;i<=n;++i)
		s[i]=s[i-1]+a[i]-sum;
	sort(s+1,s+n+1);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=abs(s[(n+1)>>1]-s[i]);
	printf("%lld\n",ans);
	return;
}
