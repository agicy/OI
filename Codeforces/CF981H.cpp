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
	typedef vector<int> poly;
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	inline void NTT(reg poly& a,reg int limit,reg int flag){
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
	inline poly add(poly a,poly b){
		reg int s=max(a.size(),b.size());
		a.resize(s),b.resize(s);
		for(reg int i=0;i<s;++i)
			a[i]=add(a[i],b[i]);
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
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[n]=fpow(fac[n],p-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	return;
}

inline pair<poly,poly> solve(reg int l,reg int r,reg int rt){
	if(l==r){
		poly F,G;
		F.resize(2),F[0]=1,F[1]=V[rt][l].second;
		G.resize(2),G[0]=add(f[V[rt][l].first],sumf[V[rt][l].first]),G[1]=1ll*add(f[V[rt][l].first],sumf[V[rt][l].first])*(n-siz[rt])%p;
		return make_pair(F,G);
	}
	reg int mid=(l+r)>>1;
	pair<poly,poly> lef=solve(l,mid,rt),rig=solve(mid+1,r,rt);
	poly F=mul(lef.first,rig.first),G=add(mul(lef.first,rig.second),mul(rig.first,lef.second));
	return make_pair(F,G);
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
	pair<poly,poly> P=solve(0,V[u].size()-1,u);
	for(reg int i=0,siz=P.first.size();i<=k&&i<siz;++i)
		f[u]=add(f[u],1ll*P.first[i]*fac[k]%p*invfac[k-i]%p);
	ans1=add(ans1,f[u]),ans2=add(ans2,1ll*f[u]*f[u]%p),ans3=sub(ans3,1ll*f[u]*sumf[u]%p);
	for(reg int i=0,siz=P.second.size();i<=k&&i<siz;++i)
		ans3=add(ans3,1ll*P.second[i]*fac[k]%p*invfac[k-i]%p);
	return;
}

int main(void){
	n=read(),k=read();
	if(k==1){
		reg int ans=1ll*n*(n-1)%p*fpow(2,p-2)%p;
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
	printf("%d\n",add(ans3,1ll*sub(1ll*ans1*ans1%p,ans2)*fpow(2,p-2)%p));
	return 0;
}