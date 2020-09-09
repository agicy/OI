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

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	if(sum>=p)
		return sum-p;
	else if(sum<0)
		return sum+p;
	else
		return sum;
}

inline int mul(reg int a,reg int b){
	reg int res=1ll*a*b%p;
	return res<0?-res:res;
}

int n;

namespace ST{
	bool Init_ST;
	int Lg[MAXN];
	int val[MAXN];
	int f[MAXN][MAXLOG2N];
	inline void InitLg(reg int n){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		Init_ST=true;
		return;
	}
	inline void Init(reg int n,reg int a[]){
		if(!Init_ST)
			InitLg(n);
		for(reg int i=1;i<=n;++i)
			val[i]=a[i];
		for(reg int i=1;i<=n;++i)
			f[i][0]=i;
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i){
				reg int posl=f[i][j-1],posr=f[i+(1<<(j-1))][j-1];
				if(val[posl]>val[posr])
					f[i][j]=posl;
				else
					f[i][j]=posr;
			}
		return;
	}
	inline int query_pMax(reg int l,reg int r){
		reg int k=Lg[r-l+1],posl=f[l][k],posr=f[r-(1<<k)+1][k];
		if(val[posl]>val[posr])
			return posl;
		else
			return posr;
	}
}

inline void add(reg int a[],reg int l,reg int r,reg int val){
	a[l]=add(a[l],val),a[r]=add(a[r],-val);
	return;
}

int K[MAXN],B[MAXN];

inline void solve(reg int l,reg int r,reg int val[]){
	if(l>r)
		return;
	reg int pos=ST::query_pMax(l,r);
	int a=pos-l+1,b=r-pos+1;
	if(a>b)
		swap(a,b);
	add(K,1,a,val[pos]),add(B,a,b,mul(a,val[pos]));
	add(K,b,a+b,-val[pos]),add(B,b,a+b,mul(a+b,val[pos]));
	solve(l,pos-1,val),solve(pos+1,r,val);
	return;
}

int ans[MAXN];

inline void solve(reg int n,reg int val[]){
	memset(K,0,sizeof(K)),memset(B,0,sizeof(B));
	ST::Init(n,val);
	solve(1,n,val);
	for(reg int i=1;i<=n;++i){
		K[i]=add(K[i],K[i-1]),B[i]=add(B[i],B[i-1]);
		ans[i]=mul(ans[i],add(mul(K[i],i),B[i]));
	}
	return;
}

int a[MAXN],b[MAXN];

int main(void){
	n=read();
	fill(ans+1,ans+n+1,1);
	for(reg int i=1;i<=n;++i)
		a[i]=read()+i;
	solve(n,a);
	for(reg int i=1;i<=n;++i)
		b[i]=read()+i;
	solve(n,b);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}