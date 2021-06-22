#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=998244353;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
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

const int MAXM=6;

string l,r;
int M,S1,S2;
modInt basS2[MAXM+1],basS1[MAXM+1];

const int MAXSIZE=(1<<MAXM);

struct Matrix{
	int n,m;
	modInt unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,modInt x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator+(const Matrix& a)const{
		assert(n==a.n),assert(m==a.m);
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				res.unit[i][j]=unit[i][j]+a.unit[i][j];
		return res;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				modInt r=unit[i][k];
				if(r.x)
					for(reg int j=0;j<a.m;++j)
						res.unit[i][j]+=r*a.unit[k][j];
			}
		return res;
	}
	inline Matrix operator^(reg ll exp)const{
		assert(n==m);
		Matrix res(n,m,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

inline pair<Matrix,Matrix> solve(reg ll len,const Matrix& trans){
	if(len==1)
		return make_pair(trans,trans);
	else if(len&1){
		pair<Matrix,Matrix> tmp=solve(len>>1,trans);
		Matrix sum=tmp.first*trans*tmp.second+tmp.first+tmp.second*trans;
		Matrix pod=tmp.second*trans*tmp.second;
		return make_pair(sum,pod);
	}
	else{
		pair<Matrix,Matrix> tmp=solve(len>>1,trans);
		Matrix sum=tmp.first*tmp.second+tmp.first;
		Matrix pod=tmp.second*tmp.second;
		return make_pair(sum,pod);
	}
}

inline modInt getVal(reg ll x,const Matrix& trans){
	if(!x)
		return 0;
	else
		return solve(x,trans).first.unit[0][0];
}

int main(void){
	cin>>l>>r;
	scanf("%d%d%d",&M,&S1,&S2);
	S1%=mod,S2%=mod;
	basS1[0]=basS2[0]=1;
	for(reg int i=1;i<=M;++i)
		basS1[i]=basS1[i-1]*S1,basS2[i]=basS2[i-1]*S2;
	Matrix trans(1<<M,1<<M,0);
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
	reg ll L=stoll(l),R=stoll(r);
	modInt ans1=getVal(R,trans);
	modInt ans2=getVal(L-1,trans);
	modInt ans=ans1-ans2;
	printf("%d\n",ans.x);
	return 0;
}