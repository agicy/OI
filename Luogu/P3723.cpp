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

const int MAXN=50000+5;
const int MAXSIZE=131072*8;
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
		return Complex(x*a.x-y*a.y,x*a.y+a.x*y);
	}
};

int limit;
int r[MAXSIZE];

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

int n,m;
int a[MAXN],b[MAXN];
Complex A[MAXSIZE],B[MAXSIZE];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	reg ll sum1=0,sum2=0;
	for(reg int i=1;i<=n;++i){
		sum1+=a[i]-b[i];
		sum2+=a[i]*a[i]+b[i]*b[i];
	}
	for(reg int i=1;i<=n;++i)
		A[i].x=A[i+n].x=a[i];
	for(reg int i=1;i<=n;++i)
		B[n-i+1].x=b[i];
	limit=1;
	reg int l=0;
	while(limit<=3*n)
		limit<<=1,++l;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	FFT(A,1),FFT(B,1);
	for(reg int i=0;i<limit;++i)
		A[i]=A[i]*B[i];
	FFT(A,-1);
	ll ans=1e18;
	for(reg int i=1;i<=n;++i)
		for(reg int j=-m;j<=m;++j)
			ans=min(ans,sum2+1ll*n*j*j-2ll*j*sum1-2ll*(ll)(A[i+n].x+0.5));
	printf("%lld\n",ans);
	return 0;
}