#include<cstdio>
typedef long long ll;
#define MOD 200907

ll T,a,b,c,k;

ll pow(ll,ll,ll);

int main(void){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld%lld",&a,&b,&c,&k);
		if(a+c==(b<<1))
			printf("%lld",(((((b-a)%MOD)*(k-1))%MOD)+a)%MOD);
		else
			printf("%lld",((a%MOD)*pow(b/a,k-1,MOD))%MOD);
		putchar('\n');
	}
	return 0;
}

ll pow(ll x,ll exp,ll mod){
	if(!exp)
		return 1;
	else if(exp==1)
		return x%mod;
	else if(exp&1){
		ll temp=pow(x,exp>>1,mod);
		return (((temp*temp)%mod)*x)%mod;
	}
	else{
		ll temp=pow(x,exp>>1,mod);
		return (temp*temp)%mod;
	}
}
