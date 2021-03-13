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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%p;
			x=1ll*x*x%p;
			exp>>=1;
		}
		return res;
	}
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	typedef vector<int> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=fpow(flag==1?g:invg,(p-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[i+j+k]%p;
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
			}
		}
		if(flag==-1){
			reg int inv=fpow(limit,p-2);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*b[i]%p;
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
}

using namespace Poly;

const int MAXK=(1<<15)+5;

int fac[MAXK],invfac[MAXK];
int dfac[MAXK],bas[MAXK];

inline void Init(reg int n,reg int val){
	fac[0]=1,bas[0]=1,dfac[0]=1;
	for(reg int i=1;i<=n;++i){
		fac[i]=1ll*fac[i-1]*i%p;
		bas[i]=add(bas[i-1],bas[i-1]);
		dfac[i]=1ll*dfac[i-1]*(val-i+1)%p;
	}
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	return;
}

int main(void){
	reg int n=read(),k=read();
	reg int m=min(n,k);
	Init(m,n);
	poly a,b;
	a.resize(m+1),b.resize(m+1);
	for(reg int i=0;i<=m;++i){
		if(i&1)
			a[i]=sub(0,1ll*invfac[i]*fpow(dfac[i],p-2)%p);
		else
			a[i]=1ll*invfac[i]*fpow(dfac[i],p-2)%p;
		b[i]=1ll*invfac[i]*invfac[i]%p*bas[i]%p;
	}
	poly ans=mul(a,b);
	for(reg int i=1;i<=m;++i)
		write(1ll*ans[i]*fac[i]%p*dfac[i]%p),putchar(i==k?'\n':' ');
	for(reg int i=m+1;i<=k;++i)
		putchar('0'),putchar(i==k?'\n':' ');
	flush();
	return 0;
}