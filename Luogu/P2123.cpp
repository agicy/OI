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

const int MAXN=20000+5;

struct Node{
	int a,b,d;
	inline void Read(void){
		a=read(),b=read();
		d=(a==b)?0:(a-b)/abs(a-b);
		return;
	}
	inline bool operator<(const Node &x)const{
		return d==x.d?(d<=0?a<x.a:b>x.b):d<x.d;
	}
};

int n;
Node p[MAXN];

int main(void){
	int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			p[i].Read();
		sort(p+1,p+n+1);
		ll ans=0,sum=0;
		for(reg int i=1;i<=n;++i){
			sum+=p[i].a;
			ans=max(ans,sum)+p[i].b;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
