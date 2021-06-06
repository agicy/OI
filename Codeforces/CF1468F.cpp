#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int MAXN=1e5+5;

int n;
int x[MAXN],y[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		map<pair<int,int>,int> M;
		n=read();
		for(reg int i=1;i<=n;++i){
			static int x1,y1,x2,y2;
			x1=read(),y1=read(),x2=read(),y2=read();
			x[i]=x2-x1,y[i]=y2-y1;
			reg int d=gcd(abs(x[i]),abs(y[i]));
			x[i]/=d,y[i]/=d;
			++M[make_pair(x[i],y[i])];
		}
		reg ll ans=0;
		for(reg int i=1;i<=n;++i)
			ans+=M[make_pair(-x[i],-y[i])];
		writeln(ans>>1);
	}
	flush();
	return 0;
}