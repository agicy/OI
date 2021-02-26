#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

namespace Poly{
	const int mod=1e9+9;
	const int B=sqrt(mod);
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
	const long double pi=acos(-1.0);
	struct Complex{
		long double x,y;
		inline Complex(reg long double x=0,reg long double y=0):x(x),y(y){return;}
		inline Complex operator+(const Complex& a)const{return Complex(x+a.x,y+a.y);}
		inline Complex operator-(const Complex& a)const{return Complex(x-a.x,y-a.y);}
		inline Complex operator*(const Complex& a)const{return Complex(x*a.x-y*a.y,x*a.y+y*a.x);}
	};
	int tot;
	map<int,int> M;
	vector<int> back[19];
	vector<int> *rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n) limit<<=1,++l;
		if(!M[limit]){
			M[limit]=++tot;
			back[tot].resize(limit);
			for(reg int i=0;i<limit;++i)
				back[tot][i]=(back[tot][i>>1]>>1)|((i&1)<<(l-1));
			rev=&back[tot];
		}
		else
			rev=&back[M[limit]];
		return limit;
	}
	inline void FFT(reg vector<Complex>& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<(*rev)[i])
				swap(a[i],a[(*rev)[i]]);
		for(reg int i=1;i<limit;i<<=1){
			Complex w(cos(pi/i),flag*sin(pi/i));
			for(reg int j=0;j<limit;j+=(i<<1)){
				Complex e(1,0);
				for(reg int k=0;k<i;++k,e=e*w){
					Complex x=a[j+k],y=a[i+j+k]*e;
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1)
			for(reg int i=0;i<limit;++i)
				a[i].x/=limit;
		return;
	}
	typedef vector<int> poly;
	inline bool check(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			if(a[i]<0||a[i]>=mod)
				return false;
		return true;
	}
	inline poly add(poly a,poly b){
		reg int s=max(a.size(),b.size());
		a.resize(s),b.resize(s);
		for(reg int i=0;i<s;++i)
			a[i]=add(a[i],b[i]);
		return a;
	}
	inline poly mul(poly a,poly b){
		vector<Complex> pA,qA,pB,qB;
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		pA.resize(limit),qA.resize(limit),pB.resize(limit),qB.resize(limit);
		for(reg int i=0,siz=a.size();i<siz;++i)
			pA[i]=Complex(a[i]/B,0),qA[i]=Complex(a[i]%B,0);
		for(reg int i=0,siz=b.size();i<siz;++i)
			pB[i]=Complex(b[i]/B,0),qB[i]=Complex(b[i]%B,0);
		FFT(pA,limit,1),FFT(qA,limit,1),FFT(pB,limit,1),FFT(qB,limit,1);
		vector<Complex> p1,p2,p3;
		p1.resize(limit),p2.resize(limit),p3.resize(limit);
		for(reg int i=0;i<limit;++i){
			p1[i]=pA[i]*pB[i];
			p2[i]=pA[i]*qB[i]+qA[i]*pB[i];
			p3[i]=qA[i]*qB[i];
		}
		FFT(p1,limit,-1),FFT(p2,limit,-1),FFT(p3,limit,-1);
		poly res;
		res.resize(s);
		for(reg int i=0;i<s;++i)
			res[i]=add(((ll)(p1[i].x+0.5)%mod*B%mod*B%mod+mod)%mod,add(((ll)(p2[i].x+0.5)%mod*B%mod+mod)%mod,(1ll*(ll)(p3[i].x+0.5)%mod+mod)%mod));
		return res;
	}
}

using namespace Poly;

const int MAXN=2e5+5;
const int MAXK=2e5+5;

int n,k;
int fac[MAXK],invfac[MAXK];
int ans1,ans2,ans3;
int siz[MAXN],f[MAXN],sumf[MAXN];
vector<pair<int,int>/**/> V[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	return;
}

poly p[MAXN][2];

inline void solve(reg int l,reg int r,const int& rt){
	if(l==r){
		p[l][0].resize(2),p[l][1].resize(2);
		p[l][0][0]=1,p[l][0][1]=V[rt][l].second;
		p[l][1][0]=add(f[V[rt][l].first],sumf[V[rt][l].first]),p[l][1][1]=1ll*add(f[V[rt][l].first],sumf[V[rt][l].first])*(n-siz[rt])%mod;
		return;
	}
	reg int mid=(l+r)>>1;
	solve(l,mid,rt),solve(mid+1,r,rt);
	poly F=mul(p[l][0],p[mid+1][0]),G=add(mul(p[l][0],p[mid+1][1]),mul(p[mid+1][0],p[l][1]));
	p[l][0]=F,p[l][1]=G;
	return;
}

inline void dfs(reg int u,int father){
	siz[u]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
			V[u].push_back(make_pair(v,siz[v]));
			sumf[u]=add(sumf[u],add(sumf[v],f[v]));
		}
	}
	if(V[u].empty()) V[u].push_back(make_pair(0,0));
	solve(0,V[u].size()-1,u);
	for(reg int i=0,siz=p[0][0].size();i<=k&&i<siz;++i)
		f[u]=add(f[u],1ll*p[0][0][i]*fac[k]%mod*invfac[k-i]%mod);
	ans1=add(ans1,f[u]),ans2=add(ans2,1ll*f[u]*f[u]%mod),ans3=sub(ans3,1ll*f[u]*sumf[u]%mod);
	for(reg int i=0,siz=p[0][1].size();i<=k&&i<siz;++i)
		ans3=add(ans3,1ll*p[0][1][i]*fac[k]%mod*invfac[k-i]%mod);
	return;
}

int main(void){
	n=read(),k=read();
	if(k==1){
		reg int ans=1ll*n*(n-1)%mod*fpow(2,mod-2)%mod;
		printf("%d\n",ans);
		return 0;
	}
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	Init(k);
	dfs(1,0);
	printf("%d\n",add(ans3,1ll*sub(1ll*ans1*ans1%mod,ans2)*fpow(2,mod-2)%mod));
	return 0;
}