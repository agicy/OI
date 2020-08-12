#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int MAXSIZE=2;
const int p=998244353;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		return;
	}
	inline Matrix(reg int x){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res(0);
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int k=0;k<MAXSIZE;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<MAXSIZE;++j)
					res[i][j]=add(res[i][j],mul(r,a.unit[k][j]));
			}
		return res;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline void print(void){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				printf("%d%c",unit[i][j],j==MAXSIZE-1?'\n':' ');
		return;
	}
};

int n,m,type;
int a[MAXN+MAXM];
Matrix pre[MAXN+MAXM],inv[MAXN+MAXM];

int main(void){
	n=read(),m=read(),type=read();
	pre[0]=inv[0]=Matrix(1);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		static Matrix f,invf;
		f[0][0]=a[i],f[0][1]=f[1][0]=1,f[1][1]=0;
		invf[0][0]=0,invf[0][1]=invf[1][0]=1,invf[1][1]=add(0,p-a[i]);
		pre[i]=pre[i-1]*f;
		inv[i]=invf*inv[i-1];
	}
	reg int lastans=0;
	while(m--){
		static int opt,l,r;
		opt=read();
		switch(opt){
			case 1:{
				a[++n]=read()^lastans;
				Matrix f,invf;
				f[0][0]=a[n],f[0][1]=f[1][0]=1,f[1][1]=0;
				invf[0][0]=0,invf[0][1]=invf[1][0]=1,invf[1][1]=add(0,p-a[n]);
				pre[n]=pre[n-1]*f;
				inv[n]=invf*inv[n-1];
				break;
			}
			case 2:{
				l=read()^lastans,r=read()^lastans;
				Matrix f,base,ans;
				f=inv[l-1]*pre[r];
				base[0][0]=1,base[0][1]=base[1][0]=base[1][1]=0;
				ans=f*base;
				printf("%d %d\n",ans[0][0],ans[1][0]);
				lastans=type*(ans[0][0]^ans[1][0]);
				break;
			}
		}
	}
	return 0;
}