#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)) *s=getchar();
	while(isdigit(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

namespace Poly{
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
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			printf("%d%c",a[i],i==siz-1?'\n':' ');
		return;
	}
	inline poly add(poly a,poly b){
		reg int s=max(a.size(),b.size());
		a.resize(s);
		for(reg int i=0,siz=b.size();i<siz;++i)
			a[i]^=b[i];
		return a;
	}
	inline poly sub(poly a,poly b){
		reg int s=max(a.size(),b.size());
		a.resize(s);
		for(reg int i=0,siz=b.size();i<siz;++i)
			a[i]^=b[i];
		return a;
	}
	inline poly mul(poly a,poly b){
		if(a.size()==1u&&b.size()==1u)
			return poly{a[0]&b[0]};
		else{
			reg int s=a.size()+b.size()-1;
			reg int limit=getRev(s);
			vector<Complex> x(limit),y(limit);
			for(reg int i=0,siz=a.size();i<siz;++i)
				x[i]=Complex(a[i],0);
			for(reg int i=0,siz=b.size();i<siz;++i)
				y[i]=Complex(b[i],0);
			FFT(x,limit,1),FFT(y,limit,1);
			for(reg int i=0;i<limit;++i)
				x[i]=x[i]*y[i];
			FFT(x,limit,-1);
			a.resize(s);
			for(reg int i=0;i<s;++i)
				a[i]=(int(x[i].x+0.5))&1;
			return a;
		}
	}
	inline poly inv(poly a){
		reg int deg=a.size();
		if(deg==1){
			poly res;
			res.resize(1);
			res[0]=a[0];
			return res;
		}
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Inv=inv(tmp);
		reg int limit=getRev(deg<<1);
		vector<Complex> tInv(limit),ta(limit);
		for(reg int i=0;i<((deg+1)>>1);++i)
			tInv[i]=Complex(Inv[i],0);
		for(reg int i=0;i<deg;++i)
			ta[i]=Complex(a[i],0);
		FFT(tInv,limit,1),FFT(ta,limit,1);
		for(reg int i=0;i<limit;++i)
			tInv[i]=(Complex(2,0)-ta[i]*tInv[i])*tInv[i];
		FFT(tInv,limit,-1);
		Inv.resize(deg);
		for(reg int i=0;i<deg;++i)
			Inv[i]=(int(tInv[i].x+0.5))&1;
		return Inv;
	}
	inline poly R(poly a){
		reverse(a.begin(),a.end());
		return a;
	}
	inline pair<poly,poly> div(poly a,poly b){
		reg int n=a.size(),m=b.size();
		poly aR=R(a),bR=R(b);
		aR.resize(n-m+1),bR.resize(n-m+1);
		poly q=mul(aR,inv(bR));
		q.resize(n-m+1);
		q=R(q);
		poly r=q;
		r=sub(a,mul(b,r));
		r.resize(m-1);
		return make_pair(q,r);
	}
	inline void fix(poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			a[i]&=1;
		while(a.size()>1u&&!a.back())
			a.pop_back();
		if(!a.size())
			a=poly{0};
		return;
	}
	inline poly operator+(const poly& a,const poly& b){
		poly res=add(a,b);
		fix(res);
		return res;
	}
	inline poly operator-(const poly& a,const poly& b){
		poly res=sub(a,b);
		fix(res);
		return res;
	}
	inline poly operator*(const poly& a,const poly& b){
		poly res=mul(a,b);
		fix(res);
		return res;
	}
	inline poly operator/(const poly& a,const poly& b){
		poly res=mul(a,inv(b));
		fix(res);
		return res;
	}
	inline bool isZero(poly a){
		fix(a);
		reg bool res=a.size()==1u&&a[0]==0;
		return res;
	}
}

using namespace Poly;

const int MAXN=300+5;

int n;
char r[MAXN][MAXN];
char b[MAXN][MAXN];
poly G[MAXN][MAXN];

inline poly Gauss(void){
	poly res={1};
	for(reg int i=0;i<n;++i){
		for(reg int j=i+1;j<n;++j)
			while(!isZero(G[j][i])){
				poly d=G[i][i]/G[j][i];
				for(reg int k=i;k<n;++k)
					G[i][k]=G[i][k]+G[j][k]*d;
				for(reg int k=i;k<n;++k)
					swap(G[i][k],G[j][k]);
				puts("+=====#");
				for(reg int i=0;i<n;++i)
					for(reg int j=0;j<n;++j){
						printf("i=%d j=%d poly=",i,j),print(G[i][j]);
					}
				puts("+=====#");
			}
				puts("+=sdasda====#");
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j){
				printf("i=%d j=%d poly=",i,j),print(G[i][j]);
			}
				puts("+=sdasda====#");
		if(isZero(G[i][i]))
			return poly{0};
		res=res*G[i][i];
	}
	return res;
}

bool ed;

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		read(r[i]);
	for(reg int i=0;i<n;++i)
		read(b[i]);
	puts("stage1");
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j){
			G[i][j]=poly{b[i][j]-'0',r[i][j]-'0'};
			fix(G[i][j]);
		}
	puts("stage2");
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j){
			printf("i=%d j=%d poly=",i,j),print(G[i][j]);
		}
	poly res=Gauss();
	puts("=============");
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j){
			printf("i=%d j=%d poly=",i,j),print(G[i][j]);
		}
	print(res);
	res.resize(n+1);
	reg int q=read();
	while(q--)
		printf("%d\n",res[read()]);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}