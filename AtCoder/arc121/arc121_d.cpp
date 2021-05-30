#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=5e3+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n;
int a[MAXN<<1];
int pos;

inline ll getVal(reg int add){
	reg int tot=0;
	static int tmp[MAXN<<1];
	for(reg int i=1;i<=pos;++i)
		tmp[++tot]=a[i];
	for(reg int i=1;i<=add;++i)
		tmp[++tot]=0;
	for(reg int i=pos+1;i<=n;++i)
		tmp[++tot]=a[i];
	reg ll Max=-inf,Min=inf;
	for(reg int i=1;i<=(tot>>1);++i)
		Max=max(Max,0ll+tmp[i]+tmp[tot-i+1]),Min=min(Min,0ll+tmp[i]+tmp[tot-i+1]);
	return Max-Min;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	for(reg int i=n;i>=1;--i)
		if(a[i]<=0){
			pos=i;
			break;
		}
	reg ll ans=inf;
	for(reg int i=(n&1);i<=n;i+=2)
		ans=min(ans,getVal(i));
	printf("%lld\n",ans);
	return 0;
}