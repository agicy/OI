#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n;
ll f[MAXN];

int main(void){
	scanf("%d",&n);
	reg ll ans=0;
	for(reg int i=n;i>=1;--i){
		f[i]=1ll*(n/i)*(n/i);
		for(reg int j=(i<<1);j<=n;j+=i)
			f[i]-=f[j];
		ans+=1ll*f[i]*i;
	}
	printf("%lld\n",ans);
	return 0;
}