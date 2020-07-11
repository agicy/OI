#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll n;

inline ll f(reg ll n){
	reg ll res=n;
	for(reg ll i=2;i*i<=n;++i){
		if(n%i==0){
			reg ll exp=0;
			while(n%i==0){
				++exp;
				n/=i;
			}
			res=res/i*(exp*i-exp+i);
		}
	}
	if(n>1)
		res=res/n*(n-1+n);
	return res;
}

int main(void){
	scanf("%lld",&n);
	printf("%lld\n",f(n));
	return 0;
}
