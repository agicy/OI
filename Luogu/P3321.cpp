#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline ll pow(reg ll x,reg ll exp,reg ll mod){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x%mod;
		x=x*x%mod;
		exp>>=1;
	}
	return res;
}

const int p=1004535809;
const int g=3;
const int invg=pow(g,p-2,p);

inline int GetRoot(reg int mod){
	static int fac[10000];
	reg int tot=0;
	reg ll phi=mod-1;
	for(reg int i=2;i*i<=phi;++i)
		if(phi%i==0){
			fac[++tot]=i;
			while(phi%i==0)
				phi/=i;
		}
	if(phi>1)
		fac[++tot]=phi;
	phi=mod-1;
	for(reg int i=2;i<=phi;++i){
		reg bool flag=true;
		for(reg int j=1;j<=tot;++j)
			if(pow(i,phi/fac[j],mod)==1){
				flag=false;
				break;
			}
		if(flag)
			return i;
	}
	return -1;
}

const int MAXSIZE=100000+5;

int n,m,X,S;
map<int,int> Log;
int limit,l;
int r[MAXSIZE];

struct Array{
	ll a[MAXSIZE];
	inline ll& operator[](reg int i){
		return a[i];
	}
};

inline void NTT(Array& a,reg int f){
	for(reg int i=0;i<limit;++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(reg int i=1;i<limit;i<<=1){
		reg ll w=pow(f==1?g:invg,(p-1)/(i<<1),p);
		for(reg int j=0;j<limit;j+=(i<<1)){
			reg ll e=1;
			for(reg int k=0;k<i;++k,e=(e*w)%p){
				reg ll x=a[j+k],y=e*a[j+k+i]%p;
				a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
			}
		}
	}
	if(f==-1){
		reg ll inv=pow(limit,p-2,p);
		for(reg int i=0;i<limit;++i)
			a[i]=a[i]*inv%p;
	}
	return;
}

inline Array operator*(const Array& a,const Array& b){
	static Array A,B;
	for(reg int i=0;i<limit;++i){
		A[i]=a.a[i];
		B[i]=b.a[i];
	}
	NTT(A,1),NTT(B,1);
	for(reg int i=0;i<limit;++i)
		A[i]=A[i]*B[i]%p;
	NTT(A,-1);
	Array res;
	for(reg int i=0;i<m-1;++i)
		res[i]=(A[i]+A[i+m-1])%p;
	return res;
}

Array F,H;

int main(void){
	n=read(),m=read(),X=read(),S=read();
	reg int G=GetRoot(m);
	for(reg int i=0;i<m-1;++i)
		Log[pow(G,i,m)]=i;
	for(reg int i=1;i<=S;++i){
		static int x;
		x=read()%m;
		if(x)
			++F[Log[x]];
	}
	H[Log[1]]=1;
	limit=1,l=0;
	while(limit<=2*m)
		limit<<=1,++l;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	while(n){
		if(n&1)
			H=H*F;
		F=F*F;
		n>>=1;
	}
	printf("%lld\n",H[Log[X]]);
	return 0;
}