#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
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

inline int inv(int x,reg int mod){
	return pow(x,mod-2,mod);
}

const int mod[3]={998244353,1004535809,469762049};
const int g[3]={3,3,3};
const int invg[3]={inv(g[0],mod[0]),inv(g[1],mod[1]),inv(g[2],mod[2])};

const int MAXSIZE=1000000+5;

int n,m,p;

int limit;
int r[MAXSIZE];

inline void NTT(reg int a[],reg int f,reg int p,reg int g){
	reg int invg=pow(g,p-2,p);
	for(reg int i=0;i<limit;++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(reg int i=1;i<limit;i<<=1){
		reg int w=pow(f==1?g:invg,(p-1)/(i<<1),p);
		for(reg int j=0;j<limit;j+=(i<<1)){
			reg int e=1;
			for(reg int k=0;k<i;++k,e=1ll*e*w%p){
				reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
				a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
			}
		}
	}
	if(f==-1){
		reg int inv=pow(limit,p-2,p);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*inv%p;
	}
	return;
}

int a[MAXSIZE],b[MAXSIZE];
int s[3][MAXSIZE];

inline void Solve(reg int id){
	static int ta[MAXSIZE],tb[MAXSIZE];
	memcpy(ta,a,sizeof(a));
	memcpy(tb,b,sizeof(b));
	NTT(ta,1,mod[id],g[id]),NTT(tb,1,mod[id],g[id]);
	for(reg int i=0;i<limit;++i)
		ta[i]=1ll*ta[i]*tb[i]%mod[id];
	NTT(ta,-1,mod[id],g[id]);
	for(reg int i=0;i<=n+m;++i)
		s[id][i]=ta[i];
	return;
}

ll M=mod[0]*mod[1];
ll ans[MAXSIZE];

inline ll mul(reg ll a,reg ll b,reg ll mod){
	reg ll res=0;
	while(b){
		if(b&1)
			res=(res+a)%mod;
		a=(a<<1)%mod;
		b>>=1;
	}
	return res;
}

inline void CRT(void){
	reg ll M=mod[0]*mod[1];
	for(reg int i=0;i<limit;++i){
		reg ll tmp=0;
		tmp=(tmp+mul(s[0][i]*mod[1]%M,pow(mod[1],mod[0]-2,mod[0]),M))%M;
		tmp=(tmp+mul(s[1][i]*mod[0]%M,pow(mod[0],mod[1]-2,mod[1]),M))%M;
		s[1][i]=tmp;
	}
	for(reg int i=0;i<limit;++i){
		reg ll tmp=(s[2][i]-s[1][i]%mod[2]+mod[2])%mod[2]*pow(M%mod[2],mod[2]-2,mod[2])%mod[2];
		ans[i]=(M%p*tmp%p+s[1][i]%p)%p;
	}
	return;
}

signed main(void){
	n=read(),m=read(),p=read();
	for(reg int i=0;i<=n;++i)
		a[i]=read();
	for(reg int i=0;i<=m;++i)
		b[i]=read();
	reg int l=0;
	limit=1;
	while(limit<=n+m)
		limit<<=1,++l;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	for(reg int i=0;i<3;++i)
		Solve(i);
	CRT();
	for(reg int i=0;i<=n+m;++i)
		printf("%lld%c",ans[i],i==n+m?'\n':' ');
	return 0;
}