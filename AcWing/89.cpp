#include<cstdio>
typedef long long ll;

ll a,b,p;

ll pow(ll,ll,ll);

int main(void){
	scanf("%lld%lld%lld",&a,&b,&p);
	a%=p;
	printf("%lld\n",pow(a,b,p));
	return 0;
}

ll pow(ll x,ll exp,ll mod){
	if(!exp)
		return 1%mod;
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
