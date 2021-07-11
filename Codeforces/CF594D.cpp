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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=2e5+5;
const int MAXQ=2e5+5;
const int MAXA=1e6+5;
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

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return r<a.r;
	}
};

int n;
int a[MAXN];
int q;
querys qu[MAXQ];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void init(reg int s){
		n=s,fill(unit+1,unit+n+1,1);
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=1ll*unit[i]*val%mod;
		return;
	}
	inline int query(reg int id){
		reg int res=1;
		for(reg int i=id;i;i^=lowbit(i))
			res=1ll*res*unit[i]%mod;
		return res;
	}
}

bool vis[MAXA];
int tot,prime[MAXA];
int fr[MAXA];

inline void init(reg int n){
	fr[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			fr[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			fr[i*prime[j]]=prime[j];
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

int pod[MAXN];
int ans[MAXQ];
int las[MAXA];

bool ed;

int main(void){
	n=read();
	pod[0]=1;
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		Max=max(Max,a[i]);
		pod[i]=1ll*pod[i-1]*a[i]%mod;
	}
	q=read();
	for(reg int i=1;i<=q;++i)
		qu[i].id=i,qu[i].l=read(),qu[i].r=read();
	sort(qu+1,qu+q+1);
	init(Max);
	BIT::init(n);
	for(reg int i=1,ptr=1;i<=n;++i){
		while(fr[a[i]]!=1){
			reg int p=fr[a[i]];
			BIT::update(i,1ll*(p-1)*fpow(p,mod-2)%mod);
			if(las[p]){
				BIT::update(las[p],1ll*p*fpow(p-1,mod-2)%mod);
			}
			las[p]=i;
			while(!(a[i]%p))
				a[i]/=p;
		}
		while(ptr<=q&&qu[ptr].r==i){
			ans[qu[ptr].id]=1ll*pod[qu[ptr].r]*fpow(pod[qu[ptr].l-1],mod-2)%mod*BIT::query(qu[ptr].r)%mod*fpow(BIT::query(qu[ptr].l-1),mod-2)%mod;
			++ptr;
		}
	}
	for(reg int i=1;i<=q;++i)
		writeln(ans[i]);
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}