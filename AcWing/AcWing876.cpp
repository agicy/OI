#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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

inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

int n;

int main(void){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		static int a,p;
		scanf("%d%d",&a,&p);
		int d=gcd(a,p);
		if(d!=1)
			puts("impossible");
		else
			printf("%d\n",pow(a%p,p-2,p)%p);
	}
	return 0;
}