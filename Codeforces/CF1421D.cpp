#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const ll inf=4e18;

ll x,y;
ll c1,c2,c3,c4,c5,c6;

int main(void){
	reg int t=read();
	while(t--){
		y=read(),x=read();
		c6=read(),c1=read(),c2=read(),c3=read(),c4=read(),c5=read();
		for(reg int i=1;i<=6;++i){
			c1=min(c1,c2+c6),c2=min(c2,c1+c3),c3=min(c3,c2+c4),
			c4=min(c4,c3+c5),c5=min(c5,c4+c6),c6=min(c6,c5+c1);
		}
		ll ans=inf;
		if(x<=0&&y<=0){
			ans=min(ans,c3*min(abs(x),abs(y))+max(abs(x)-abs(y),0ll)*c4+max(abs(y)-abs(x),0ll)*c2);
			ans=min(ans,c3*max(abs(x),abs(y))+max(abs(x)-abs(y),0ll)*c5+max(abs(y)-abs(x),0ll)*c1);
			ans=min(ans,c2*abs(y)+c4*abs(x));
		}
		if(x<=0&&y>=0){
			ans=min(ans,c6*abs(y)+c4*abs(y-x));
			ans=min(ans,c3*abs(x)+c5*abs(y-x));
			ans=min(ans,c4*abs(x)+c5*abs(y));
		}
		if(x>=0&&y>=0){
			ans=min(ans,c6*min(abs(x),abs(y))+max(abs(x)-abs(y),0ll)*c1+max(abs(y)-abs(x),0ll)*c5);
			ans=min(ans,c6*max(abs(x),abs(y))+max(abs(x)-abs(y),0ll)*c2+max(abs(y)-abs(x),0ll)*c4);
			ans=min(ans,c5*abs(y)+c1*abs(x));
		}
		if(x>=0&&y<=0){
			ans=min(ans,c3*abs(y)+c1*abs(y-x));
			ans=min(ans,c6*abs(x)+c2*abs(y-x));
			ans=min(ans,c1*abs(x)+c2*abs(y));
		}
		printf("%lld\n",ans);
	}
	return 0;
}