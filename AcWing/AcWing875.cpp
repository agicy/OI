#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;

inline int mul(reg int a,reg int b,reg int p){
	return 1ll*a*b%p;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

int main(void){
	scanf("%d",&n);
	while(n--){
		static int a,b,p;
		scanf("%d%d%d",&a,&b,&p);
		printf("%d\n",pow(a%p,b,p)%p);
	}
	return 0;
}