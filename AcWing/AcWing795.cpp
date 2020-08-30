#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n,m;
int a[MAXN];
ll sum[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	while(m--){
		static int l,r;
		scanf("%d%d",&l,&r);
		printf("%lld\n",sum[r]-sum[l-1]);
	}
	return 0;
}