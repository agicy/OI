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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2.5e4+5;
const int MAXK=25+5;

int n,k;
int a[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int l=1,r=0,len=0;
ll cost;

inline void add_front(reg int x){
	cost+=len-BIT::query(x);
	BIT::update(x,1);
	++len;
	return;
}

inline void add_back(reg int x){
	cost+=BIT::query(x);
	BIT::update(x,1);
	++len;
	return;
}

inline void del_front(reg int x){
	--len;
	BIT::update(x,-1);
	cost-=len-BIT::query(x);
	return;
}

inline void del_back(reg int x){
	--len;
	BIT::update(x,-1);
	cost-=BIT::query(x);
	return;
}

inline ll getVal(reg int L,reg int R){
	while(l<L) del_front(a[l++]);
	while(l>L) add_front(a[--l]);
	while(r<R) add_back(a[++r]);
	while(r>R) del_back(a[r--]);
	return cost;
}

inline void solve(reg ll f[],reg int L,reg int R,reg ll g[],reg int l,reg int r){
	if(L>R||l>r)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			f[i]=g[l-1]+getVal(l,i);
		return;
	}
	reg int mid=(L+R)>>1,ptr=l;
	for(reg int i=l;i<=min(r,mid);++i)
		if(f[mid]>g[i-1]+getVal(i,mid))
			ptr=i,f[mid]=g[i-1]+getVal(i,mid);
	solve(f,L,mid-1,g,l,ptr),solve(f,mid+1,R,g,ptr,r);
	return;
}

ll dp[MAXK][MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	BIT::Init(n);
	memset(dp[0],0x3f,sizeof(dp[0]));
	dp[0][0]=0;
	for(reg int i=1;i<=k;++i){
		memset(dp[i&1],0x3f,sizeof(dp[i&1]));
		solve(dp[i&1],1,n,dp[(i&1)^1],1,n);
	}
	printf("%lld\n",dp[k&1][n]);
	return 0;
}