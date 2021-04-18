#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int p;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

namespace Poly{
	const int B=16;
	inline int mod(reg double x){
		if(x<0)
			return (ll)(x+0.5)%p+p;
		else
			return (ll)(x+0.5)%p;
	}
	const double pi=acos(-1.0);
	struct Complex{
		double x,y;
		inline Complex(reg double x=0,reg double y=0):x(x),y(y){
			return;
		}
		inline Complex operator+(const Complex& a)const{
			return Complex(x+a.x,y+a.y);
		}
		inline Complex operator-(const Complex& a)const{
			return Complex(x-a.x,y-a.y);
		}
		inline Complex operator*(const Complex& a)const{
			return Complex(x*a.x-y*a.y,x*a.y+y*a.x);
		}
	};
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		if(limit!=(int)rev.size()){
			rev.resize(limit);
			for(reg int i=0;i<limit;++i)
				rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		}
		return limit;
	}
	inline void FFT(reg vector<Complex>& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			Complex w(cos(pi/i),flag*sin(pi/i));
			for(reg int j=0;j<limit;j+=(i<<1)){
				Complex e(1,0);
				for(reg int k=0;k<i;++k,e=e*w){
					Complex x=a[j+k],y=e*a[i+j+k];
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1)
			for(reg int i=0;i<limit;++i)
				a[i].x/=limit;
		return;
	}
	typedef vector<int> poly;
	inline poly add(poly a,poly b){
		reg int s=max(a.size(),b.size());
		a.resize(s),b.resize(s);
		for(reg int i=0;i<s;++i)
			a[i]=::add(a[i],b[i]);
		return a;
	}
	//template fix
	inline poly mul(poly a,poly b,reg int LIM){
		vector<Complex> pA,qA,pB,qB;
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		pA.resize(limit),qA.resize(limit),pB.resize(limit),qB.resize(limit);
		for(reg int i=0,siz=a.size();i<siz;++i)
			pA[i]=Complex(a[i]/B,0),qA[i]=Complex(a[i]%B,0);
		for(reg int i=0,siz=b.size();i<siz;++i)
			pB[i]=Complex(b[i]/B,0),qB[i]=Complex(b[i]%B,0);
		FFT(pA,limit,1),FFT(qA,limit,1),FFT(pB,limit,1),FFT(qB,limit,1);
		vector<Complex> p1,p2,p3;
		p1.resize(limit),p2.resize(limit),p3.resize(limit);
		for(reg int i=0;i<limit;++i)
			p1[i]=pA[i]*pB[i],p2[i]=pA[i]*qB[i]+qA[i]*pB[i],p3[i]=qA[i]*qB[i];
		FFT(p1,limit,-1),FFT(p2,limit,-1),FFT(p3,limit,-1);
		poly res;
		res.resize(s);
		for(reg int i=0;i<s;++i)
			res[i]=::add(1ll*mod(p1[i].x)*B%p*B%p,::add(1ll*mod(p2[i].x)*B%p,mod(p3[i].x)));
		res.resize(LIM);
		return res;
	}/*
	inline poly mul(poly a,poly b,reg int LIM){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		vector<Complex> x,y;
		x.resize(limit),y.resize(limit);
		for(reg int i=0,siz=a.size();i<siz;++i)
			x[i].x=a[i];
		for(reg int i=0,siz=b.size();i<siz;++i)
			y[i].x=b[i];
		FFT(x,limit,1),FFT(y,limit,1);
		for(reg int i=0;i<limit;++i)
			x[i]=x[i]*y[i];
		FFT(x,limit,-1);
		poly res;
		res.resize(s);
		for(reg int i=0;i<s;++i)
			res[i]=((ll)(x[i].x+0.5)%p+p)%p;
		res.resize(LIM);
		return res;
	}*/
}

using namespace Poly;

int m,A,O,S,U;
poly bas;

inline pair<poly,poly> solve(reg int x){
	if(x==1)
		return make_pair(bas,bas);
	else if(x&1){
		pair<poly,poly> p=solve(x-1);
		return make_pair(mul(p.first,bas,m+1),add(p.second,mul(p.first,bas,m+1)));
	}
	else{
		pair<poly,poly> p=solve(x>>1);
		return make_pair(mul(p.first,p.first,m+1),add(p.second,mul(p.first,p.second,m+1)));
	}
}

int main(void){
	scanf("%d%d%d%d%d%d",&m,&p,&A,&O,&S,&U);
	bas.resize(m+1);
	for(reg int i=1;i<=m;++i)
		bas[i]=(O*i*i+S*i+U)%p;
	printf("%d\n",solve(min(A,m)).second[m]);
	return 0;
}