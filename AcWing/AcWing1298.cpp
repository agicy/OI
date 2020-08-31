#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a,b;

int main(void){
	scanf("%d",&n);
	scanf("%d%d",&a,&b);
	ll ans=b,c=a;
	for(int i=2;i<=n;++i){
		scanf("%d%d",&a,&b);
		while(ans%a!=b)
			ans+=c;
		c*=a;
	}
	printf("%lld\n",ans);
	return 0;
}