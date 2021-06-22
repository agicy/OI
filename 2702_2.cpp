#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

const int mod=998244353;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

typedef vector<modInt> poly;

inline poly operator+(const poly& a,const poly& b){
	poly res(max(a.size(),b.size()));
	for(reg int i=0,siz=a.size();i<siz;++i) res[i]+=a[i];
	for(reg int i=0,siz=b.size();i<siz;++i) res[i]+=b[i];
	return res;
}

inline poly operator*(const poly& a,const modInt& b){
	poly res=a;
	for(reg int i=0,siz=a.size();i<siz;++i)
		res[i]*=b;
	return res;
}

inline poly operator*(const poly& a,const poly& b){
	poly res(a.size()+b.size()-1);
	for(reg int i=0,siza=a.size();i<siza;++i)
		for(reg int j=0,sizb=b.size();j<sizb;++j)
			res[i+j]+=a[i]*b[j];
	return res;
}

inline poly operator%(const poly& a,const poly& b){
	poly res=a;
	modInt inv=fpow(b.back(),mod-2);
	for(reg int i=a.size()-b.size();i>=0;--i){
		modInt tmp=res[i+b.size()-1]*inv;
		for(reg int j=0,siz=b.size();j<siz;++j)
			res[i+j]-=tmp*b[j];
	}
	res.resize(b.size());
	return res;
}

inline poly operator/(poly a,const poly& b){
	poly res(a.size()-b.size()+1);
	modInt inv=fpow(b.back(),mod-2);
	for(reg int i=res.size()-1;i>=0;--i){
		res[i]=inv*a[i+b.size()-1];
		for(reg int j=b.size()-1;j>=0;--j)
			a[i+j]-=res[i]*b[j];
	}
	return res;
}

inline poly fpow(poly x,const int exp[],const int& len,const poly& mod){
	poly res={1};
	for(reg int i=0;i<len;++i){
		poly tmp=x;
		for(reg int j=1;j<10;++j){
			if(j==exp[i])
				res=res*x%mod;
			x=x*tmp%mod;
		}
	}
	return res;
}

const int MAXM=6;

struct Matrix{
	int n,m;
	modInt unit[(1<<MAXM)+1][(1<<MAXM)+1];
	inline Matrix(reg int n,reg int m,modInt x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator+(const Matrix& a)const{
		//assert(n==a.n),assert(m==a.m);
		Matrix res(n,m,0);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				res.unit[i][j]=unit[i][j]+a.unit[i][j];
		return res;
	}
	inline Matrix operator-(const Matrix& a)const{
		//assert(n==a.n),assert(m==a.m);
		Matrix res(n,m,0);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				res.unit[i][j]=unit[i][j]-a.unit[i][j];
		return res;
	}
	inline Matrix operator*(const Matrix& a)const{
		//assert(m==a.n);
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				modInt r=unit[i][k];
				if(r.x){
					for(reg int j=0;j<a.m;++j)
						res.unit[i][j]+=r*a.unit[k][j];
				}
			}
		return res;
	}
	inline Matrix operator*(const modInt& a)const{
		Matrix res(n,m);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				res.unit[i][j]=unit[i][j]*a;
		return res;
	}
	inline modInt det(void)const{
		//assert(n==m);
		Matrix tmp=*this;
		modInt res=1;
		for(reg int i=0;i<n;++i){
			reg int ptr=-1;
			for(reg int j=i;j<n;++j)
				if(tmp.unit[i][j].x){
					ptr=j;
					break;
				}
			if(ptr==-1)
				return 0;
			if(ptr!=i)
				res=-res,swap(tmp.unit[i],tmp.unit[ptr]);
			res*=tmp.unit[i][i];
			modInt inv=fpow(tmp.unit[i][i],mod-2);
			for(reg int j=i+1;j<n;++j)
				if(tmp.unit[j][i].x){
					modInt d=tmp.unit[j][i]*inv;
					for(reg int k=i;k<n;++k)
						tmp.unit[j][k]-=d*tmp.unit[i][k];
				}
		}
		return res;
	}
};

inline poly Lagrange(const Matrix& a){
	modInt x[a.n+1],y[a.n+1];
	for(reg int i=0;i<=a.n;++i)
		x[i]=i+1,y[i]=(a-Matrix(a.n,a.m,i+1)).det();
	poly f(a.n+1),g={1};
	for(reg int i=0;i<=a.n;++i)
		g=g*poly{-x[i],1};
	for(reg int i=0;i<=a.n;++i){
		modInt pod=1;
		for(reg int j=0;j<=a.n;++j)
			if(j!=i)
				pod*=x[i]-x[j];
		pod=y[i]*fpow(pod,mod-2);
		f=f+g/poly{-x[i],1}*pod;
	}
	return f;
}

inline modInt getVal(const Matrix& a,const int exp[],const int& len,const poly& f){
	poly g=fpow({0,1},exp,len,f);
	Matrix I(a.n,a.m,1),sum(a.n,a.m,0);
	for(reg int i=0;i<a.n;++i){
		sum=sum+I*g[i];
		I=I*a;
	}
	Matrix res(a.n,a.m,0);
	res.unit[0][0]=1;
	res=res*sum;
	return res.unit[0][res.m-1];
}

const int MAXL=2501+5;

char L[MAXL],R[MAXL];
int lenL,l[MAXL],lenR,r[MAXL];
int M,S1,S2;
modInt basS2[MAXM+1],basS1[MAXM+1];

bool ed;

int main(void){
	scanf("%s%s",L,R);
	lenL=strlen(L);
	for(reg int i=0;i<lenL;++i)
		l[i]=L[i]-'0';
	reverse(l,l+lenL);
	lenR=strlen(R);
	for(reg int i=0;i<lenR;++i)
		r[i]=R[i]-'0';
	reverse(r,r+lenR);
	++r[0];
	for(reg int i=0;i<lenR;++i)
		if(r[i]>=10)
			r[i+1]+=r[i]/10,r[i]%=10;
		else
			break;
	if(r[lenR])
		++lenR;
	scanf("%d%d%d",&M,&S1,&S2);
	S1%=mod,S2%=mod;
	basS1[0]=basS2[0]=1;
	for(reg int i=1;i<=M;++i)
		basS1[i]=basS1[i-1]*S1,basS2[i]=basS2[i-1]*S2;
	Matrix trans((1<<M)+1,(1<<M)+1,0);
	trans.unit[0][1<<M]=trans.unit[1<<M][1<<M]=1;
	for(reg int S1=0;S1<(1<<M);++S1)
		for(reg int S2=0;S2<(1<<M);++S2){
			if(S1&S2)
				continue;
			reg int T=((1<<M)-1)^S1^S2;
			reg int cnt=0;
			trans.unit[S1][S2]=1;
			for(reg int i=0;i<M;++i){
				if((T>>i)&1)
					++cnt;
				else{
					if(cnt&1)
						trans.unit[S1][S2]=0;
					else
						trans.unit[S1][S2]*=basS2[cnt>>1];
					cnt=0;
				}
			}
			if(cnt&1)
				trans.unit[S1][S2]=0;
			else
				trans.unit[S1][S2]*=basS2[cnt>>1];
			cnt=0;
			trans.unit[S1][S2]*=basS1[__builtin_popcount(S2)];
		}
	poly f=Lagrange(trans);
	modInt ans=getVal(trans,r,lenR,f)-getVal(trans,l,lenL,f);
	printf("%d\n",ans.x);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}