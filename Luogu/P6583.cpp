#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll n;
ll x[372];

int main(void){
	scanf("%lld",&n);
	reg int cnt=0;
	for(reg ll i=1;i<=n;i<<=1)
		for(reg ll j=i;j<=n;j*=5)
			x[++cnt]=j;
	sort(x+1,x+cnt+1);
	reg int ptr=cnt;
	reg ll ans=0;
	for(reg ll l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		reg ll tmp=n/l;
		while(ptr&&x[ptr]>tmp)
			--ptr;
		reg ll sum=r-l+1;
		sum-=r/2-(l-1)/2;
		sum-=r/5-(l-1)/5;
		sum+=r/10-(l-1)/10;
		ans+=sum*ptr*tmp;
	}
	printf("%lld\n",ans);
	return 0;
}