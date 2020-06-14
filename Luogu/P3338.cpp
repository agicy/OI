#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=400000+5;

int n;
int r[MAXN];

const double pi=acos(-1.0);

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
		return Complex(x*a.x-y*a.y,x*a.y+y*a.x);
	}
};

int limit;
Complex a[MAXN],b[MAXN],c[MAXN];

inline void FFT(reg Complex a[],reg int f){
	for(reg int i=0;i<limit;++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(reg int i=1;i<limit;i<<=1){
		Complex w(cos(pi/i),f*sin(pi/i));
		for(reg int j=0;j<limit;j+=(i<<1)){
			Complex e(1,0);
			for(reg int k=0;k<i;++k,e=e*w){
				static Complex x,y;
				x=a[j+k],y=a[j+k+i]*e;
				a[j+k]=x+y,a[j+k+i]=x-y;
			}
		}
	}
	if(f==-1)
		for(reg int i=0;i<limit;++i)
			a[i].x/=1.0*limit;
	return;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		scanf("%lf",&a[i].x);
		c[n-i].x=a[i].x;
		b[i].x=(1.0/(1.0*i*i));
	}
	limit=1;
	reg int l=0;
	while(limit<=(n<<1))
		limit<<=1,++l;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	FFT(a,1),FFT(b,1),FFT(c,1);
	for(reg int i=0;i<limit;++i){
		a[i]=a[i]*b[i];
		c[i]=c[i]*b[i];
	}
	FFT(a,-1),FFT(c,-1);
	for(reg int i=1;i<=n;++i)
		printf("%.3lf\n",a[i].x-c[n-i].x);
	return 0;
}