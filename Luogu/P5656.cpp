#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg ll d=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return d;
}

int main(void){
	reg int t=read();
	while(t--){
		reg ll a=read(),b=read(),c=read();
		static ll x,y;
		reg ll d=exgcd(a,b,x,y);
		if(c%d)
			write(-1),putchar('\n');
		else{
			x*=c/d,y*=c/d;
			reg ll p=b/d,q=a/d;
			reg ll k;
			if(x<0)
				k=ceil((1.0-x)/p),x+=p*k,y-=q*k;
			else
				k=(x-1)/p,x-=p*k,y+=q*k;
			if(y>0)
				write((y-1)/q+1),putchar(' '),write(x),putchar(' '),write((y-1)%q+1),putchar(' '),write(x+(y-1)/q*p),putchar(' '),write(y),putchar('\n');
			else
				write(x),putchar(' '),write(y+q*(ll(ceil((1.0-y)/q)))),putchar('\n');
		}
	}
	flush();
	return 0;
}