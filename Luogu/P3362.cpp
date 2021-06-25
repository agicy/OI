#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

const int MAXN=1e7+5;
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
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,d,q;
bool vis[MAXN];
int tot,prime[MAXN];
int Min[MAXN],Mind[MAXN];
int f[MAXN];

inline void Init(reg int n){
	f[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			Min[i]=i;
			Mind[i]=fpow(i,d);
			f[i]=add(Mind[i],1);
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				Min[i*prime[j]]=Min[i]*prime[j];
				Mind[i*prime[j]]=1ll*Mind[i]*Mind[prime[j]]%mod;
				f[i*prime[j]]=add(f[i],1ll*Mind[i*prime[j]]*f[i/Min[i]]%mod);
				break;
			}
			Min[i*prime[j]]=prime[j];
			Mind[i*prime[j]]=Mind[prime[j]];
			f[i*prime[j]]=1ll*f[i]*f[prime[j]]%mod;
		}
	}
	for(reg int i=2;i<=n;++i)
		f[i]=add(f[i],f[i-1]);
	return;
}

int main(void){
	n=read(),d=readll()%(mod-1),q=read();
	Init(n);
	while(q--){
		static int l,r;
		l=read(),r=read();
		writeln(sub(f[r],f[l-1]));
	}
	flush();
	return 0;
}