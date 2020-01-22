#include<cstdio>
#include<cmath>
#define INF 0X3F3F3F3F3F3F3F3F
#define min(a,b) ( (a) < (b) ? (a) : (b) )

long long n;

bool check(long long);

int main(void){
	register long long l=1,r=2000000000,mid,ans=INF;
	scanf("%lld",&n);
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)){
			r=mid-1;
			ans=min(ans,mid);
		}
		else
			l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}

bool check(long long mid){
	return mid*log10(mid)-n+1>=0;
}

