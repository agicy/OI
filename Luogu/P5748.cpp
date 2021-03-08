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

inline int max(reg int a,reg int b){
	return a>b?a:b;
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
		for(reg int i=1;i<limit;++i)
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
					reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
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
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			printf("%d%c",a[i],i==siz-1?'\n':' ');
		return;
	}
	inline poly add(poly a,poly b){
		reg int s=max(a.size(),b.size());
		for(reg int i=0;i<s;++i)
			a[i]=add(a[i],b[i]);
		return a;
	}
	inline poly sub(poly a,poly b){
		reg int s=max(a.size(),b.size());
		for(reg int i=0;i<s;++i)
			a[i]=sub(a[i],b[i]);
		return a;
	}
	inline poly der(poly a){
		for(reg int i=0,siz=a.size();i<siz-1;++i)
			a[i]=1ll*(i+1)*a[i+1]%p;
		a.pop_back();
		return a;
	}
	inline poly itg(poly a){
		vector<int> inv;
		inv.resize(a.size()+1);
		inv[0]=inv[1]=1;
		for(reg int i=2,siz=inv.size();i<siz;++i)
			inv[i]=1ll*(p-p/i)*inv[p%i]%p;
		a.resize(a.size()+1);
		for(reg int i=a.size()-1;i>0;--i)
			a[i]=1ll*a[i-1]*inv[i]%p;
		a[0]=0;
		return a;
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
	inline poly inv(poly a){
		reg int deg=a.size();
		if(deg==1){
			poly res;
			res.resize(1);
			res[0]=fpow(a[0],p-2);
			return res;
		}
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Inv=inv(tmp);
		reg int limit=getRev(deg<<1);
		Inv.resize(limit,0),a.resize(limit,0);
		NTT(Inv,limit,1),NTT(a,limit,1);
		for(reg int i=0;i<limit;++i)
			Inv[i]=1ll*sub(2,1ll*a[i]*Inv[i]%p)*Inv[i]%p;
		NTT(Inv,limit,-1);
		Inv.resize(deg);
		return Inv;
	}
	inline poly ln(const poly& a){
		poly res=itg(mul(der(a),inv(a)));
		res.resize(a.size());
		return res;
	}
	inline poly exp(poly a){
		reg int deg=a.size();
		if(deg==1){
			poly res;
			res.resize(1);
			res[0]=1;
			return res;
		}
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Exp=exp(tmp);
		Exp.resize(deg);
		poly Ln=ln(Exp);
		Ln=sub(a,Ln);
		++Ln[0];
		poly res=mul(Exp,Ln);
		res.resize(deg);
		return res;
	}
}

using namespace Poly;

const int MAXT=1e3+5;
const int MAXN=1e5+5;

int n[MAXT];
int fac[MAXN];

int main(void){
	reg int t=read();
	reg int Max=0;
	for(reg int i=1;i<=t;++i){
		n[i]=read();
		Max=max(Max,n[i]);
	}
	poly bell;
	bell.resize(Max+1);
	bell[1]=1;
	bell=exp(bell);
	bell[0]=0;
	bell=exp(bell);
	fac[0]=1;
	for(reg int i=1;i<=Max;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	for(reg int i=1;i<=t;++i)
		writeln(1ll*bell[n[i]]*fac[n[i]]%p);
	flush();
	return 0;
}