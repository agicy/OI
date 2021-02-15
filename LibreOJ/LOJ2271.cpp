#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

namespace Poly{
	int p,B;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int mod(reg long double x){
		if(x<0)
			return (ll)(x+0.5)%p+p;
		else
			return (ll)(x+0.5)%p;
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
			return Complex(x*a.x-y*a.y,x*a.y+a.x*y);
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
	const long double pi=acos(-1.0);
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
			res[i]=add(1ll*mod(p1[i].x)*B%p*B%p,add(1ll*mod(p2[i].x)*B%p,mod(p3[i].x)));
		return res;
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
		tmp=mul(mul(a,Inv),Inv);
		Inv.resize(a.size());
		for(reg int i=0,siz=a.size();i<siz;++i)
			Inv[i]=sub(add(Inv[i],Inv[i]),tmp[i]);
		return Inv;
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
	inline poly ln(const poly& a){
		poly res=itg(mul(der(a),inv(a)));
		res.resize(a.size());
		return res;
	}
}

const int MAXN=(1<<18)+5;

int n;

int main(void){
	using namespace Poly;
	n=read(),p=read();
	B=sqrt(p);
	poly f;
	f.resize(n+1);
	for(reg int i=1;i<=n;++i)
		f[i]=read();
	f[0]=1;
	poly a=ln(f);
	for(reg int i=1;i<=n;++i)
		a[i]=1ll*a[i]*i%p;
	for(reg int i=1;i<=n;++i)
		for(reg int j=(i<<1);j<=n;j+=i)
			a[j]=sub(a[j],a[i]);
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i)
		if(a[i])
			S[++top]=i;
	printf("%d\n",top);
	for(reg int i=1;i<=top;++i)
		printf("%d%c",S[i],i==top?'\n':' ');
	return 0;
}