#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}


inline int fpow(reg int x,reg ll exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

ll n;
int m;

int main(void){
	scanf("%lld%d",&n,&m);
	switch(n){
		case 1:{
			printf("%d\n",m);
			break;
		}
		case 2:{
			printf("%lld\n",1ll*m*sub(m,1)%mod);
			break;
		}
		default:{
			reg int ans=0;
			if(n&1)
				ans=sub(1,m);
			else
				ans=sub(m,1);
			ans=add(ans,fpow(sub(m,1),n));
			printf("%d\n",ans);
			break;
		}
	}
	return 0;
}