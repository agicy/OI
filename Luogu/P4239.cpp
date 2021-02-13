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

namespace Poly{
	const int mod=1e9+7;
	const int B=sqrt(mod);
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
	const long double pi=acos(-1.0);
	struct Complex{
		long double x,y;
		inline Complex(reg long double x=0,reg long double y=0):x(x),y(y){
			return;
		}
		inline Complex operator+(const Complex& a)const{
			return Complex(x+a.x,y+a.y);
		}
		inline Complex operator-(const Complex& a)const{
			return Complex(x-a.x,y-a.y);
		}
		inline Complex operator*(const Complex& a)const{
			return Complex(x*a.x-y*a.y,x*a.y+y*a.x);
		}
	};
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
	inline void FFT(reg vector<Complex>& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			Complex w(cos(pi/i),flag*sin(pi/i));
			for(reg int j=0;j<limit;j+=(i<<1)){
				Complex e(1,0);
				for(reg int k=0;k<i;++k,e=e*w){
					Complex x=a[j+k],y=a[i+j+k]*e;
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1)
			for(reg int i=0;i<limit;++i)
				a[i].x/=limit;
		return;
	}
	typedef vector<int> poly;
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			write(a[i]),putchar(i==siz-1?'\n':' ');
		return;
	}
	inline poly mul(poly a,poly b){
		vector<Complex> pA,qA,pB,qB;
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		pA.resize(limit),qA.resize(limit),pB.resize(limit),qB.resize(limit);
		for(reg int i=0,siz=a.size();i<siz;++i)
			pA[i]=Complex(a[i]/B,0),qA[i]=Complex(a[i]%B,0);
		for(reg int i=0,siz=b.size();i<siz;++i)
			pB[i]=Complex(b[i]/B,0),qB[i]=Complex(b[i]%B,0);
		FFT(pA,limit,1),FFT(qA,limit,1),FFT(pB,limit,1),FFT(qB,limit,1);
		vector<Complex> p1,p2,p3;
		p1.resize(limit),p2.resize(limit),p3.resize(limit);
		for(reg int i=0;i<limit;++i){
			p1[i]=pA[i]*pB[i];
			p2[i]=pA[i]*qB[i]+qA[i]*pB[i];
			p3[i]=qA[i]*qB[i];
		}
		FFT(p1,limit,-1),FFT(p2,limit,-1),FFT(p3,limit,-1);
		poly res;
		res.resize(s);
		for(reg int i=0;i<s;++i)
			res[i]=add((ll)(p1[i].x+0.5)%mod*B%mod*B%mod,add((ll)(p2[i].x+0.5)%mod*B%mod,1ll*(ll)(p3[i].x+0.5)%mod));
		return res;
	}
	inline poly inv(poly a){
		reg int deg=a.size();
		if(deg==1){
			poly res;
			res.resize(1);
			res[0]=fpow(a[0],mod-2);
			return res;
		}
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Inv=inv(tmp);
		tmp=mul(mul(a,Inv),Inv);
		Inv.resize(a.size());
		for(reg int i=0,siz=a.size();i<siz;++i)
			Inv[i]=sub(add(Inv[i],Inv[i]),tmp[i]);
		return Inv;
	}
}

using namespace Poly;

int main(void){
	reg int n=read();
	poly x;
	x.resize(n);
	for(reg int i=0;i<n;++i)
		x[i]=read();
	poly res=inv(x);
	print(res);
	flush();
	return 0;
}