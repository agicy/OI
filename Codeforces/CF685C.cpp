#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const ll inf=4e18;

int n;
ll x[MAXN],y[MAXN],z[MAXN];
ll xans,yans,zans;

inline bool check(reg ll mid){
	reg ll l1=-inf,r1=inf;
	reg ll l2=-inf,r2=inf;
	reg ll l3=-inf,r3=inf;
	reg ll l4=-inf,r4=inf;
	for(reg int i=1;i<=n;++i){
		l1=max(l1,-mid+x[i]+y[i]+z[i]),r1=min(r1,mid+x[i]+y[i]+z[i]);
		l2=max(l2,-mid-x[i]+y[i]+z[i]),r2=min(r2,mid-x[i]+y[i]+z[i]);
		l3=max(l3,-mid+x[i]-y[i]+z[i]),r3=min(r3,mid+x[i]-y[i]+z[i]);
		l4=max(l4,-mid+x[i]+y[i]-z[i]),r4=min(r4,mid+x[i]+y[i]-z[i]);
	}
	for(reg int i=0;i<2;++i){
		reg ll l11=l1+((l1&1)^i),r11=r1-((r1&1)^i);
		reg ll l21=l2+((l2&1)^i),r21=r2-((r2&1)^i);
		reg ll l31=l3+((l3&1)^i),r31=r3-((r3&1)^i);
		reg ll l41=l4+((l4&1)^i),r41=r4-((r4&1)^i);
		if(l11<=r11&&l21<=r21&&l31<=r31&&l41<=r41){
			reg ll a=l21,b=l31,c=l41;
			if(a+b+c<=r11){
				if(a+b+c<l11)
					a=(r21<l11-b-c)?r21:l11-b-c;
				if(a+b+c<l11)
					b=(r31<l11-a-c)?r31:l11-a-c;
				if(a+b+c<l11)
					c=(r41<l11-a-b)?r41:l11-a-b;
				if(a+b+c>=l11){
					xans=(b+c)>>1,yans=(a+c)>>1,zans=(a+b)>>1;
					return true;
				}
			}
		}
	}
	return false;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			x[i]=readll(),y[i]=readll(),z[i]=readll();
		reg ll l=0,r=inf,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(check(mid))
				r=mid;
			else
				l=mid+1;
		}
		printf("%lld %lld %lld\n",xans,yans,zans);
	}
	return 0;
}