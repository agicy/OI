#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100+5;
const int MAXLOG2A=32;

int n,m,q;
ll a[MAXN];

struct Matrix{
	int x,y;
	ll unit[MAXN][MAXN];
	inline Matrix(reg int x=0,reg int y=0):x(x),y(y){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline Matrix operator*(const Matrix &a)const{
		Matrix res(x,a.y);
		for(reg int i=1;i<=x;++i)
			for(reg int j=1;j<=a.y;++j)
				for(reg int k=1;k<=y;++k)
					res.unit[i][j]^=unit[i][k]*a.unit[k][j];
		return res;
	}
};

Matrix g[MAXLOG2A];

int main(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	g[0].x=g[0].y=n;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		g[0].unit[u][v]=g[0].unit[v][u]=1;
	}
	for(reg int i=1,di=i-1;i<MAXLOG2A;di=i++)
		g[i]=g[di]*g[di];
	while(q--){
		reg ll x=read();
		Matrix ans(1,n);
		memcpy(ans.unit[1]+1,a+1,n*sizeof(ll));
		for(reg ll w=1,i=0;w<=x;w<<=1,++i)
			if(x&w)
				ans=ans*g[i];
		printf("%lld\n",ans.unit[1][1]);
	}
	return 0;
}