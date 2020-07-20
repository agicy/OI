#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll a,b;

inline void exgcd(reg ll,reg ll,ll&,ll&,ll&);

int main(void){
	ll d,x,y;
	scanf("%lld%lld",&a,&b);
	exgcd(a,b,d,x,y);
	printf("%lld\n",((x/d)%(b/d)+(b/d))%(b/d));
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
