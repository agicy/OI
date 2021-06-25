#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXSIZE=11;

ll n,m;
int p,q,r,t;
int u,v,w;
int x,y,z;

inline ll add(reg ll a,reg ll b){
	a+=b;
	return a>=m?a-m:a;
}

inline ll sub(reg ll a,reg ll b){
	a-=b;
	return a<0?a+m:a;
}

inline ll mul(reg ll a,reg ll b){
	reg ll res=0;
	while(b){
		if(b&1)
			res=add(res,a);
		a=add(a,a);
		b>>=1;
	}
	return res;
}

struct Matrix{
	int n,m;
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg ll x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg ll r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j]));
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
	n=readll(),m=readll();
	p=read(),q=read(),r=read(),t=read(),u=read(),v=read(),w=read(),x=read(),y=read(),z=read();
	if(n<2)
		puts("nodgd 1\nCiocio 1\nNicole 1");
	else{
		Matrix A(1,11,0),f(11,11,0);
		f.unit[0][1]=f.unit[0][2]=f.unit[0][3]=f.unit[1][0]=f.unit[1][2]=f.unit[1][4]=f.unit[2][0]=f.unit[2][1]=f.unit[2][5]=f.unit[6][6]=f.unit[7][2]=f.unit[7][7]=f.unit[8][0]=f.unit[8][6]=f.unit[8][7]=f.unit[8][8]=f.unit[9][1]=f.unit[10][2]=1,f.unit[7][6]=f.unit[8][2]=2,f.unit[0][0]=p,f.unit[1][1]=u,f.unit[2][2]=x,f.unit[3][0]=q,f.unit[4][1]=v,f.unit[5][2]=y,f.unit[6][0]=r,f.unit[7][0]=t,f.unit[9][9]=w,f.unit[10][10]=z;
		A.unit[0][0]=A.unit[0][1]=A.unit[0][2]=3,A.unit[0][3]=A.unit[0][4]=A.unit[0][5]=A.unit[0][6]=A.unit[0][7]=A.unit[0][8]=1,A.unit[0][9]=w,A.unit[0][10]=z;
		Matrix res=A*(f^(n-2));
		printf("nodgd %lld\nCiocio %lld\nNicole %lld\n",res.unit[0][0],res.unit[0][1],res.unit[0][2]);
	}
	return 0;
}