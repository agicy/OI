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

const int MAXR=5e4+5;
const int MAXC=5e4+5;
const int MAXN=5e4+5;

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	typedef vector<int> poly;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int pow(reg int x,reg int exp,reg int mod){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
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
	inline void NTT(reg poly& a,reg int limit,reg int type){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=pow(type==1?g:invg,(p-1)/(i<<1),p);
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
					a[j+k]=add(x,y),a[j+k+i]=sub(x,y);
				}
			}
		}
		if(type==-1){
			reg int inv=pow(limit,p-2,p);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
}

using namespace Poly;

int r,c,n;
int x[MAXN],y[MAXN];
bool visR[MAXR];
bool visC[MAXC];
bool vis[MAXR+MAXC];

int main(void){
	reg int T=read();
	for(reg int Case=1;Case<=T;++Case){
		memset(visR,false,sizeof(visR));
		memset(visC,false,sizeof(visC));
		memset(vis,false,sizeof(vis));
		r=read(),c=read(),n=read();
		poly a,b;
		for(reg int i=1;i<=n;++i){
			x[i]=r-read(),y[i]=read()-1;
			visR[x[i]]=true,visC[y[i]]=true,vis[x[i]+y[i]]=true;
		}
		a.resize(r),b.resize(c);
		for(reg int i=0;i<r;++i)
			a[i]=(!visR[i]);
		for(reg int i=0;i<c;++i)
			b[i]=(!visC[i]);
		reg int limit=getRev(r+c-1);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*b[i]%p;
		NTT(a,limit,-1);
		reg ll ans=0;
		for(reg int i=0;i<r+c-1;++i)
			if(!vis[i])
				ans+=a[i];
		printf("Case %d: %lld\n",Case,ans);
	}
	return 0;
}