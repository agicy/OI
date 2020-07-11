#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 9999991

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

inline ll fact(reg ll x,reg ll mod){
	reg ll res=1;
	for(reg int i=2;i<=x;++i)
		res=res*i%mod;
	return res;
}

int n;

int main(void){
	scanf("%d",&n);
	reg int ans=fact(n-1,MOD)*pow(n,n-2,MOD)%MOD;
	printf("%d\n",ans);
	return 0;
}
