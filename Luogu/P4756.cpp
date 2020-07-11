#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=200000+5;

int n,m;
ll sum[MAXN];
ll SMax[MAXN],topMax;
ll SMin[MAXN],topMin;
double MaxK[MAXN],MinK[MAXN];

inline double K(reg ll x1,reg ll y1,reg ll x2,reg ll y2){
	return (double)(1.0*y1-1.0*y2)/(-1.0*x1+1.0*x2);
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		sum[i]=sum[i-1]+read();
		while(topMax&&K(i,sum[i],SMax[topMax],sum[SMax[topMax]])<=K(i,sum[i],SMax[topMax-1],sum[SMax[topMax-1]]))
			--topMax;
		while(topMin&&K(i,sum[i],SMin[topMin],sum[SMin[topMin]])>=K(i,sum[i],SMin[topMin-1],sum[SMin[topMin-1]]))
			--topMin;
		SMax[++topMax]=i;
		SMin[++topMin]=i;
	}
	for(reg int i=1;i<=topMax;++i)
		MaxK[i]=K(SMax[i],sum[SMax[i]],SMax[i-1],sum[SMax[i-1]]);
	for(reg int i=1;i<=topMin;++i)
		MinK[i]=K(SMin[i],sum[SMin[i]],SMin[i-1],sum[SMin[i-1]]);
	reg ll pre=0;
	while(m--){
		reg int x=(read()+pre)%(4*n+1)-2*n;
		reg int a,b;
		if(x<=MaxK[1])
			a=0;
		else{
			reg int l=1,r=topMax,mid;
			while(l<=r){
				mid=(l+r)>>1;
				if(x>=MaxK[mid])
					l=mid+1,a=SMax[mid];
				else
					r=mid-1;
			}
		}
		if(x>=MinK[1])
			b=0;
		else{
			reg int l=1,r=topMin,mid;
			while(l<=r){
				mid=(l+r)>>1;
				if(x<=MinK[mid])
					l=mid+1,b=SMin[mid];
				else
					r=mid-1;
			}
		}
		reg ll ans=(ll)(a-b)*x+(sum[a]-sum[b]);
		printf("%lld\n",ans);
		pre=ans;
	}
	return 0;
}
