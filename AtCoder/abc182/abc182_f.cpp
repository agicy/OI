#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}
inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=50+5;

int n;
ll x;
ll a[MAXN];
map<ll,ll> f,g;

int main(void){
	n=read(),x=readll();
	for(reg int i=1;i<=n;++i)
		a[n-i+1]=readll();
	ll x0=x/a[1]*a[1];
	f[x0]=1;
	if(x0!=x)
		f[x0+a[1]]=1;
	for(reg int i=2;i<=n;++i){
		g.clear();
		reg ll Max=a[i-1]/a[i];
		for(auto it:f){
			reg ll d=x-it.first,m=d/a[i];
			ll y=it.first+m*a[i];
			if(abs(m)<Max)
				g[y]+=it.second;
			if(y!=x&&abs(m)+1<Max)
				g[y+a[i]*(d/abs(d))]+=it.second;
		}
		swap(f,g);
	}
	printf("%lld\n",f[x]);
	return 0;
}