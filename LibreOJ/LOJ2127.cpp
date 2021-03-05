#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=20;
const double eps=1e-7;

int n;
int cnt[1<<MAXN];
double a[1<<MAXN];

int main(void){
	scanf("%d",&n);
	reg int limit=1<<n;
	for(reg int i=0;i<limit;++i)
		scanf("%lf",&a[i]);
	for(reg int i=0;i<limit;++i)
		cnt[i]=cnt[i>>1]+(i&1);
	for(reg int i=1;i<limit;i<<=1)
		for(reg int j=0;j<limit;j+=i<<1)
			for(reg int k=0;k<i;++k)
				a[i+j+k]+=a[j+k];
	reg double ans=0;
	for(reg int i=1;i<limit;++i)
		if(1-a[(limit-1)^i]>1e-8)
			ans+=((cnt[i]&1)?1:-1)/(1-a[(limit-1)^i]);
	if(ans<eps)
		puts("INF");
	else
		printf("%.10lf\n",ans);
	return 0;
}