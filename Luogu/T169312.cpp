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

const int MAXN=2e5+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
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

int n;
int l[MAXN],r[MAXN];
int cntx[MAXN],cnty[MAXN];
int fac[MAXN],invfac[MAXN];

struct Event{
	int pos,tag;
	inline Event(reg int pos=0,reg int tag=0):pos(pos),tag(tag){
		return;
	}
	inline bool operator<(const Event& a)const{
		return pos<a.pos;
	}
};

Event E[MAXN<<1];

inline void getCnt(reg int cnt[]){
	for(reg int i=1;i<=n;++i){
		static int l,r;
		l=read(),r=read();
		E[i]=Event(l,1),E[i+n]=Event(r,-1);
	}
	sort(E+1,E+(n<<1|1));
	reg int x=0;
	for(reg int i=1,ptr,las=0;i<=(n<<1);i=ptr){
		cnt[x]=add(cnt[x],E[i].pos-las);
		ptr=i;
		while(ptr<=(n<<1)&&E[ptr].pos==E[i].pos){
			x+=E[ptr].tag;
			++ptr;
		}
		las=E[i].pos;
	}
	return;
}

const int MAXSIZE=524288;

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
	int rev[MAXSIZE];
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg int a[],reg int limit,reg int flag){
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
}

int a[MAXSIZE],b[MAXSIZE];

int main(void){
	n=read();
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	getCnt(cntx),getCnt(cnty);
	reg int sumx=0,sumy=0;
	for(reg int i=1;i<=n;++i){
		sumx=add(sumx,cntx[i]),sumy=add(sumy,cnty[i]);
		a[i]=1ll*cntx[i]*fac[n-i]%mod,b[i]=1ll*cnty[i]*fac[n-i]%mod;
	}
	reg int limit=Poly::getRev(n<<1|1);
	Poly::NTT(a,limit,1),Poly::NTT(b,limit,1);
	for(reg int i=0;i<limit;++i)
		a[i]=1ll*a[i]*b[i]%mod;
	Poly::NTT(a,limit,-1);
	reg int ans=1ll*fac[n]*sumx%mod*sumy%mod;
	for(reg int i=1;i<=n;++i)
		ans=sub(ans,1ll*a[i]*invfac[n-i]%mod);
	ans=1ll*ans*invfac[n]%mod;
	printf("%d\n",ans);
	return 0;
}