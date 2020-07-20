#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

int n;
ll a[MAXN],b[MAXN];

inline int log2(reg ll x){
	reg int res=0;
	while((1ll<<res)<=x)
		++res;
	return res;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		int ans=0;
		b[1]=0;
		for(reg int i=2;i<=n;++i){
			b[i]=max(0ll,a[i-1]+b[i-1]-a[i]);
			ans=max(ans,log2(b[i]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
