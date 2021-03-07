#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
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

int main(void){
	reg int n=read(),S=read(),T=read();
	poly strling2=getStrling2(S+1);
	reg int ans=0,tmp=1;
	for(reg int i=1;i<=n-S-T;++i)
		tmp=1ll*tmp*i%p;
	for(reg int i=S;i>=0;--i,tmp=1ll*tmp*(n-i-T)%p){
		reg int val=1ll*strling2[S-i+1]*fpow(n-i-T,T)%p*tmp%p;
		if(i&1)
			ans=sub(ans,val);
		else
			ans=add(ans,val);
	}
	printf("%d\n",ans);
	return 0;
}