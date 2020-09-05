#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

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

const int MAXSIZE=2097152*4;

int n,m;
int limit,l,r[MAXSIZE];
Complex a[MAXSIZE], b[MAXSIZE];

inline void DFT(reg Complex a[],reg int f){
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
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<=n;++i)
		a[i].x=read();
	for(reg int i=0;i<=m;++i)
		b[i].x=read();
	limit=1;
	while(limit<=n+m)
		limit<<=1,++l;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	DFT(a,1),DFT(b,1);
	for(reg int i=0;i<=limit;++i)
		a[i]=a[i]*b[i];
	DFT(a,-1);
	for(reg int i=0;i<=n+m;++i)
		printf("%d%c",(int)(a[i].x/limit+0.5),i==n+m?'\n':' ');
	return 0;
}