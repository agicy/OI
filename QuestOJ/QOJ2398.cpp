#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=1e9+7;

ll a,b;

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=(res+a)%mod;
		a=(a<<1)%mod;
		b>>=1;
	}
	return res;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

int main(void){
	scanf("%lld%lld",&a,&b);
	if(a%mod==0)
		puts("0");
	else{
		reg ll tmp=pow(a,b-1,mod-1);
		printf("%lld\n",pow(a,tmp,mod));
	}
	return 0;
}