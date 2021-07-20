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

const int mod=998244353;

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

const int MAXN=3e3+5;

int tot,x[MAXN],y[MAXN];
int pod[MAXN];

inline void insert(reg int _x,reg int _y){
	for(reg int i=1;i<=tot;++i)
		pod[i]=1ll*pod[i]*sub(x[i],_x)%mod;
	reg int tmp=1;
	for(reg int i=1;i<=tot;++i)
		tmp=1ll*tmp*sub(_x,x[i])%mod;
	++tot;
	x[tot]=_x,y[tot]=_y,pod[tot]=tmp;
	return;
}

inline int query(reg int _x){
	static int lef[MAXN],rig[MAXN];
	lef[0]=1;
	for(reg int i=1;i<=tot;++i)
		lef[i]=1ll*lef[i-1]*sub(_x,x[i])%mod;
	rig[tot+1]=1;
	for(reg int i=tot;i>=1;--i)
		rig[i]=1ll*rig[i+1]*sub(_x,x[i])%mod;
	static int __pod[MAXN],__invpod[MAXN],__inv[MAXN];
	__pod[0]=1;
	for(reg int i=1;i<=tot;++i)
		__pod[i]=1ll*__pod[i-1]*pod[i]%mod;
	__invpod[tot]=fpow(__pod[tot],mod-2);
	for(reg int i=tot-1;i>=0;--i)
		__invpod[i]=1ll*__invpod[i+1]*pod[i+1]%mod;
	for(reg int i=1;i<=tot;++i)
		__inv[i]=1ll*__invpod[i]*__pod[i-1]%mod;
	reg int res=0;
	for(reg int i=1;i<=tot;++i)
		res=add(res,1ll*y[i]*lef[i-1]%mod*rig[i+1]%mod*__inv[i]%mod);
	return res;
}

bool ed;

int main(void){
	reg int n=read();
	while(n--){
		static int x;
		switch(read()){
			case 1:{
				x=read();
				insert(x,read());
				break;
			}
			case 2:{
				x=read();
				writeln(query(x));
				break;
			}
			default:assert(false);
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}