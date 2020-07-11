#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353

const int MAXN=200000+5;

int n;
ll p[MAXN];

int main(void){
	scanf("%d",&n);
	p[0]=1;
	for(reg int i=1;i<=n;++i)
		p[i]=p[i-1]*10%MOD;
	for(reg int i=1;i<=n;++i)
		if(i==n)
			puts("10");
		else{
			reg ll mid=n-i-1,lr=2;
			mid=p[n-i-1]*mid%MOD*81%MOD,lr=lr*9%MOD*p[n-i]%MOD;
			printf("%lld ",(mid+lr)%MOD);
		}
	return 0;
}
