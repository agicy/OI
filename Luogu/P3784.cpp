#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=(1<<20)+5;
const int M=32767;

int n,p;
int f[MAXN];
int a[MAXN];

namespace Poly{
	const double pi=acos(-1);
	inline int add(reg int x,reg int y){
		reg int sum=x+y;
		return sum>=p?sum-p:p;
	}
	inline int pow(reg int x,reg int exp,reg int mod){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	int r[MAXN],len[MAXN],_inv[MAXN];

	struct Complex{
		double x,y;
		inline Complex(reg double x=0,reg double y=0):x(x),y(y){
			return;
		}
		inline Complex operator+(const Complex& a){
			return Complex(x+a.x,y+a.y);
		}
		inline Complex operator-(const Complex& a){
			return Complex(x-a.x,y-a.y);
		}
		inline Complex operator*(const Complex& a){
			return Complex(x*a.x-y*a.y,x*a.y+a.x*y);
		}
	};
	Complex a[MAXN],b[MAXN],Aa[MAXN],Ab[MAXN],Ba[MAXN],Bb[MAXN];
	inline Complex conj(const Complex& a){
		return Complex(a.x,-a.y);
	}
	int qm(int x) {return x>=p?x-p:x;}
	inline void FFT(reg Complex a[],reg int limit){
		for(reg int i=0;i<limit;++i)
			if(i<r[i])
				swap(a[i],a[r[i]]);
		for(reg int i=1;i<limit;i<<=1) {
			Complex w(cos(pi/i),sin(pi/i));
			for(reg int j=0;j<limit;j+=(i<<1)){
				Complex e(1,0);
				for(reg int k=0;k<i;++k,e=e*w){
					Complex x=a[j+k],y=e*a[j+k+i];
					a[j+k]=x+y,a[j+k+i]=x-y;
				}
			}
		}
		return;
	}

	inline void mul(const int ka[],const int kb[],reg int res[],reg int n){
		for(reg int i=0;i<n;++i)
			r[i]=(r[i>>1]>>1)|((i&1)<<(len[n]-1));
		for(reg int i=0;i<(n>>1);++i){
			a[i]=Complex(ka[i]&M,ka[i]>>15);
			b[i]=Complex(kb[i]&M,kb[i]>>15);
			a[i+(n>>1)]=b[i+(n>>1)]=Complex(0,0);
		}
		FFT(a,n),FFT(b,n);
		for(reg int i=0;i<n;++i){
			int j=(n-i)&(n-1);
			Complex kAa=(a[i]+conj(a[j]))*Complex(0.5,0);
			Complex kAb=(a[i]-conj(a[j]))*Complex(0,-0.5);
			Complex kBa=(b[i]+conj(b[j]))*Complex(0.5,0);
			Complex kBb=(b[i]-conj(b[j]))*Complex(0,-0.5);
			Aa[j]=kAa*kBa,Ab[j]=kAa*kBb,Ba[j]=kBa*kAb,Bb[j]=kAb*kBb;
		}
		for(reg int i=0;i<n;++i){
			a[i]=Aa[i]+Ab[i]*Complex(0,1);
			b[i]=Ba[i]+Bb[i]*Complex(0,1);
		}
		FFT(a,n),FFT(b,n);
		for(reg int i=0;i<n;++i) {
			reg int kAa=(ll)(a[i].x/n+0.5)%p;
			reg int kAb=(ll)(a[i].y/n+0.5)%p;
			reg int kBa=(ll)(b[i].x/n+0.5)%p;
			reg int kBb=(ll)(b[i].y/n+0.5)%p;
			res[i]=qm(((ll)kAa+((ll)(kAb+kBa)<<15)+((ll)kBb<<30))%p+p);
		}
	}
	inline void sum(const int a[],reg int res[],reg int n){
		for(reg int i=1;i<n;++i)
			res[i]=1ll*a[i-1]*_inv[i]%p;
		res[0]=0;
		return;
	}
	inline void diff(const int a[],reg int res[],reg int n){
		for(reg int i=1;i<n;++i)
			res[i-1]=1ll*a[i]*i%p;
		res[n-1]=0;
		return;
	}
	inline void inv(const int a[],reg int res[],reg int n){
		if(n==1){
			res[0]=pow(a[0],p-2,p);
			return;
		}
		inv(a,res,n>>1);
		static int tmp1[MAXN],tmp2[MAXN];
		mul(a,res,tmp1,n<<1);
		mul(tmp1,res,tmp2,n<<1);
		for(reg int i=0;i<n;++i)
			res[i]=((res[i]<<1)-tmp2[i]+p)%p,res[i+n]=0;
		return;
	}
	inline void ln(const int a[],reg int b[],reg int n){
		static int Diff[MAXN],Inv[MAXN],tmp[MAXN];
		memset(Inv,0,sizeof(Inv));
		diff(a,Diff,n);
		inv(a,Inv,n);
		mul(Diff,Inv,tmp,n<<1);
		sum(tmp,b,n);
		return;
	}
}

int main(void){
	n=read(),p=read();
	for(reg int i=1;i<=n;++i)
		f[i]=read();
	f[0]=1;

	reg int limit=1;
	while(limit<=n)
		limit<<=1,Poly::len[limit]=Poly::len[limit>>1]+1;
	Poly::len[limit<<1]=Poly::len[limit]+1;

	Poly::_inv[1]=1;
	for(reg int i=2;i<(limit<<1);++i)
		Poly::_inv[i]=1ll*(p-p/i)*Poly::_inv[p%i]%p;

	Poly::ln(f,a,limit);
	for(reg int i=1;i<=n;++i)
		a[i]=1ll*a[i]*i%p;
	for(reg int i=1;i<=n;++i)
		for(reg int j=(i<<1);j<=n;j+=i)
			a[j]=Poly::add(a[j],p-a[i]);

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