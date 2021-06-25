#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

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

const modInt inv2=fpow(2,mod-2);

ll n;
int a,b,c,d;

const int MAXS=1e7+5;
const int S=1e7;

bool vis[MAXS];
int tot,prime[MAXS];
modInt mu[MAXS];
modInt Smu[MAXS];

inline void Init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i,mu[i]=-modInt(1);
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(reg int i=1;i<=n;++i)
		Smu[i]=Smu[i-1]+mu[i];
	return;
}

unordered_map<ll,modInt> MSmu;

inline modInt getSmu(ll n){
	if(n<=S)
		return Smu[n];
	if(MSmu[n].x)
		return MSmu[n];
	modInt ans=1;
	for(reg ll l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		ans-=modInt((r-l+1)%mod)*getSmu(n/l);
	}
	return MSmu[n]=ans;
}

inline modInt f(reg ll a,reg ll b,reg ll c,reg ll n){
	if((a*n+b)/c==0)
		return 0;
	if(!a)
		return modInt((n+1)%mod)*modInt((b/c)%mod);
	if(!n)
		return (b/c)%mod;
	if(a>=c||b>=c)
		return f(a%c,b%c,c,n)+modInt((a/c)%mod)*modInt(n%mod)*modInt((n+1)%mod)*inv2+modInt((b/c)%mod)*modInt((n+1)%mod);
	reg ll m=(a*n+b)/c;
	return modInt(n%mod)*modInt(m%mod)-f(c,c-b-1,a,m-1);
}

inline modInt getSum(reg ll n){
	modInt part1=n%mod;
	modInt part2=f(c,0,d,n);
	modInt part3=f(a,b-1,b,n);
	return part1+part2-part3;
}

bool ed;

int main(void){
	Init(S);
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%lld%d%d%d%d",&n,&a,&b,&c,&d);
		modInt ans=0;
		for(reg ll lef=1,rig;lef<=n;lef=rig+1){
			rig=n/(n/lef);
			ans+=(getSmu(rig)-getSmu(lef-1))*getSum(n/lef);
		}
		printf("%d\n",ans.x);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}