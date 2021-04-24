#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,2097152,stdin),p1==p2)?EOF:*p1++)
static char buf[2097152],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=100;
const int MAXLOG2L=30;

struct Matrix{
	int n,m;
	bitset<MAXN> unit[MAXN];
	inline Matrix(reg int n=0,reg int m=0,reg bool x=false):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				unit[i][j]=(i==j)?x:false;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k)
				if(unit[i][k])
					res.unit[i]|=a.unit[k];
		return res;
	}
};

int n,m,q;
Matrix bas[MAXLOG2L];

int main(void){
	n=read(),m=read();
	bas[0]=Matrix(n,n,false);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read()-1,y=read()-1;
		bas[0].unit[x][y]=true;
	}
	for(reg int i=1;i<MAXLOG2L;++i)
		bas[i]=bas[i-1]*bas[i-1];
	q=read();
	for(reg int i=1;i<=q;++i){
		static int l,a,b;
		static Matrix x;
		l=read(),a=read()-1,b=read()-1;
		x=Matrix(1,n,false);
		x.unit[0][a]=true;
		for(reg int j=MAXLOG2L-1;j>=0;--j)
			if((l>>j)&1)
				x=x*bas[j];
		writeln(x.unit[0][b]?"YES":"NO");
	}
	flush();
	return 0;
}