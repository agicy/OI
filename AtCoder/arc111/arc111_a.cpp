#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline ll fpow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	x%=mod;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

ll n;
int m;

int main(void){
	scanf("%lld%d",&n,&m);
	printf("%lld\n",fpow(10,n,m*m)/m);
	return 0;
}