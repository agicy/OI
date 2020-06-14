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
	while('0'<=ch&&ch<='9')res=res*10+ch-'0',ch=getchar();
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

const int p=998244353;
const int g=3;
const int invg=pow(3,p-2,p);

typedef vector<int> Poly;

const int MAXN=100000+5;

int r[MAXN<<3];

inline int GetLimit(reg int len){
	reg int limit=1,l=0;
	while(limit<len)
		limit<<=1,++l;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	return limit;
}

inline void NTT(Poly &poly,reg int f,reg int limit){
	for(reg int i=0;i<limit;++i)
		if(i<r[i])
			swap(poly[i],poly[r[i]]);
	for(reg int i=1;i<limit;i<<=1){
		reg int w=pow(f==1?g:invg,(p-1)/(i<<1),p);
		for(reg int j=0;j<limit;j+=(i<<1)){
			reg int e=1;
			for(reg int k=0;k<i;++k,e=1ll*e*w%p){
				reg int x=poly[j+k],y=1ll*e*poly[j+k+i]%p;
				poly[j+k]=(x+y)%p,poly[j+k+i]=(x-y+p)%p;
			}
		}
	}
	if(f==-1){
		reg int inv=pow(limit,p-2,p);
		for(reg int i=0;i<limit;++i)
			poly[i]=1ll*poly[i]*inv%p;
	}
	return;
}

inline Poly operator*(Poly a,Poly b){
	reg int size=a.size()+b.size()-1;
	reg int limit=GetLimit(size);
	a.resize(limit),b.resize(limit);
	NTT(a,1,limit),NTT(b,1,limit);
	for(reg int i=0;i<limit;++i)
		a[i]=1ll*a[i]*b[i]%p;
	NTT(a,-1,limit);
	return a;
}

int n,k;
int a[MAXN];

inline Poly Solve(reg int l,reg int r){
	if(l==r){
		Poly poly;
		poly.resize(2);
		poly[0]=a[l],poly[1]=p-1;
		return poly;
	}
	reg int mid=(l+r)>>1;
	Poly L=Solve(l,mid),R=Solve(mid+1,r);
	reg int size=L.size()+R.size()-1;
	L=L*R;
	L.resize(size);
	return L;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int pre=1;
	for(reg int i=1;i<=n;++i)
		pre=1ll*pre*a[i]%p;
	reg int ans=0;
	Poly poly=Solve(1,n);
	reg int mul=1,invn=pow(n,p-2,p);
	for(reg int i=0;i<=min(n,k);++i){
		ans=(ans+1ll*poly[i]*mul%p)%p;
		mul=1ll*mul*(k-i)%p*invn%p;
	}
	printf("%d\n",(pre-ans+p)%p);
	return 0;
}