#pragma GCC optimize("Ofast")
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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
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

const int mod=20000023;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void){
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg ll exp){
	exp%=mod-1;
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

ll n,k;
modInt fac[mod],sum[mod];

inline void init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+fac[i];
	return;
}

inline modInt getSum(modInt a,modInt q,reg ll len){
	if(q.x==1)
		return a*modInt(len%mod);
	else
		return a*(fpow(q,len)-1)*fpow(q-1,mod-2);
}

inline modInt getVal(reg ll q,reg ll len){
	modInt tmp=modInt(q%mod);
	modInt realq=tmp*(tmp+1);
	reg ll cnt1=(len+1)/2,cnt2=len-cnt1;
	return getSum(tmp,realq,cnt1)+getSum(realq,realq,cnt2);
}

inline modInt getAns(ll n,reg ll k){
	if(n<=k)
		return sum[min(n,mod-1ll)];
	else if(k+1>=mod)
		return sum[mod-1];
	else
		return sum[k+1]+fac[k+1]*getVal(k,n-k-1);
}

bool ed;

int main(void){
	reg int t=read();
	init(mod-1);
	while(t--){
		n=readll(),k=readll();
		writeln(getAns(n,k).x);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}