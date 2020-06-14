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

int a,b,c,d;

int main(void){
	a=read(),b=read(),c=read(),d=read();
	reg ll ans=0;
	for(reg int i=a;i<=b;++i){
		ll Min=b+i-1,Max=c+i-1;
		if(Min>=d){
			ans+=(ll)(d-c+1)*(c-b+1);
		}
		else{
			reg ll l=max(c,b+i-1),r=min(d,c+i-1);
			ans+=((ll)(r-l+1)*(l-c+1+r-c+1)>>1);
			if(Max>d)
				ans+=(ll)(Max-d)*(d-c+1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}