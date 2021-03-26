#include<cstdio>
typedef long long ll;

int main(ll p,ll q){
	scanf("%lld%lld",&p,&q);
	printf("%lld\n",(((p-1)*(q-1))>>2)+(q==p?((q-1)>>1):0));
	return 0;
}