#include<cstdio>
typedef long long ll;

ll a,b,p;

int main(void){
	register ll res=0;
	scanf("%lld%lld%lld",&a,&b,&p);
	while(b){
		if(b&1)
			res=(res+a)%p;
		b>>=1;
		a=(a<<1)%p;
	}
	printf("%lld\n",res);
	return 0;
}
