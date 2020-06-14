#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 45989
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50+5;
const int MAXM=60+5;
const int MAXSIZE=125;

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n=0,reg int m=0):n(n),m(m){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void operator~(void){
		for(reg int i=0;i<n;++i)
			unit[i][i]=1;
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(const Matrix &a){
		Matrix res(n,a.m);
		reg int r;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res[i][j]=(res[i][j]+a.unit[k][j]*r%MOD)%MOD;
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res(this->n,this->m),x=*this;
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

int n,m,t,A,B;
int cnt=1,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v){
	Add_Edge(u,v);
	Add_Edge(v,u);
	return;
}

int main(void){
	n=read(),m=read(),t=read(),A=read(),B=read();
	for(reg int i=0;i<m;++i)
		Add_Tube(read(),read());
	Matrix T(cnt+1,cnt+1);
	for(reg int i=2;i<=cnt;++i)
		for(reg int j=head[to[i]];j;j=Next[j])
			if((i^j)!=1)
				T[i][j]+=1;
	Matrix ans(1,cnt+1);
	for(reg int i=head[A];i;i=Next[i])
		ans[0][i]=1;
	ans=ans*(T^(t-1));
	reg int Ans=0;
	for(reg int i=head[B];i;i=Next[i])
		Ans=(Ans+ans[0][i^1])%MOD;
	printf("%d\n",Ans);
	return 0;
}