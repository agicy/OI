#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;
const int MAXM=2e5+5;

namespace Poly{
	const int MAXSIZE=MAXN+MAXM;
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
	int fac[MAXSIZE],invfac[MAXSIZE],Inv[MAXSIZE];
	inline void Init(reg int n){
		fac[0]=1;
		for(reg int i=1;i<=n;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[n]=fpow(fac[n],p-2);
		for(reg int i=n-1;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		for(reg int i=1;i<=n;++i)
			Inv[i]=1ll*fac[i-1]*invfac[i]%p;
		return;
	}
	inline int binom(reg int n,reg int m){
		if(m<0||n<m)
			return 0;
		else
			return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
	}
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=1;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	typedef vector<int> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=fpow(flag==1?g:invg,(p-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
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
			printf("%d%c",a[i],i==siz-1?'\n':' ');
		return;
	}
	inline poly add(poly a,poly b){
		reg int s=max(a.size(),b.size());
		for(reg int i=0;i<s;++i)
			a[i]=add(a[i],b[i]);
		return a;
	}
	inline poly sub(poly a,poly b){
		reg int s=max(a.size(),b.size());
		for(reg int i=0;i<s;++i)
			a[i]=sub(a[i],b[i]);
		return a;
	}
	inline poly der(poly a){
		for(reg int i=0,siz=a.size();i<siz-1;++i)
			a[i]=1ll*(i+1)*a[i+1]%p;
		a.pop_back();
		return a;
	}
	inline poly itg(poly a){
		vector<int> inv;
		inv.resize(a.size()+1);
		inv[0]=inv[1]=1;
		for(reg int i=2,siz=inv.size();i<siz;++i)
			inv[i]=1ll*(p-p/i)*inv[p%i]%p;
		a.resize(a.size()+1);
		for(reg int i=a.size()-1;i>0;--i)
			a[i]=1ll*a[i-1]*inv[i]%p;
		a[0]=0;
		return a;
	}
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit),b.resize(limit);
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
	inline poly ln(const poly& a){
		poly res=itg(mul(der(a),inv(a)));
		res.resize(a.size());
		return res;
	}
	inline poly exp(poly a){
		reg int deg=a.size();
		if(deg==1){
			poly res;
			res.resize(1);
			res[0]=1;
			return res;
		}
		poly tmp=a;
		tmp.resize((deg+1)>>1);
		poly Exp=exp(tmp);
		Exp.resize(deg);
		poly Ln=ln(Exp);
		Ln=sub(a,Ln);
		++Ln[0];
		poly res=mul(Exp,Ln);
		res.resize(deg);
		return res;
	}
	inline poly getStrling2(reg int n){
		reg int tmp=1;
		for(reg int i=1;i<=n;++i)
			tmp=1ll*tmp*i%p;
		vector<int> invfac;
		invfac.resize(n+1);
		invfac[n]=fpow(tmp,p-2);
		for(reg int i=n-1;i>=0;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		poly a,b;
		a.resize(n+1),b.resize(n+1);
		for(reg int i=0;i<=n;++i){
			a[i]=((i&1)?(p-1ll):1ll)*invfac[i]%p;
			b[i]=1ll*fpow(i,n)*invfac[i]%p;
		}
		poly ans=mul(a,b);
		ans.resize(n+1);
		return ans;
	}
}

using namespace Poly;

namespace Subtask1{
	inline int Solve(reg int n,reg int m){
		return fpow(m,n);
	}
}

namespace Subtask2{
	inline int Solve(reg int n,reg int m){
		if(m<n)
			return 0;
		else
			return 1ll*fac[m]*invfac[m-n]%p;
	}
}

namespace Subtask3{
	inline int Solve(reg int n,reg int m){
		if(n<m)
			return 0;
		else{
			reg int ans=0;
			for(reg int i=0;i<=m;++i){
				reg int val=1ll*binom(m,i)*fpow(m-i,n)%p;
				if(i&1)
					ans=sub(ans,val);
				else
					ans=add(ans,val);
			}
			return ans;
		}
	}
}

poly strling2;

namespace Subtask4{
	inline int Solve(reg int n,reg int m){
		reg int ans=0;
		for(reg int i=0;i<=m&&i<=n;++i)
			ans=add(ans,strling2[i]);
		return ans;
	}
}

namespace Subtask5{
	inline int Solve(reg int n,reg int m){
		return n<=m;
	}
}

namespace Subtask6{
	inline int Solve(reg int n,reg int m){
		if(n<m)
			return 0;
		else
			return strling2[m];
	}
}

namespace Subtask7{
	inline int Solve(reg int n,reg int m){
		return binom(n+m-1,m-1);
	}
}

namespace Subtask8{
	inline int Solve(reg int n,reg int m){
		return binom(m,n);
	}
}

namespace Subtask9{
	inline int Solve(reg int n,reg int m){
		return binom(n-1,m-1);
	}
}

poly f;

namespace Subtask10{
	inline int Solve(reg int n,reg int m){
		return f[n];
	}
}

namespace Subtask11{
	inline int Solve(reg int n,reg int m){
		return n<=m;
	}
}

namespace Subtask12{
	inline int Solve(reg int n,reg int m){
		if(n<m)
			return 0;
		else
			return f[n-m];
	}
}

int main(void){
	int n,m;
	scanf("%d%d",&n,&m);
	Init(n+m);
	strling2=getStrling2(n);
	poly tmp;
	tmp.resize(n+1);
	for(reg int i=1;i<=m;++i)
		for(reg int j=1;i*j<=n;++j)
			tmp[i*j]=sub(tmp[i*j],Inv[j]);
	f=inv(exp(tmp));
	printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",Subtask1::Solve(n,m),Subtask2::Solve(n,m),Subtask3::Solve(n,m),Subtask4::Solve(n,m),Subtask5::Solve(n,m),Subtask6::Solve(n,m),Subtask7::Solve(n,m),Subtask8::Solve(n,m),Subtask9::Solve(n,m),Subtask10::Solve(n,m),Subtask11::Solve(n,m),Subtask12::Solve(n,m));
	return 0;
}