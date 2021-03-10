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

const int MAXK=15+5;

int k;
int b[MAXK],c[MAXK];
ll n,m;
int p;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

const int MAXSIZE=16;

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%p);
			}
		return res;
	}
	inline Matrix operator^(reg ll exp){
		Matrix res(n,n,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int main(void){
	k=read();
	for(reg int i=1;i<=k;++i)
		b[i]=read();
	for(reg int i=1;i<=k;++i)
		c[i]=read();
	n=readll(),m=readll(),p=read();
	for(reg int i=1;i<=k;++i)
		b[i]%=p;
	for(reg int i=1;i<=k;++i)
		c[i]%=p;
	Matrix f(k+1,k+1);
	for(reg int i=0;i<k-1;++i)
		f.unit[i+1][i]=1;
	for(reg int i=0;i<k;++i)
		f.unit[i][k-1]=c[k-i];
	f.unit[0][k]=f.unit[k][k]=1;
	Matrix bas(1,k+1);
	for(reg int i=0;i<k;++i)
		bas.unit[0][i]=b[i+1];
	reg int ans1=(bas*(f^(n-1))).unit[0][k];
	reg int ans2=(bas*(f^m)).unit[0][k];
	printf("%d\n",sub(ans2,ans1));
	return 0;
}