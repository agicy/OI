#include<cstdio>
#include<algorithm>
using std::min;
using std::sort;
typedef long long ll;

const ll MAXN=200000+5;
const ll MAXM=200000+5;

ll n,m,T;
ll a[MAXN],b[MAXM];

ll workrow(ll a[],ll n){
	ll s[MAXM];
	register ll i,mid=(n+1)>>1,ans=0;
	for(i=1;i<=n;++i){
		a[i]-=(T/n);
		s[i]=s[i-1]+a[i];
	}
	sort(s+1,s+n+1);
	for(i=1;i<=n;++i)
		ans+=abs(s[mid]-s[i]);
	return ans;
}

int main(void){
	register ll i;
	scanf("%lld%lld%lld",&n,&m,&T);
	for(i=1;i<=T;++i){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		++a[x],++b[y];
	}
	if(T%n==0&&T%m==0)
		printf("both %lld\n",workrow(a,n)+workrow(b,m));
	else if(T%n==0)
		printf("row %lld\n",workrow(a,n));
	else if(T%m==0)
		printf("column %lld\n",workrow(b,m));
	else
		puts("impossible");
	return 0;
}
