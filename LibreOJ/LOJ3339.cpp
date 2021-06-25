#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=50;
const int MAXW=5;
const int MAXK=200;
const int MAXLOG2T=29+1;
const int MAXSIZE=MAXN*MAXW;
const ll inf=1e18;

struct Matrix{
	int n,m;
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n=0,reg int m=0,reg ll x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:-inf;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,-inf);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg ll r=unit[i][k];
				if(r!=-inf)
					for(reg int j=0;j<a.m;++j)
						if(a.unit[k][j]!=-inf)
							res.unit[i][j]=max(res.unit[i][j],r+a.unit[k][j]);
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res(n,n,0),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

struct Event{
	int t,u,w;
	inline bool operator<(const Event& a)const{
		return t<a.t;
	}
};

int n,m,t,k;
int c[MAXN];
int id[MAXN][MAXW];
Event E[MAXK];
Matrix f,bas[MAXLOG2T];

inline void trans(Matrix& A,reg int t){
	for(reg int i=MAXLOG2T-1;i>=0;--i)
		if((t>>i)&1)
			A=A*bas[i];
	return;
}

int main(void){
	freopen("delicacy.in","r",stdin);
	freopen("delicacy.out","w",stdout);
	n=read(),m=read(),t=read(),k=read();
	for(reg int i=0;i<n;++i)
		c[i]=read();
	f=Matrix(5*n,5*n,-inf);
	reg int tot=0;
	for(reg int i=0;i<n;++i){
		for(reg int j=0;j<5;++j)
			id[i][j]=tot++;
		for(reg int j=1;j<5;++j)
			f.unit[id[i][j-1]][id[i][j]]=0;
	}
	for(reg int i=0;i<m;++i){
		static int u,v,w;
		u=read()-1,v=read()-1,w=read();
		f.unit[id[u][w-1]][id[v][0]]=c[v];
	}
	for(reg int i=0;i<k;++i)
		E[i].t=read(),E[i].u=read()-1,E[i].w=read();
	sort(E,E+k);
	Matrix A(1,5*n,-inf);
	A.unit[0][id[0][0]]=c[0];
	bas[0]=f;
	for(reg int i=1;i<MAXLOG2T;++i)
		bas[i]=bas[i-1]*bas[i-1];
	reg int las=0;
	for(reg int i=0;i<k;++i){
		trans(A,E[i].t-las);
		if(A.unit[0][id[E[i].u][0]]!=-inf)
			A.unit[0][id[E[i].u][0]]+=E[i].w;
		las=E[i].t;
	}
	if(las!=t)
		trans(A,t-las);
	printf("%lld\n",(A.unit[0][id[0][0]]==-inf)?-1:A.unit[0][id[0][0]]);
	return 0;
}