#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
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

int n;
ll a[MAXN<<1];

int main(void){
	n=read();
	for(reg int i=1;i<=(n<<1);++i)
		a[i]=read();
	sort(a+1,a+(n<<1)+1);
	ll ans=INF;
	for(reg int i=2;i+n-1<=(n<<1);++i)
		ans=min(ans,(a[n<<1]-a[1])*(a[i+n-1]-a[i]));
	ans=min(ans,(a[n]-a[1])*(a[n<<1]-a[n+1]));
	printf("%lld\n",ans);
	return 0;
}
