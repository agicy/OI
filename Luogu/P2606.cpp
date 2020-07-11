#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1000000+5;

int n,m;
ll sum[MAXN],inv[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	inv[1]=inv[0]=1;
	fill(sum+1,sum+n+1,1);
	for(reg int i=2;i<=n;++i)
		inv[i]=(m-m/i)*inv[m%i]%m;
	for(reg int i=n;i>=2;--i)
		sum[i>>1]+=sum[i];
	reg ll ans=1;
	for(reg int i=1;i<=n;++i)
		ans=ans*i%m*inv[sum[i]]%m;
	printf("%lld\n",ans);
	return 0;
}
