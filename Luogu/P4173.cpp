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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)&&*s!='*')*s=getchar();
	while(isalpha(*s)||*s=='*')*(++s)=getchar();
	*s='\0';
	return;
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
		inline Complex operator*(reg double a)const{
			return Complex(x*a,y*a);
		}
		inline Complex operator*(const Complex& a)const{
			return Complex(x*a.x-y*a.y,x*a.y+y*a.x);
		}
	};
	typedef vector<Complex> poly;
	const double pi=acos(-1.0);
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
				a[i].x=(int)(a[i].x/limit+0.5);
		return;
	}
}

using namespace Poly;

const int MAXN=3e5+5;

int n,m;
char sa[MAXN],sb[MAXN];
int a[MAXN],b[MAXN];

int main(void){
	m=read(),n=read(),read(sa),read(sb);
	reg int limit=getRev(n+m);
	for(reg int i=0;i<m;++i)
		if(sa[i]!='*')
			a[i]=sa[i]-'a'+1;
	for(reg int i=0;i<n;++i)
		if(sb[i]!='*')
			b[i]=sb[i]-'a'+1;
	reverse(a,a+m);
	poly A,B,ans;
	A.resize(limit),B.resize(limit),ans.resize(limit);
	for(reg int i=0;i<m;++i)
		A[i]=Complex(a[i]*a[i]*a[i],0);
	for(reg int i=0;i<n;++i)
		B[i]=Complex(b[i],0);
	FFT(A,limit,1),FFT(B,limit,1);
	for(reg int i=0;i<limit;++i)
		ans[i]=ans[i]+A[i]*B[i];
	for(reg int i=0;i<m;++i)
		A[i]=Complex(a[i]*a[i],0);
	for(reg int i=m;i<limit;++i)
		A[i]=Complex(0,0);
	for(reg int i=0;i<n;++i)
		B[i]=Complex(b[i]*b[i],0);
	for(reg int i=n;i<limit;++i)
		B[i]=Complex(0,0);
	FFT(A,limit,1),FFT(B,limit,1);
	for(reg int i=0;i<limit;++i)
		ans[i]=ans[i]-A[i]*B[i]*2.0;
	for(reg int i=0;i<m;++i)
		A[i]=Complex(a[i],0);
	for(reg int i=m;i<limit;++i)
		A[i]=Complex(0,0);
	for(reg int i=0;i<n;++i)
		B[i]=Complex(b[i]*b[i]*b[i],0);
	for(reg int i=n;i<limit;++i)
		B[i]=Complex(0,0);
	FFT(A,limit,1),FFT(B,limit,1);
	for(reg int i=0;i<limit;++i)
		ans[i]=ans[i]+A[i]*B[i];
	FFT(ans,limit,-1);
	reg int top=0;
	static int S[MAXN];
	for(reg int i=m-1;i<n;++i)
		if(fabs(ans[i].x)<=0.5)
			S[++top]=i-m+2;
	printf("%d\n",top);
	for(reg int i=1;i<=top;++i)
		printf("%d%c",S[i],i==top?'\n':' ');
	return 0;
}