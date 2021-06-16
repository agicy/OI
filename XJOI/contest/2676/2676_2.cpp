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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int mod=1e9+7;

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

const int MAXN=100;
const int MAXM=18;

int n,m;
modInt fac[MAXN+1],invfac[MAXN+1];
modInt cnt[MAXN+1][MAXN+1];
bitset<MAXN> S[MAXM<<1],nS[MAXM<<1];

inline modInt binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return fac[n]*invfac[m]*invfac[n-m];
}

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			for(reg int k=1;k<=min(i,j);++k)
				cnt[i][j]+=binom(i,k)*binom(j,k);
	return;
}

int Cnt;
modInt ans;

inline vector<int> merge(vector<int> a,vector<int> b){
	return 
}

inline void dfs(reg bool flag,reg int las,bitset<MAXN> p,bitset<MAXN> np,vector<int> V){
	if(!p.count()||!np.count())
		return;
	++Cnt;
	if(las>=0){
		if(flag)
			ans+=cnt[p.count()][np.count()];
		else
			ans-=cnt[p.count()][np.count()];
	}
	for(reg int i=las+1;i<m;++i)
		dfs(!flag,i,p&S[i],np&nS[i]);
	return;
}

bool ed;

int main(void){
	n=read(),m=read();
	Init(n);
	bitset<MAXN> U;
	for(reg int i=0;i<n;++i)
		U[i]=true;
	for(reg int i=0;i<m;++i){
		reg int s=read();
		for(reg int j=0;j<s;++j)
			S[i][read()-1]=true;
		nS[i]=S[i]^U;
		nS[i+m]=S[i],S[i+m]=nS[i];
	}
	bitset<MAXN> p,np;
	p.set(),np.set();
	m<<=1;
	dfs(0,-1,p,np);
	modInt inv2=fpow(2,mod-2);
	printf("%d\n",(ans*inv2).x);

	fprintf(stderr,"Cnt=%d\n",Cnt);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}