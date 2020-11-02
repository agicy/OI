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

int n;
vector<ll> a,b,ta,tb;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static ll x;
		x=read();
		a.push_back(x);
	}
	for(reg int i=1;i<=n;++i){
		static ll x;
		x=read();
		b.push_back(x);
	}
	reg ll ans=0;
	for(reg int i=0;i<30;++i){
		ta=a,tb=b;
		reg ll T=(1<<i),mod=(T<<1);
		for(reg int j=0;j<n;++j){
			ta[j]&=mod-1;
			tb[j]&=mod-1;
		}
		sort(tb.begin(),tb.end());
		reg int cnt=0;
		for(reg int j=0;j<n;++j){
			cnt+=lower_bound(tb.begin(),tb.end(),T*2-ta[j])-lower_bound(tb.begin(),tb.end(),T-ta[j]);
			cnt+=lower_bound(tb.begin(),tb.end(),T*4-ta[j])-lower_bound(tb.begin(),tb.end(),T*3-ta[j]);
		}
		if(cnt&1)
			ans|=T;
	}
	printf("%lld\n",ans);
	return 0;
}