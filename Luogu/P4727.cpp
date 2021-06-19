#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int mod=997;

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
	inline modInt operator-(void){
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

const int MAXN=60+5;

int n;
modInt fac[MAXN],invfac[MAXN],inv[MAXN];
modInt ans;
int Gcd[MAXN][MAXN];

inline void solve(const vector<int>& b){
	static int cnt[MAXN];
	for(int x:b)
		++cnt[x];
	reg int sum=0;
	for(reg int i=0,siz=b.size();i<siz;++i)
		for(reg int j=0;j<i;++j)
			sum+=Gcd[b[i]][b[j]];
	for(reg int i=0,siz=b.size();i<siz;++i)
		sum+=b[i]>>1;
	modInt pod=1;
	for(int x:b)
		pod*=inv[x];
	for(int x:b)
		pod*=invfac[cnt[x]],cnt[x]=0;
	ans+=fpow(2,sum)*pod;
	return;
}

inline void dfs(vector<int> V,reg int las,reg int res){
	if(!res){
		solve(V);
		return;
	}
	for(int i=las;i<=res;++i){
		V.push_back(i);
		dfs(V,i,res-i);
		V.pop_back();
	}
	return;
}

int main(void){
	scanf("%d",&n);
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	for(reg int i=1;i<=n;++i)
		inv[i]=invfac[i]*fac[i-1];
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			Gcd[i][j]=gcd(i,j);
	dfs({},1,n);
	printf("%d\n",ans.x);
	return 0;
}