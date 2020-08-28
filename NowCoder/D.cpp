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
inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int p=998244353;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

int n;
ll k;

const int MAXSIZE=500;

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int N,reg int M){
		n=N,m=M;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline Matrix operator*(const Matrix& a){
		if(m!=a.n)
			exit(-1);
		Matrix res(n,a.m);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k)
				if(unit[i][k]){
					reg int r=unit[i][k];
					for(reg int j=0;j<a.m;++j)
						if(a.unit[k][j])
							res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j]));
				}
		return res;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline void print(void){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				printf("%d%c",unit[i][j],j==m-1?'\n':' ');
		return;
	}
};

int a,b,c;

int main(void){
	n=read(),k=readll()%998244352,a=read(),b=read(),c=read();
	reg int s=add(a,add(b,c));
	reg int invs=fpow(s,p-2);
	reg int pr=mul(a,invs),pl=mul(b,invs),pm=mul(c,invs);
	Matrix f(n,n);
	for(reg int i=0;i<n;++i){
		reg int l=(i==0?n-1:i-1),r=(i+1==n?0:i+1);
		f[i][l]=pl,f[i][i]=pm,f[i][r]=pr;
	}
	Matrix base(1,n);
	for(reg int i=0;i<n;++i){
		static int x;
		x=read();
		base[0][i]=x;
	}
	while(k){
		if(k&1)
			base=base*f;
		f=f*f;
		k>>=1;
	}
	for(reg int i=0;i<n;++i)
		printf("%d%c",base[0][i],i==n-1?'\n':' ');
	return 0;
}