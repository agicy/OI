#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

ll R;

int main(void){
	scanf("%lld",&R);
	reg ll ans=0;
	for(reg ll x=0;x*x<=R;++x){
		reg ll y=sqrt((double)R-x*x);
		ans=(ans+x*x%MOD*(2*y+1))%MOD;
	}
	printf("%lld\n",(ans<<2)%MOD);
	return 0;
}
