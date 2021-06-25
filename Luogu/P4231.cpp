#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e7+5;

int n,m;
ll a[MAXN];

int main(void){
	n=read(),m=read();
	while(m--){
		static int l,r;
		static ll s,t;
		l=read(),r=read(),s=readll(),t=readll();
		reg ll d=(t-s)/(r-l);
		a[l]+=s,a[l+1]+=d-s;
		a[r+1]+=-d-t,a[r+2]+=t;
	}
	for(reg int i=1;i<=n;++i)
		a[i]+=a[i-1];
	for(reg int i=1;i<=n;++i)
		a[i]+=a[i-1];
	reg ll ans1=0,ans2=0;
	for(reg int i=1;i<=n;++i)
		ans1^=a[i],ans2=max(ans2,a[i]);
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}