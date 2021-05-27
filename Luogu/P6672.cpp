#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=998244353;

int n;

int main(void){
	scanf("%d",&n);
	reg int m=0;
	for(reg int i=1;i<=n;++i){
		static int w;
		scanf("%d",&w);
		m+=w;
	}
	reg int ans=1;
	for(reg int i=1;i<=m;++i)
		if(m-n+1!=i)
			ans=1ll*ans*i%mod;
	printf("%d\n",ans);
	return 0;
}