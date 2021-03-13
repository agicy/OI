#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg ll d=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return d;
}

inline int inv(reg int a,reg int p){
	ll x,y;
	exgcd(a,p,x,y);
	return (x%p+p)%p;
}

int n,m,p;

int main(void){
	n=read(),m=read(),p=read();
	reg int cnt=0;
	for(reg int x1=0;x1<=n;++x1)
		for(reg int x2=0;x2<=n;++x2)
			for(reg int x3=0;x3<=n;++x3)
	for(reg int y1=0;y1<=m;++y1)
		for(reg int y2=0;y2<=m;++y2)
			for(reg int y3=0;y3<=m;++y3)
				if(1ll*x1*y2+1ll*x2*y3+1ll*x3*y1-1ll*x1*y3-1ll*x2*y1-1ll*x3*y2==2)
					++cnt;
	const int inv3=inv(3,p);
	reg int ans=1ll*cnt*inv3%p;
	printf("%d\n",ans);
	return 0;
}