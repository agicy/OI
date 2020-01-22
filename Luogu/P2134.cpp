#include<cstdio>
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define min(a,b) ( (a) < (b) ? (a) : (b) )

int n;
ll p,q;

ll travel(ll day,ll times);

int main(void){
	register int i;
	register ll ans=INF;
	scanf("%d%lld%lld",&n,&p,&q);
	for(i=0;i<=n;++i)
		ans=min(ans,i*q+travel(n-i,i+1));
	printf("%lld\n",ans);
	return 0;
}

ll travel(ll day,ll times){
	return p*(times-(day%times))*(day/times)*(day/times)+p*(day%times)*((day/times)+1)*((day/times)+1);
}
