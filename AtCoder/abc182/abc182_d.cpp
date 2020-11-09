#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

int n;
int a[MAXN];
ll sum[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	ll ans=0,pos=0,Max=-inf;
	for(reg int i=1;i<=n;++i){
		Max=max(Max,sum[i]);
		ans=max(ans,pos+Max);
		pos+=sum[i];
	}
	printf("%lld\n",ans);
	return 0;
}