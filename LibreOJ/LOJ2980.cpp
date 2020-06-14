#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353
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

const int MAXN=2.5e5+5;
const int MAXM=2.5e5+5;

int n;

const int MAXSIZE=4;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				for(reg int k=0;k<MAXSIZE;++k)
					res[i][j]=(res[i][j]+(ll)unit[i][k]*a.unit[k][j]%MOD)%MOD;
		return res;
	}
	inline Matrix operator+(const Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				res[i][j]=(unit[i][j]+a.unit[i][j])%MOD;
		return res;
	}
};

Matrix I;
int a[MAXN],b[MAXN],c[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	bool istag[MAXN<<2];
	Matrix tag[MAXN<<2];
	Matrix val[MAXN<<2];
	inline void pushup(reg int k){
		val[k]=val[lson]+val[rson];
		return;
	}
	inline void Mul(reg int k,const Matrix& x){
		val[k]=val[k]*x;
		if(!istag[k]){
			istag[k]=true;
			tag[k]=x;
		}
		else
			tag[k]=tag[k]*x;
		return;
	}
	inline void pushdown(reg int k){
		if(istag[k]){
			Mul(lson,tag[k]);
			Mul(rson,tag[k]);
			istag[k]=false;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			val[k][0][0]=a[l];
			val[k][0][1]=b[l];
			val[k][0][2]=c[l];
			val[k][0][3]=1;
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,const Matrix& x){
		if(L<=l&&r<=R){
			Mul(k,x);
			return;
		}
		pushdown(k);
		if(L<=mid)
			Update(lson,l,mid,L,R,x);
		if(R>mid)
			Update(rson,mid+1,r,L,R,x);
		pushup(k);
		return;
	}
	inline Matrix Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val[k];
		pushdown(k);
		Matrix res;
		if(L<=mid)
			res=res+Query(lson,l,mid,L,R);
		if(R>mid)
			res=res+Query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read();
	I[0][0]=I[1][1]=I[2][2]=I[3][3]=1;
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read(),c[i]=read();
	Build(1,1,n);
	reg int m=read();
	while(m--){
		static int opt,l,r,v;
		static Matrix M;
		M=I;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				M[1][0]=1;
				Update(1,1,n,l,r,M);
				break;
			}
			case 2:{
				M[2][1]=1;
				Update(1,1,n,l,r,M);
				break;
			}
			case 3:{
				M[0][2]=1;
				Update(1,1,n,l,r,M);
				break;
			}
			case 4:{
				v=read();
				M[3][0]=v;
				Update(1,1,n,l,r,M);
				break;
			}
			case 5:{
				v=read();
				M[1][1]=v;
				Update(1,1,n,l,r,M);
				break;
			}
			case 6:{
				v=read();
				M[2][2]=0,M[3][2]=v;
				Update(1,1,n,l,r,M);
				break;
			}
			case 7:{
				Matrix res=Query(1,1,n,l,r);
				printf("%d %d %d\n",res[0][0],res[0][1],res[0][2]);
				break;
			}
			default:break;
		}
	}
	return 0;
}