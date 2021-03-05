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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e5+5;
const int MAXP=2e7+5;

bool vis[MAXP];
int tot,prime[MAXP];
int phi[MAXP];

inline void Init(reg int n){
	phi[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	return;
}

int n,m;
int a[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

inline int getMod(reg ll x,reg int p){
	return x>=p?x%p+p:x;
}

inline int fpow(reg int x,reg int exp,reg int p){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=getMod(1ll*res*x,p);
		x=getMod(1ll*x*x,p);
		exp>>=1;
	}
	return res;
}

inline int getVal(reg int l,reg int r,reg int p){
	if(l==r||p==1)
		return getMod(BIT::query(l),p);
	else
		return fpow(getMod(BIT::query(l),p),getVal(l+1,r,phi[p]),p);
}

int main(void){
	Init(2e7);
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	BIT::Init(n);
	for(reg int i=1;i<=n;++i)
		BIT::update(i,a[i]-a[i-1]);
	while(m--){
		static int opt,l,r,p;
		opt=read(),l=read(),r=read(),p=read();
		switch(opt){
			case 1:{
				BIT::update(l,p),BIT::update(r+1,-p);
				break;
			}
			case 2:{
				writeln(getVal(l,r,p)%p);
				break;
			}
		}
	}
	flush();
	return 0;
}