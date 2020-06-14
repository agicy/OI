#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,m;

int main(void){
	scanf("%d%d",&n,&m);
	if(n>m)
		swap(n,m);
	switch(n){
		case 1:{
			printf("%lld\n",pow(2,m,MOD));
			break;
		}
		case 2:{
			printf("%lld\n",pow(3,m-1,MOD)*4%MOD);
			break;
		}
		case 3:{
			printf("%lld\n",pow(3,m-3,MOD)*112%MOD);
			break;
		}
		default:{
			if(m==n)
				printf("%lld",(83*pow(8,n,MOD)%MOD+5*pow(2,n+7,MOD)%MOD)*190104168%MOD);
			else
				printf("%lld",(83*pow(8,n,MOD)%MOD+pow(2,n+8,MOD))*pow(3,m-n-1,MOD)%MOD*570312504%MOD);
			break;
		}
	}
	return 0;
}