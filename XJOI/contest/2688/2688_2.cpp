#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline int lcm(reg int a,reg int b){
	return a/gcd(a,b)*b;
}

const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		//assert(0<=x&&x<mod);
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

const int MAXN=50+5;

int n,w1,w2,w3;
modInt fac[MAXN],invfac[MAXN],inv[MAXN];
int k2[MAXN][MAXN];
int k3[MAXN][MAXN][MAXN];
modInt ans;
int cnt[MAXN];

bool ed;

inline void solve(const vector<int>& b){
	for(int x:b)
		++cnt[x];
	vector<pair<int,int>> V;
	for(int x:b)
		if(cnt[x])
			V.push_back(make_pair(x,cnt[x])),cnt[x]=0;
	reg int cnt1=b.size();
	reg int cnt2=0;
	for(pair<int,int> i:V)
		for(pair<int,int> j:V)
			if(i.first==j.first)
				cnt2+=(i.first-1)*i.second+i.first*i.second*(i.second-1);
			else
				cnt2+=k2[i.first][j.first]*i.second*j.second;
	reg int cnt3=0;
	for(pair<int,int> i:V)
		for(pair<int,int> j:V)
			if(i.first==j.first)
				for(pair<int,int> k:V)
					cnt3+=(i.first-1)*k2[i.first][k.first]*i.second*k.second+k3[i.first][j.first][k.first]*i.second*(i.second-1)*k.second;
			else
				for(pair<int,int> k:V)
					cnt3+=k3[i.first][j.first][k.first]*i.second*j.second*k.second;
	modInt pod=1;
	for(pair<int,int> i:V)
		pod*=fpow(inv[i.first],i.second)*invfac[i.second];
	ans+=pod*fpow(w1,cnt1)*fpow(w2,cnt2)*fpow(w3,cnt3);
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
	scanf("%d%d%d%d",&n,&w1,&w2,&w3);
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
			k2[i][j]=gcd(i,j);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			for(reg int k=1;k<=n;++k)
				k3[i][j][k]=k2[i][j]*gcd(lcm(i,j),k);
	dfs({},1,n);
	printf("%d\n",ans.x);
	return 0;
}