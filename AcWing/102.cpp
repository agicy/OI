#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define eps 1e-5
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

int n,f;
double a[MAXN];
double sum[MAXN];

inline bool check(reg double);

int main(void){
	scanf("%d%d",&n,&f);
	for(reg int i=1;i<=n;++i)
		scanf("%lf",&a[i]);
	reg double l=-1e8,r=1e8,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%lld\n",(ll)(r*1000));
	return 0;
}

inline bool check(reg double mid){
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i]-mid;
	double Min=1e8,ans=-1e8;
	for(reg int i=f;i<=n;++i){
		Min=min(Min,sum[i-f]);
		ans=max(ans,sum[i]-Min);
	}
	return ans<=0?false:true;
}
