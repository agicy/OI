#include<cstdio>
#include<algorithm>
using std::swap;
#define reg register
typedef long long ll;

ll x,y,m,n,L;

inline void exgcd(reg ll,reg ll,ll&,ll&,ll&);

int main(void){
	ll a,b,d;
	scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L);
	if(n<m)
		swap(n,m),swap(x,y);
	exgcd(n-m,L,d,a,b);
	if((x-y)%d!=0||m==n)
		puts("Impossible");
	else
		printf("%lld\n",(a*(x-y)/d%(L/d)+(L/d))%(L/d));
	return 0;
}

inline void exgcd(reg ll a,reg ll b,ll& d,ll& x,ll& y){
	if(!b)
		x=1,y=0,d=a;
	else{
		exgcd(b,a%b,d,x,y);
		ll t=x;x=y,y=t-a/b*y;
	}
	return;
}
