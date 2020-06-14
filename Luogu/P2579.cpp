#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 10000
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50+5;
const int MAXSIZE=50;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator~(void){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j);
		return *this;
	}
	inline Matrix operator*(Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				for(reg int k=0;k<MAXSIZE;++k)
					res[i][j]=(res[i][j]+unit[i][k]*a[k][j]%MOD)%MOD;
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res,x=*this;
		~res;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int n,m,Start,End,K;
Matrix G,A[12];

inline void Set(reg int i,reg int p){
	for(reg int x=0;x<n;++x)
		A[i][x][p]=0;
	return;
}

int main(void){
	n=read(),m=read(),Start=read(),End=read(),K=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		G[x][y]=G[y][x]=1;
	}
	for(reg int i=0;i<12;++i)
		A[i]=G;
	reg int nfish=read();
	for(reg int i=1;i<=nfish;++i){
		static int t,p[4];
		t=read();
		for(reg int j=0;j<t;++j)
			p[j]=read();
		for(reg int j=0;j<12;++j)
			Set(j,p[j%t]);
	}
	Matrix ans;
	~ans;
	for(reg int i=1;i<=12;++i)
		ans=ans*A[i%12];
	ans=ans^(K/12);
	for(reg int i=1;i<=(K%12);++i)
		ans=ans*A[i];
	printf("%d\n",ans[Start][End]);
	return 0;
}