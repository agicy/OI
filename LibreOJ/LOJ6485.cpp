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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

ll n;
int s;
int a[4];
const int w[4]={1,911660635,998244352,86583718};
const int inv4=748683265;

int main(void){
	reg int T=read();
	while(T--){
		n=readll(),s=read();
		for(reg int i=0;i<4;++i)
			a[i]=read();
		reg int ans=0;
		for(reg int i=0;i<4;++i){
			reg int sum=0;
			for(reg int j=0;j<4;++j)
				sum=add(sum,1ll*fpow(add(w[j],s),n%(mod-1))*fpow(w[j],i)%mod);
			ans=add(ans,1ll*a[(n+i)&3]*sum%mod);
		}
		writeln(1ll*ans*inv4%mod);
	}
	flush();
	return 0;
}