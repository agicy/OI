#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50+5;
const int MAXP=47+1;

inline int add(reg int a,reg int b,reg int p){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b,reg int p){
	return a*b%p;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x,mod);
		x=mul(x,x,mod);
		exp>>=1;
	}
	return res;
}

int n,p;
int a[MAXN];
int t[MAXP][MAXN*MAXN];
map<pair<ll,ll>,int> M;

inline int dfs(ll m,ll k){
	if((k-1)/n>=m)
		return 0;
	if(m<=p)
		return t[m][k];
	if(m%p==0)
		return k%p?0:dfs(m/p,k/p);
	map<pair<ll,ll>,int>::iterator pt=M.find(make_pair(m,k));
	if(pt!=M.end())
		return pt->second;
	reg ll v=m%p,lim=v*n,res=k%p,ans=0,c=k/p,d=m/p;
	for(reg ll i=res;i<=lim&&i<=k;i+=p)
		ans=add(ans,mul(t[v][i],dfs(d,c--),p),p);
	return M[make_pair(m,k)]=ans;
}

int fac[MAXP],invfac[MAXP];

int main(void){
	n=read(),p=read();
	for(reg int i=0;i<=n;++i)
		a[i]=read();
	fac[0]=invfac[0]=1;
	for(reg int i=1;i<p;++i)
		fac[i]=fac[i-1]*i%p;
	invfac[p-1]=pow(fac[p-1],p-2,p);
	for(reg int i=p-2;i>=1;--i)
		invfac[i]=invfac[i+1]*(i+1)%p;
	t[0][0]=1;
	for(reg int i=1;i<=p;++i)
		for(reg int j=0;j<=n;++j)
			for(reg int k=0;k<=n*(i-1);++k)
				t[i][j+k]=add(t[i][j+k],mul(a[j],t[i-1][k],p),p);
	reg int T=read();
	while(T--){
		static ll m,k;
		m=read(),k=read();
		printf("%d\n",dfs(m,k));
	}
	return 0;
}