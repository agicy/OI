#pragma GCC optimize("Ofast")
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

const int MAXN=500+5;
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

const modInt g=3;
const modInt invg=332748118;
const modInt zero(0);

namespace Poly{
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
	typedef vector<modInt> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			modInt w=fpow(flag==1?g:invg,(mod-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				modInt e=1;
				for(reg int k=0;k<i;++k,e*=w){
					modInt x=a[j+k],y=e*a[i+j+k];
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
			}
		}
		if(flag==-1){
			modInt inv=fpow(limit,mod-2);
			for(reg int i=0;i<limit;++i)
				a[i]*=inv;
		}
		return;
	}
}

using namespace Poly;

int n,k;
vector<int> G[MAXN];
modInt fac[MAXN],invfac[MAXN],inv[MAXN];
int siz[MAXN];
modInt f[MAXN][MAXN];
modInt x,w;
modInt tmp[MAXN];

inline void getFac(reg modInt f[],reg int siz){
	const int BLK=8;
	reg int tot=(siz+1)/BLK,res=(siz+1)%BLK,ptr=0;
	while(tot--){
		f[ptr]*=fac[ptr],f[ptr]*=fac[siz-ptr];
		f[ptr+1]*=fac[ptr+1],f[ptr+1]*=fac[siz-ptr-1];
		f[ptr+2]*=fac[ptr+2],f[ptr+2]*=fac[siz-ptr-2];
		f[ptr+3]*=fac[ptr+3],f[ptr+3]*=fac[siz-ptr-3];
		f[ptr+4]*=fac[ptr+4],f[ptr+4]*=fac[siz-ptr-4];
		f[ptr+5]*=fac[ptr+5],f[ptr+5]*=fac[siz-ptr-5];
		f[ptr+6]*=fac[ptr+6],f[ptr+6]*=fac[siz-ptr-6];
		f[ptr+7]*=fac[ptr+7],f[ptr+7]*=fac[siz-ptr-7];
		ptr+=BLK;
	}
	switch(res){
		case 7:f[ptr+6]*=fac[ptr+6],f[ptr+6]*=fac[siz-ptr-6];
		case 6:f[ptr+5]*=fac[ptr+5],f[ptr+5]*=fac[siz-ptr-5];
		case 5:f[ptr+4]*=fac[ptr+4],f[ptr+4]*=fac[siz-ptr-4];
		case 4:f[ptr+3]*=fac[ptr+3],f[ptr+3]*=fac[siz-ptr-3];
		case 3:f[ptr+2]*=fac[ptr+2],f[ptr+2]*=fac[siz-ptr-2];
		case 2:f[ptr+1]*=fac[ptr+1],f[ptr+1]*=fac[siz-ptr-1];
		case 1:f[ptr]*=fac[ptr],f[ptr]*=fac[siz-ptr];
		case 0:;
	}
	return;
}

inline void getInvfac(reg modInt f[],reg int siz){
	const int BLK=8;
	reg int tot=(siz+1)/BLK,res=(siz+1)%BLK,ptr=0;
	while(tot--){
		f[ptr]*=invfac[ptr],f[ptr]*=invfac[siz-ptr];
		f[ptr+1]*=invfac[ptr+1],f[ptr+1]*=invfac[siz-ptr-1];
		f[ptr+2]*=invfac[ptr+2],f[ptr+2]*=invfac[siz-ptr-2];
		f[ptr+3]*=invfac[ptr+3],f[ptr+3]*=invfac[siz-ptr-3];
		f[ptr+4]*=invfac[ptr+4],f[ptr+4]*=invfac[siz-ptr-4];
		f[ptr+5]*=invfac[ptr+5],f[ptr+5]*=invfac[siz-ptr-5];
		f[ptr+6]*=invfac[ptr+6],f[ptr+6]*=invfac[siz-ptr-6];
		f[ptr+7]*=invfac[ptr+7],f[ptr+7]*=invfac[siz-ptr-7];
		ptr+=BLK;
	}
	switch(res){
		case 7:f[ptr+6]*=invfac[ptr+6],f[ptr+6]*=invfac[siz-ptr-6];
		case 6:f[ptr+5]*=invfac[ptr+5],f[ptr+5]*=invfac[siz-ptr-5];
		case 5:f[ptr+4]*=invfac[ptr+4],f[ptr+4]*=invfac[siz-ptr-4];
		case 4:f[ptr+3]*=invfac[ptr+3],f[ptr+3]*=invfac[siz-ptr-3];
		case 3:f[ptr+2]*=invfac[ptr+2],f[ptr+2]*=invfac[siz-ptr-2];
		case 2:f[ptr+1]*=invfac[ptr+1],f[ptr+1]*=invfac[siz-ptr-1];
		case 1:f[ptr]*=invfac[ptr],f[ptr]*=invfac[siz-ptr];
		case 0:;
	}
	return;
}

inline modInt dfs(reg int u,reg int father){
	siz[u]=0,f[u][0]=1;
	for(int v:G[u])
		if(v!=father){
			dfs(v,u);
			for(reg int i=0;i<=siz[u];++i)
				tmp[i]=f[u][i],f[u][i]=zero;
			fill(f[u]+siz[u]+1,f[u]+siz[u]+siz[v]+1,zero);
			for(reg int i=0;i<=siz[u];++i){
				const int BLK=8;
				reg int tot=(siz[v]+1)/BLK,res=(siz[v]+1)%BLK,ptr=0;
				while(tot--){
					f[u][i+ptr]+=tmp[i]*f[v][ptr];
					f[u][i+ptr+1]+=tmp[i]*f[v][ptr+1];
					f[u][i+ptr+2]+=tmp[i]*f[v][ptr+2];
					f[u][i+ptr+3]+=tmp[i]*f[v][ptr+3];
					f[u][i+ptr+4]+=tmp[i]*f[v][ptr+4];
					f[u][i+ptr+5]+=tmp[i]*f[v][ptr+5];
					f[u][i+ptr+6]+=tmp[i]*f[v][ptr+6];
					f[u][i+ptr+7]+=tmp[i]*f[v][ptr+7];
					ptr+=BLK;
				}
				switch(res){
					case 7:f[u][i+ptr+6]+=tmp[i]*f[v][ptr+6];
					case 6:f[u][i+ptr+5]+=tmp[i]*f[v][ptr+5];
					case 5:f[u][i+ptr+4]+=tmp[i]*f[v][ptr+4];
					case 4:f[u][i+ptr+3]+=tmp[i]*f[v][ptr+3];
					case 3:f[u][i+ptr+2]+=tmp[i]*f[v][ptr+2];
					case 2:f[u][i+ptr+1]+=tmp[i]*f[v][ptr+1];
					case 1:f[u][i+ptr]+=tmp[i]*f[v][ptr];
					case 0:;
				}
			}
			siz[u]+=siz[v];
		}
	modInt res(0);
	if(!siz[u])
		siz[u]=1,f[u][0]=modInt(1)-x,f[u][1]=x;
	else if(u!=1){
		++siz[u],f[u][siz[u]]=0;
		static modInt tmp[MAXN];
		for(reg int i=0;i<=siz[u];++i)
			tmp[i]=f[u][i];
		for(reg int i=0;i<siz[u];++i){
			tmp[siz[u]]+=f[u][i]*x*inv[siz[u]-i];
			tmp[i]-=f[u][i]*x*inv[siz[u]-i];
		}
		for(reg int i=0;i<=siz[u];++i)
			f[u][i]=tmp[i];
	}
	else{
		for(reg int i=0;i<=siz[u];++i)
			res+=f[u][i]*inv[n-i];
		res=res*x;
	}
	return res;
}

int main(void){
	n=read(),k=read();
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	invfac[n]=fpow(fac[n],mod-2);
	for(reg int i=n-1;i>=0;--i)
		invfac[i]=invfac[i+1]*(i+1);
	inv[0]=1;
	for(reg int i=1;i<=n;++i)
		inv[i]=fac[i-1]*invfac[i];
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	reg int limit=getRev(n+1);
	poly res;
	res.resize(limit,zero);
	x=1,w=fpow(g,(mod-1)/limit);
	for(reg int i=0;i<limit;++i)
		res[i]=dfs(1,0),x=x*w;
	NTT(res,limit,-1);
	modInt ans=0;
	for(reg int i=0;i<=k;++i)
		ans+=res[i];
	printf("%d\n",ans.x);
	//fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}