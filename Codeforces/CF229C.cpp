#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000000+5;

int n,m;
int deg[MAXN];
ll ans;

int main(void){
	n=read(),m=read();
	reg ll ans=1ll*n*(n-1)/2*(n-2)/3;
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		++deg[a],++deg[b];
	}
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		sum=(sum+1ll*deg[i]*(n-1-deg[i]));
	printf("%lld\n",ans-(sum>>1));
	return 0;
}