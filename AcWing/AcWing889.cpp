#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int p=1e9+7;

int n;

inline int pow(int x,int exp,int mod){
	int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int main(void){
	scanf("%d",&n);
	int ans1=1,ans2=n+1;
	for(int i=1;i<=n;++i){
		ans1=1ll*ans1*(1ll*i*(i+n)%p)%p;
		ans2=1ll*ans2*(1ll*i*i%p)%p;
	}
	printf("%lld\n",1ll*ans1*pow(ans2,p-2,p)%p);
	return 0;
}