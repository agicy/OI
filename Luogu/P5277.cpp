#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

namespace Cipolla{
	int alpha,a;
	const int mod=998244353;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=mod?a-mod:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+mod:a;
	}
	struct complex{
		int x,y;
		inline complex(reg int x=0,reg int y=0):x(x),y(y){
			return;
		}
	};
	inline complex operator*(const complex& a,const complex& b){
		return complex(add(1ll*a.x*b.x%mod,1ll*a.y*b.y%mod*alpha%mod),add(1ll*a.y*b.x%mod,1ll*a.x*b.y%mod));
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	inline complex fpow(complex x,int exp){
		complex res=complex(1,0);
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
	inline pair<int,int> solve(reg int x){
		if(fpow(x,(mod-1)>>1)==mod-1)
			return make_pair(-1,-1);
		srand(time(0));
		while(true){
			a=rand()%mod;
			alpha=sub(1ll*a*a%mod,x);
			if(fpow(alpha,(mod-1)>>1)==mod-1)
				break;
		}
		complex res=fpow(complex(a,1),(mod+1)>>1);
		return make_pair(min(res.x,mod-res.x),max(res.x,mod-res.x));
	}
}

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
	typedef vector<int> poly;
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg poly& a,reg int limit,reg int flag){
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
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			write(a[i]),putchar(i==siz-1?'\n':' ');
		return;
	}
	inline poly add(poly a,poly b){
		reg int s=max(a.size(),b.size());
		a.resize(s),b.resize(s);
		for(reg int i=0;i<s;++i)
			a[i]=add(a[i],b[i]);
		return a;
	}
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit,0),b.resize(limit,0);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*b[i]%p;
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
	inline poly inv(poly a){
		reg int deg=a.size();
		if(deg==1){
			poly res;
			res.resize(1);
			res[0]=fpow(a[0],p-2);
			return res;
		}
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Inv=inv(tmp);
		reg int limit=getRev(deg<<1);
		Inv.resize(limit,0),a.resize(limit,0);
		NTT(Inv,limit,1),NTT(a,limit,1);
		for(reg int i=0;i<limit;++i)
			Inv[i]=1ll*sub(2,1ll*a[i]*Inv[i]%p)*Inv[i]%p;
		NTT(Inv,limit,-1);
		Inv.resize(deg);
		return Inv;
	}
	inline poly sqrt(poly a){
		reg int deg=a.size();
		if(deg==1){
			poly res;
			res.resize(1);
			res[0]=Cipolla::solve(a[0]).first;
			return res;
		}
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Sqrt=sqrt(tmp);
		Sqrt.resize(deg);
		poly mid=mul(a,inv(Sqrt));
		mid.resize(deg);
		poly res=add(Sqrt,mid);
		reg int inv2=fpow(2,p-2);
		for(reg int i=0;i<deg;++i)
			res[i]=1ll*inv2*res[i]%p;
		return res;
	}
}

int main(void){
	reg int n=read();
	Poly::poly a;
	a.resize(n);
	for(reg int i=0;i<n;++i)
		a[i]=read();
	a=Poly::sqrt(a);
	Poly::print(a);
	flush();
	return 0;
}