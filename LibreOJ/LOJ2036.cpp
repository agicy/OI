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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMax(reg ll &a,reg ll b){
	if(a<b)
		a=b;
	return;
}

const int MAXL=1e5+5;
const ll inf=1e18;

int l,k;
int x[MAXL];
ll ans1=-1,ans2=-1;

inline ll check(reg ll mid){
	reg ll cnt=0;
	ll sum=0;
	for(reg int i=1;i<=l;++i){
		sum+=x[i];
		cMax(sum,0);
		if(sum>=mid)
			++cnt,sum=0;
	}
	return cnt;
}

int main(void){
	l=read(),k=read();
	for(reg int i=1;i<=l;++i)
		x[i]=read();
	reg ll l=1,r=inf,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)<=k){
			r=mid-1;
			if(check(mid)==k)
				ans1=mid;
		}
		else
			l=mid+1;
	}
	l=1,r=inf;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)>=k){
			l=mid+1;
			if(check(mid)==k)
				ans2=mid;
		}
		else
			r=mid-1;
	}
	if(~ans1)
		printf("%lld %lld\n",ans1,ans2);
	else
		puts("-1");
	return 0;
}