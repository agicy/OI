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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)) *s=getchar();
	while(isdigit(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

int Max;
int n;

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%p;
			x=1ll*x*x%p;
			exp>>=1;
		}
		return res;
	}
	vector<int> rev;
	inline int getRev(reg int n){
		assert(n!=1);
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg vector<int>& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=fpow(flag==1?g:invg,(p-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[i+j+k]%p;
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
			}
		}
		if(flag==-1){
			reg int inv=fpow(limit,p-2);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	typedef vector<int> poly;
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			printf("%d%c",a[i],i==siz-1?'\n':' ');
		return;
	}
	const unsigned int B=30;
	inline poly brute_force_mul(poly a,poly b){
		poly res(a.size()+b.size()-1);
		for(reg int i=0,siz=a.size();i<siz;++i)
			for(reg int j=0,siz=b.size();j<siz;++j)
				res[i+j]^=a[i]&b[j];
		return res;
	}
	inline poly mul(poly a,poly b){
		Max=max(Max,(int)a.size());
		Max=max(Max,(int)b.size());
		if(a.size()<=B&&b.size()<=B)
			return brute_force_mul(a,b);
		else{
			reg int s=a.size()+b.size()-1;
			reg int limit=getRev(s);
			a.resize(limit),b.resize(limit);
			NTT(a,limit,1),NTT(b,limit,1);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*b[i]%p;
			NTT(a,limit,-1);
			a.resize(s);
			for(reg int i=0;i<s;++i)
				a[i]&=1;
			return a;
		}
	}
	inline poly brute_force_sqr(poly a){
		poly res(a.size()+a.size()-1);
		for(reg int i=0,siz=a.size();i<siz;++i)
			for(reg int j=0,siz=a.size();j<siz;++j)
				res[i+j]^=a[i]&a[j];
		return res;
	}
	inline poly sqr(poly a){
		if(a.size()<=2*B)
			return brute_force_sqr(a);
		else{
			reg int s=a.size()+a.size()-1;
			reg int limit=getRev(s);
			a.resize(limit);
			NTT(a,limit,1);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*a[i]%p;
			NTT(a,limit,-1);
			a.resize(s);
			for(reg int i=0;i<s;++i)
				a[i]&=1;
			return a;
		}
	}
	inline poly inv(poly a){
		assert(a.size());
		reg int deg=a.size();
		if(deg==1)
			return poly{fpow(a[0],p-2)&1};
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Inv=inv(tmp);
		Inv=mul(sqr(Inv),a);
		Inv.resize(deg);
		for(reg int i=0;i<deg;++i)
			Inv[i]&=1;
		return Inv;
	}
	inline poly R(poly a){
		reverse(a.begin(),a.end());
		return a;
	}
	inline void fix(poly& a){
		if(a.size()>n+1)
			a.resize(n+1);
		for(reg int i=0,siz=a.size();i<siz;++i)
			a[i]&=1;
		while(a.size()>1u&&!a.back())
			a.pop_back();
		return;
	}
	inline bool isZero(poly a){
		fix(a);
		reg bool res=a.size()==1u&&a[0]==0;
		return res;
	}
	inline poly div(poly a,poly b){
		assert(!isZero(b));
		if(a.size()<b.size())
			return poly{0};
		if(a.size()==1u)
			return poly{1};
		assert(a.size());
		reg int n=a.size(),m=b.size();
		poly aR=R(a),bR=R(b);
		aR.resize(n-m+1),bR.resize(n-m+1);
		poly q=mul(aR,inv(bR));
		q.resize(n-m+1);
		q=R(q);
		for(reg int i=0;i<n-m+1;++i)
			q[i]&=1;
		return q;
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
		if(a.size()<b.size())
			return poly{0};
		else{
			poly res=div(a,b);
			fix(res);
			return res;
		}
	}
}

using namespace Poly;

const int MAXN=300+5;
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
			}
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
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j){
			G[i][j]=poly{b[i][j]-'0',r[i][j]-'0'};
			fix(G[i][j]);
		}
	poly res=Gauss();
	res.resize(n+1);
	reg int q=read();
	while(q--)
		printf("%d\n",res[read()]);
	fprintf(stderr,"%d\n",Max);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}