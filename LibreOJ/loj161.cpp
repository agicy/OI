#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e6+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod,exp>>=1;
	}
	return res;
}

int n;
int a[MAXN];
int pod[MAXN],invpod[MAXN],inv[MAXN];

bool ed;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	pod[0]=1;
	for(reg int i=1;i<=n;++i)
		pod[i]=1ll*pod[i-1]*a[i]%mod;
	invpod[n]=fpow(pod[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invpod[i]=1ll*invpod[i+1]*a[i+1]%mod;
	for(reg int i=1;i<=n;++i)
		inv[i]=1ll*invpod[i]*pod[i-1]%mod;
	reg int ans=0;
	for(reg int i=n,bas=1;i>=1;--i,bas=998244353ll*bas%mod)
		ans=add(ans,1ll*inv[i]*bas%mod);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}