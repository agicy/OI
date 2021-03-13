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

const int MAXN=1e5+5;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN<<1];
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

int n;
int a[MAXN],b[MAXN];
int x[MAXN<<1],rnk[MAXN<<1];
ll sum[MAXN<<1];

inline ll calc(reg int l,reg int r){
	return abs(sum[r]-sum[l]);
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read(),b[i]=read();
		x[i]=a[i],x[i+n]=b[i];
		rnk[i]=i,rnk[i+n]=i+n;
	}
	sort(x+1,x+2*n+1);
	x[0]=0;
	reg int tot=0;
	for(reg int i=1;i<=(n<<1);++i)
		if(i==1||x[i]!=x[i-1])
			x[++tot]=x[i];
	sum[0]=0;
	for(reg int i=1;i<=tot;i++)
		sum[i]=sum[i-1]+x[i]-x[i-1]-1;
	for(reg int i=1;i<=n;i++){
		reg int pos1=lower_bound(x+1,x+tot+1,a[i])-x,pos2=lower_bound(x+1,x+tot+1,b[i])-x;
		swap(rnk[pos1],rnk[pos2]);
	}
	reg ll ans=0;
	BIT::Init(n<<1);
	for(reg int i=tot;i>=1;--i){
		ans+=0ll+BIT::query(rnk[i])+calc(i,rnk[i]);
		BIT::update(rnk[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}