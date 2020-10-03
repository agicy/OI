#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;

ll n,a,b,c;
ll h[MAXN];
ll sum[MAXN];

inline ll check(int mid){
	reg int before=upper_bound(h+1,h+n+1,mid)-(h+1),after=n-before;
	reg ll sum1=sum[before],sum2=sum[n]-sum1;
	ll up=sum2-(ll)after*mid,down=(ll)mid*before-sum1;
	reg ll Min=min(down,up);
	return min(down*a+up*b,Min*c+(up-Min)*b+(down-Min)*a);
}

int main(void){
	n=read(),a=read(),b=read(),c=read();
	c=min(c,a+b);
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	sort(h+1,h+n+1);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+h[i];
	reg int l=0,r=1e9,mid;
	ll ans=3e18;
	while(r-l>1){
		mid=(l+r)>>1;
		ll val1=check(mid),val2=check(mid+1);
		ans=min(ans,min(val1,val2));
		if(!ans){
			puts("0");
			return 0;
		}
		if(val1<val2)
			r=mid-1;
		else
			l=mid+1;
	}
	for(reg int i=l-1;i<=r+1;++i)
		ans=min(ans,check(i));
	printf("%lld\n",ans);
	return 0;
}