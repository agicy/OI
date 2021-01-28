#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=4e4+5;
const int MAXA=2e4+5;
const double pi=acos(-1.0);
const double eps=1e-6;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

namespace Poly{
	struct Complex{
		double x,y;
		inline Complex(reg double x=0,reg double y=0):x(x),y(y){
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
	typedef vector<Complex> poly;
	const int MAXS=MAXA*2*3;
	const int MAXSIZE=131072;
	int rev[MAXSIZE];
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		for(reg int i=1;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void FFT(poly& a,reg int limit,reg int type){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			Complex w(cos(pi/i),type*sin(pi/i));
			for(reg int j=0;j<limit;j+=(i<<1)){
				Complex e(1,0);
				for(reg int k=0;k<i;++k,e=e*w){
					Complex x=a[j+k],y=a[i+j+k]*e;
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(type==-1)
			for(reg int i=0;i<limit;++i)
				a[i].x=(ll)(a[i].x/limit+0.5);
		return;
	}
}

using namespace Poly;

int n;
int x[MAXN];

int main(void){
	n=read();
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		x[i]=read()+2e4;
		Max=max(Max,x[i]);
	}
	poly a,b,c;
	a.resize(3*Max+1);
	b.resize(3*Max+1);
	c.resize(3*Max+1);
	for(reg int i=1;i<=n;++i)
		++a[x[i]].x,++b[2*x[i]].x,++c[3*x[i]].x;
	reg int limit=getRev(3*Max+1);
	a.resize(limit),b.resize(limit),c.resize(limit);
	FFT(a,limit,1),FFT(b,limit,1),FFT(c,limit,1);
	for(reg int i=0;i<limit;++i)
		a[i]=(a[i]*(a[i]*a[i]-b[i]*3)+c[i]*2);
	FFT(a,limit,-1);
	for(reg int i=1;i<=3*Max;++i)
		if(a[i].x>eps)
			printf("%d : %lld\n",i-60000,(ll)(a[i].x/6));
	return 0;
}