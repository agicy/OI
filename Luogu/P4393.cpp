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

const int MAXN=1000000+5;

int n;
ll a[MAXN];

int main(void){
	reg ll ans=0;
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=2;i<=n;++i)
		ans+=max(a[i],a[i-1]);
	printf("%lld\n",ans);
	return 0;
}
