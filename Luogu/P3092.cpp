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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMax(reg ll &a,reg ll b){
	if(a<b)
		a=b;
	return;
}

const int MAXK=16;
const int MAXN=1e5+5;

int k,n;
ll a[MAXK];
ll c[MAXN];
ll sum[MAXN];

inline int lowbit(reg int x){
	return x&(-x);
}

int Lg[1<<MAXK];
int f[1<<MAXK];

inline int find(reg ll s,reg int st){
	reg int l=st,r=n,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(sum[mid]-sum[st-1]==s)
			return mid;
		if(sum[mid]-sum[st-1]<s)
			l=mid+1;
		else
			r=mid-1;
	}
	return r;
}

int main(void){
	k=read(),n=read();
	for(reg int i=0;i<k;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+c[i];
	reg int U=(1<<k)-1;
	ll ans=-1;
	Lg[0]=-1;
	for(reg int i=0;i<=U;++i)
		Lg[i]=Lg[i>>1]+1;
	for(reg int S=0;S<=U;++S){
		reg ll sum=0;
		for(reg int i=0;i<k;++i)
			if((S>>i)&1)
				cMax(f[S],find(a[i],f[S^(1<<i)]+1));
			else
				sum+=a[i];
		if(f[S]==n)
			cMax(ans,sum);
	}
	printf("%lld\n",ans);
	return 0;
}