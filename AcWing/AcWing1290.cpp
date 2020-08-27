#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int p=100003;

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int m;
ll n;

int main(void){
	scanf("%d%lld",&m,&n);
	printf("%d\n",(pow(m%p,n%(p-1),p)-(1ll*m*pow((m-1+p)%p,(n-1)%(p-1),p)%p)+p)%p);
	return 0;
}