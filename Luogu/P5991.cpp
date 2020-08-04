#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll k,a,b;

inline int F(reg ll x){
	reg int res=0;
	while(x){
		res+=(x%10)*(x%10);
		x/=10;
	}
	return res;
}

int main(void){
	scanf("%lld%lld%lld",&k,&a,&b);
	reg int ans=0;
	for(reg int i=min(1458ll,b/k);i;--i){
		reg ll n=i*k;
		if(n>=a&&F(n)==i)
			++ans;
	}
	printf("%d\n",ans);
	return 0;
}