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

const int MAXN=100;
const int MAXLOG2L=30+1;

struct Matrix{
	int n;
	bitset<MAXN> unit[MAXN];
	inline Matrix(reg int n=0,reg bool x=false):n(n){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				unit[i][j]=(i==j)?x:false;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<n;++k)
				if(unit[i][k])
					res.unit[i]|=a.unit[k];
		return res;
	}
};

int n,m,q;
Matrix bas[MAXLOG2L];

int main(void){
	n=read(),m=read();
	Matrix f(n,false);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read()-1,y=read()-1;
		f.unit[x][y]=true;
	}
	bas[0]=f;
	for(reg int i=1;i<MAXLOG2L;++i)
		bas[i]=bas[i-1]*bas[i-1];
	q=read();
	for(reg int i=1;i<=q;++i){
		static int l,a,b;
		l=read(),a=read()-1,b=read()-1;
		Matrix x(n,true);
		for(reg int j=MAXLOG2L-1;j>=0;--j)
			if((l>>j)&1)
				x=x*bas[j];
		puts(x.unit[a][b]?"YES":"NO");
	}
	return 0;
}