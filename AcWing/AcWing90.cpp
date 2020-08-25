#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline ll add(reg ll a,reg ll b,reg ll mod){
	reg ll sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,mod);
		a=add(a,a,mod);
		b>>=1;
	}
	return res;
}

int main(void){
	ll a,b,p;
	scanf("%lld%lld%lld",&a,&b,&p);
	a%=p,b%=p;
	printf("%lld\n",mul(a,b,p));
	return 0;
}