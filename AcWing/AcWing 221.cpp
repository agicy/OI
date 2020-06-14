#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int phi(reg int n){
	reg int res=n;
	for(reg ll i=2;i*i<=n;++i)
		if(n%i==0){
			res=res/i*(i-1);
			while(n%i==0)
				n/=i;
		}
	if(n>1)
		res=res/n*(n-1);
	return res;
}

int n;

int main(void){
	scanf("%d",&n);
	reg ll ans=0;
	for(reg ll i=1;i*i<=n;++i)
		if(n%i==0){
			ans+=(n/i)*phi(i);
			if(i*i!=n)
				ans+=i*phi(n/i);
		}
	printf("%lld\n",ans);
	return 0;
}