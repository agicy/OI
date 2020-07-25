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
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

int n,m;
ll K;

const int MAXN=40+5;
const int MAXSIZE=3*MAXN+5;
const int MAXLOG2K=60+5;

struct Matrix{
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		for(reg int i=0;i<=3*n;++i)
			for(reg int j=0;j<=3*n;++j){
				res.unit[i][j]=0;
				for(reg int k=0;k<=3*n;++k)
					res.unit[i][j]+=unit[i][k]*a.unit[k][j];
			}
		return res;
	}
};

Matrix A,B[MAXLOG2K];

inline bool check(const Matrix& a){
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		if(K<=(sum+=(a.unit[i][0]-1)))
			return true;
	return false;
}

int main(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,c;
		u=read(),v=read(),c=read();
		++B[0].unit[u+(c-1)*n][v];
	}
	B[0].unit[0][0]=1;
	for(reg int i=1;i<=n;++i)
		B[0].unit[i][0]=B[0].unit[i][i+n]=B[0].unit[i+n][i+2*n]=1;
	reg int ptr;
	for(ptr=1;;++ptr){
		if(ptr>=MAXLOG2K){
			puts("-1");
			return 0;
		}
		B[ptr]=B[ptr-1]*B[ptr-1];
		if(check(B[ptr]))
			break;
	}
	for(reg int i=0;i<=3*n;++i)
		A.unit[i][i]=1;
	reg ll ans=0;
	for(--ptr;ptr>=0;--ptr){
		Matrix tmp=A*B[ptr];
		if(!check(tmp)){
			A=tmp;
			ans+=(1ll<<ptr);
		}
	}
	printf("%lld\n",ans);
	return 0;
}