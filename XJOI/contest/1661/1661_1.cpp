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

const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
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
	inline modInt operator-(void)const{
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

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

const int K=300;

modInt fac[K+1],invfac[K+1];
modInt bas2[K+1];
modInt strling1[K+1][K+1],strling2[K+1][K+1];

inline modInt binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return fac[n]*invfac[m]*invfac[n-m];
}

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	bas2[0]=1;
	for(reg int i=1;i<=n;++i)
		bas2[i]=bas2[i-1]+bas2[i-1];
	strling1[0][0]=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=i;++j)
			strling1[i][j]=strling1[i-1][j-1]+strling1[i-1][j]*(i-1);
	strling2[0][0]=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=i;++j)
			strling2[i][j]=strling2[i-1][j-1]+strling2[i-1][j]*j;
	return;
}

int n,m,k;
modInt basn[K+1],dnp[K+1],val[K+1];

int main(void){
	Init(K);
	reg int t=read();
	while(t--){
		n=read(),m=read(),k=read();
		n-=m;
		modInt N=n,M=m;
		const modInt inv2=fpow(2,mod-2);
		basn[0]=1;
		for(reg int i=1;i<=k;++i)
			basn[i]=basn[i-1]*N;
		dnp[0]=1;
		for(reg int i=1;i<=k;++i)
			dnp[i]=dnp[i-1]*(M-i+1);
		for(reg int p=0;p<=k;++p){
			modInt bas=fpow(2,m);
			val[p]=0;
			for(reg int q=0;q<=p;bas=bas*inv2,++q)
				val[p]=val[p]+bas*strling2[p][q]*dnp[q];
		}
		modInt ans=0;
		for(reg int j=0;j<=k;++j){
			modInt sum=0;
			for(reg int p=0;p<=j;++p)
				sum=sum+binom(j,p)*basn[j-p]*bas2[p]*val[p];
			if((k-j)&1)
				ans=ans-strling1[k][j]*sum;
			else
				ans=ans+strling1[k][j]*sum;
		}
		ans=ans*invfac[k];
		writeln(ans.x);
	}
	flush();
	return 0;
}