#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
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
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,a,b,s;
int A[MAXN];

inline ll getVal(reg int mid){
	reg ll sum=-inf;
	static ll b[MAXN];
	for(reg int i=1;i<=n;++i){
		b[i]=0ll+A[i]+mid;
		sum=max(sum,b[i]);
	}
	reg ll tmp=0;
	for(reg int i=1;i<=n;++i){
		if(tmp+b[i]<0)
			tmp=0;
		else
			tmp+=b[i];
		sum=max(sum,tmp);
	}
	return sum;
}

inline int myceil(reg int a,reg int b){
	return (a+b-1)/b;
}

int main(void){
	n=read(),a=read(),b=read(),s=read();
	for(reg int i=1;i<=n;++i)
		A[i]=read();
	reg ll ans=inf;
	for(reg int i=0;i<=30;++i){
		reg int l=0,r=2e9,mid;
		while(l<r){
			mid=(0ll+l+r)>>1;
			if(getVal(mid)>=myceil(s,1<<i))
				r=mid;
			else
				l=mid+1;
		}
		ans=min(ans,1ll*l*a+1ll*i*b);
	}
	printf("%lld\n",ans);
	return 0;
}