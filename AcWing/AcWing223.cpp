#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=10+5;

int n;
int a[MAXN],m[MAXN];

inline ll exgcd(reg ll a,reg ll b,reg ll& x,reg ll& y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

inline ll CRT(void){
	reg ll ans=0,M=1;
	for(reg int i=1;i<=n;++i)
		M*=m[i];
	for(reg int i=1;i<=n;++i){
		reg ll Mi=M/m[i];
		ll t1,t2;
		exgcd(Mi,m[i],t1,t2);
		ans=(ans+a[i]*Mi%M*t1)%M;
	}
	return (ans+M)%M;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d%d",&m[i],&a[i]);
	printf("%lld\n",CRT());
	return 0;
}