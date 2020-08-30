#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int p=200907;

inline int pow(int x,int exp,int mod){
	x%=mod;
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
	int T;
	scanf("%d",&T);
	while(T--){
		static int a,b,c,k;
		scanf("%d%d%d%d",&a,&b,&c,&k);
		if(2*b==a+c){
			int d=b-a;
			int ans=(a%p+1ll*(k-1)*d%p)%p;
			printf("%d\n",ans);
		}
		else if(1ll*b*b==1ll*a*c){
			int q=b/a;
			int ans=1ll*a*pow(q,k-1,p)%p;
			printf("%d\n",ans);
		}
		else
			puts("impossible");
	}
	return 0;
}