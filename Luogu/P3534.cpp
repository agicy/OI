#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000000+5;

int n;
ll m;
int x[MAXN],a[MAXN];
ll sum[MAXN];

inline int check(reg int mid){
	reg ll cnt=0;
	for(reg int i=1;i<=n;++i)
		a[i]=x[i];
	a[n+1]=-1;
	for(reg int i=2;i<=n;++i)
		if(a[i]-a[i-1]>mid){
			cnt+=(a[i]-a[i-1])-mid;
			a[i]=a[i-1]+mid;
		}
	if(cnt>m)
		return 0;
	for(reg int i=n-1;i>=1;--i)
		if(a[i]-a[i+1]>mid){
			cnt+=(a[i]-a[i+1])-mid;
			a[i]=a[i+1]+mid;
		}
	if(cnt>m)
		return 0;
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	reg int l=1,r=1;
	for(reg int i=1;i<=n;++i){
		reg int temp=a[i];
		a[i]=0;
		while(a[l]<mid*(i-l))
			++l;
		while(a[r+1]>=mid*(r-i+1))
			++r;
		a[i]=temp;
		reg ll S=(1ll*mid*((1ll*(i-l)*(i-l+1)+1ll*(r-i)*(r-i+1))/2));
		if(m-cnt>=(sum[r]-sum[l-1])-S)
			return i;
	}
	return 0;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read();
	if(check(0)){
		printf("%d %d\n",check(0),0);
		return 0;
	}
	reg int l=0,r=1e9+1,mid;
	while(l+1!=r){
		mid=(l+r)>>1;
		if(check(mid)!=0)
			r=mid;
		else
			l=mid;
	}
	printf("%d %d\n",check(r),r);
	return 0;
}