#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)

const int p=1004535809;
const int invg=334845270;
const int g=3;

static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=(10ll*res+ch-'0')%p,ch=getchar();
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

inline int inv(reg int x,reg int p){
	return pow(x,p-2,p);
}

const int MAXN=100000+5;

int n,m,a[MAXN<<2],b[MAXN<<2];
int limit,r[MAXN<<2];

inline void Init(reg int n){
	limit=1;
	reg int l=0;
	while(limit<=n)
		limit<<=1,++l;
	for(reg int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	return;
}

inline void NTT(reg int a[],reg int type){
	for(reg int i=0;i<limit;++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(reg int i=1;i<limit;i<<=1){
		reg int w=pow(type==1?g:invg,(p-1)/(i<<1),p);
		for(reg int j=0;j<limit;j+=(i<<1)){
			reg int e=1;
			for(reg int k=0;k<i;++k,e=1ll*e*w%p){
				reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
				a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
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

int type;

int main(void){
	n=read(),m=read(),type=read();
	for(reg int i=1;i<=n;++i)
		a[i-1]=read();
	b[0]=1;
	if(!type)
		for(reg int i=1;i<=n;++i)
			b[i]=1ll*b[i-1]*(m+i-1)%p*inv(i,p)%p;
	else
		for(reg int i=1;i<=n;++i)
			b[i]=(-1ll*b[i-1]*((m-i+1+p)%p)%p*inv(i,p)%p+p)%p;
	Init(n<<1);
	NTT(a,1),NTT(b,1);
	for(reg int i=0;i<limit;++i)
		a[i]=1ll*a[i]*b[i]%p;
	NTT(a,-1);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i-1],i==n?'\n':' ');
	return 0 ;
}