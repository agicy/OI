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

const int MAXN=1e6+5;
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

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=add(unit[i],val);
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res=add(res,unit[i]);
		return res;
	}
}

namespace BIT2{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=add(unit[i],val);
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res=add(res,unit[i]);
		return res;
	}
}

int n;
int a[MAXN];
vector<int> V;

int main(void){
	n=read();
	V.resize(n);
	for(reg int i=1;i<=n;++i)
		V[i-1]=a[i]=read();
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	reg int ans=0;
	const int inv2=fpow(2,mod-2);
	BIT1::Init(V.size()),BIT2::Init(V.size());
	for(reg int i=1;i<=n;++i){
		BIT1::update(a[i],i),BIT2::update(a[i],1ll*i*(i+1)%mod);
		reg int val1=1ll*n-i+1,val2=1ll*(n-i+1)*inv2%mod,val3=1ll*(i+n)*(n-i+1)%mod*inv2%mod;
		reg int cnt1=BIT1::query(a[i]-1),cnt2=BIT2::query(a[i]-1);
		reg int cnt=sub(add(1ll*val1*cnt1%mod,1ll*val3*cnt1%mod),1ll*val2*cnt2%mod);
		ans=add(ans,1ll*cnt*V[a[i]-1]%mod);
	}
	BIT1::Init(V.size()),BIT2::Init(V.size());
	for(reg int i=n;i>=1;--i){
		BIT1::update(a[i],n-i+1),BIT2::update(a[i],1ll*(i+n)*(n-i+1)%mod);
		reg int val1=i,val2=1ll*i*(i+1)%mod*inv2%mod,val3=1ll*i*inv2%mod;
		reg int cnt1=BIT1::query(a[i]),cnt2=BIT2::query(a[i]);
		reg int cnt=sub(add(1ll*val1*cnt1%mod,1ll*val3*cnt2%mod),1ll*val2*cnt1%mod);
		ans=add(ans,1ll*cnt*V[a[i]-1]%mod);
	}
	printf("%d\n",ans);
	return 0;
}