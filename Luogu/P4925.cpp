#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline ll add(reg ll a,reg ll b,reg ll mod){
	reg ll sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a,mod);
		a=add(a,a,mod);
		b>>=1;
	}
	return res;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

ll k,l,p,s,w;

int main(void){
	scanf("%lld%lld%lld%lld%lld",&k,&l,&p,&s,&w);
	k%=p;
	if(!s)
		if(l==1)
			printf("%lld\n",k);
		else if(l==2)
			printf("%lld\n",mul(k,add(k,p-1,p),p));
		else
			printf("%lld\n",mul(k,mul(add(k,p-1,p),pow(add(k,p-2,p),l-2,p),p),p));
	else
		if(l==1)
			puts("1");
		else if(l==2)
			printf("%lld\n",add(k,p-1,p));
		else
			printf("%lld\n",mul(add(k,p-1,p),pow(add(k,p-2,p),l-2,p),p));
	return 0;
}