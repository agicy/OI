#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

int n;

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		reg ll ans=1;
		for(reg int i=1;i<=n;++i)
			ans=ans/gcd(ans,i)*i;
		printf("%lld\n",ans);
	}
	return 0;
}