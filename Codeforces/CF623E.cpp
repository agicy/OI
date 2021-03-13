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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

namespace Poly{
	const int p=1e9+7;
	const int B=sqrt(p);
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
	int las;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		if(limit==las)
			return limit;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return las=limit;
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
	typedef vector<int> poly;
	inline void FFT(reg vector<Complex>& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			Complex w(cos(pi/i),flag*sin(pi/i));
			for(reg int j=0;j<limit;j+=(i<<1)){
				Complex e(1,0);
				for(reg int k=0;k<i;++k,e=e*w){
					Complex x=a[j+k],y=e*a[i+j+k];
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1)
			for(reg int i=0;i<limit;++i)
				a[i].x/=limit;
		return;
	}
	inline int mod(reg long double x){
		if(x<0)
			return (ll)(x+0.5)%p+p;
		else
			return (ll)(x+0.5)%p;
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
			res[i]=add(1ll*mod(p1[i].x)*B%p*B%p,add(1ll*mod(p2[i].x)*B%p,mod(p3[i].x)));
		return res;
	}
}

using namespace Poly;

const int MAXK=3e4+5;

ll n;
int k;
int fac[MAXK],invfac[MAXK];
int bas[MAXK];

inline void Init(reg int n){
	fac[0]=bas[0]=1;
	for(reg int i=1;i<=n;++i){
		fac[i]=1ll*fac[i-1]*i%p;
		bas[i]=add(bas[i-1],bas[i-1]);
	}
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	return;
}

inline poly solve(reg int n){
	if(n==1){
		poly res;
		res.resize(k+1);
		res[0]=0;
		for(reg int i=1;i<=k;++i)
			res[i]=invfac[i];
		return res;
	}
	poly res,a;
	reg int tmp=n>>1;
	res=solve(tmp);
	a.resize(k+1);
	for(reg int i=1,pod=bas[tmp];i<=k;++i,pod=1ll*pod*bas[tmp]%p)
		a[i]=1ll*res[i]*pod%p;
	res=mul(res,a);
	res.resize(k+1);
	if(n&1){
		for(reg int i=1,pod=2;i<=k;++i,pod=add(pod,pod)){
			res[i]=1ll*res[i]*pod%p;
			a[i]=invfac[i];
		}
		res=mul(res,a);
		res.resize(k+1);
	}
	return res;
}

int main(void){
	n=readll(),k=read();
	if(n>k)
		puts("0");
	else{
		Init(k);
		poly res=solve(n);
		reg int ans=0;
		for(reg int i=n;i<=k;++i)
			ans=add(ans,1ll*res[i]*fac[k]%p*invfac[k-i]%p);
		printf("%d\n",ans);
	}
	return 0;
}