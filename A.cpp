#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void Yes(void){
	putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
	return;
}

inline void No(void){
	putchar('N'),putchar('o'),putchar('\n');
	return;
}

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

int main(void){
	reg int t=read();
	while(t--){
		static ll n,m,a,b;
		n=readll(),m=readll(),a=readll(),b=readll();
		reg ll res=m-m/b*b;
		reg ll ans=m/b+(res+b/2-1)/(b/2);
		if(res>b/2&&a>b/2){
			reg ll d=gcd(a,b);
			if(res%d==0){
				res/=d,a/=d,b/=d;
				if(!((a-res)%(b-a))){
					reg ll tmp=(a-res)/(b-a);
					if(tmp>=0&&m-(tmp+1)*a>=0)
						--ans;
				}
			}
		}
		if(ans<=n)
			Yes();
		else
			No();
	}
	flush();
	return 0;
}