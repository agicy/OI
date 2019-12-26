#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll n,k;

int main(void){
	reg ll ans=0;
	scanf("%lld%lld",&n,&k);
	for(reg ll x=1,y;x<=n;x=y+1){
		if(k/x)
			y=min(k/(k/x),n);
		else
			break;
		ans+=(k/x)*(y-x+1)*(x+y)/2;
	}
	printf("%lld\n",n*k-ans);
	return 0;
}
