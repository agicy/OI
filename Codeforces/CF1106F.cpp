#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXK=100;
const int mod=998244353;
const int g=3;

inline int add(reg int a,reg int b,reg int mod){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b,reg int mod){
	a-=b;
	return a<0?a+mod:a;
}

inline int mul(reg int a,reg int b,reg int mod){
	return 1ll*a*b%mod;
}

inline int fpow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

const int MAXSIZE=MAXK;

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],mul(r,a.unit[k][j],mod-1),mod-1);
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

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline int BSGS(reg int a,reg int b,reg int p){
	map<int,int> M;
	reg int m=ceil(sqrt(p));
	for(reg int i=1;i<=m;++i){
		b=1ll*b*a%p;
		M[b]=i;
	}
	reg int tmp=fpow(a,m,p);
	b=1;
	for(reg int i=1;i<=m;++i){
		b=1ll*b*tmp%p;
		if(M.count(b))
			return i*m-M[b];
	}
	return -1;
}

inline int phi(reg int x){
	reg int res=x;
	for(reg int i=2;i*i<=x;++i)
		if(!(x%i)){
			res=res/i*(i-1);
			while(!(x%i))
				x/=i;
		}
	if(x>1)
		res=res/x*(x-1);
	return res;
}

int k;

signed main(void){
	k=read();
	Matrix bas(1,k),f(k,k);
	for(reg int i=0;i<k;++i)
		f.unit[k-i-1][k-1]=read()%(mod-1);
	reg int n=read()-k;
	reg int tmp=BSGS(g,read(),mod);
	for(reg int i=0;i+1<k;++i)
		f.unit[i+1][i]=1;
	bas.unit[0][k-1]=1;
	bas=bas*(f^n);
	reg int sum=bas.unit[0][k-1],p=gcd(sum,mod-1);
	if(tmp%p)
		puts("-1");
	else{
		tmp/=p,sum/=p;
		reg int exp=(mod-1)/p;
		printf("%d\n",fpow(g,mul(fpow(sum,phi(exp)-1,exp),tmp,exp),mod));
	}
	return 0;
}