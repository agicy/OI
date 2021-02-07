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

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXK=5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,k;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

ll dp[1<<MAXK][MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int id;
		ll val;
		#define id(x) unit[(x)].id
		#define val(x) unit[(x)].val
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		if(val(lson)<val(rson))
			id(k)=id(lson),val(k)=val(lson);
		else
			id(k)=id(rson),val(k)=val(rson);
		return;
	}
	int limit;
	inline void build(reg int n){
		limit=1;
		while(limit<n)
			limit<<=1;
		for(reg int i=limit+1;i<=limit+n;++i)
			
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg ll dis[]){
		if(l==r){
			id(k)=l,val(k)=dis[l];
			return;
		}
		build(lson,l,mid,dis),build(rson,mid+1,r,dis);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg ll Val){
		if(l==r){
			val(k)=Val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,Val);
		else
			update(rson,mid+1,r,pos,Val);
		pushup(k);
		return;
	}
	inline int query(reg int k){
		return id(k);
	}
	inline bool check(reg int k){
		return val(k)!=inf;
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	memset(dp,0x3f,sizeof(dp));
	n=read(),k=read(),m=read();
	for(reg int i=0;i<k;++i)
		dp[1<<i][read()-1]=0;
	for(reg int i=0;i<m;++i){
		static int a,b,c;
		a=read()-1,b=read()-1,c=read();
		Add_Edge(a,b,c),Add_Edge(b,a,c);
	}
	for(reg int S=1;S<(1<<k);++S){
		for(reg int i=0;i<n;++i)
			for(reg int sub=S&(S-1);sub;sub=S&(sub-1))
				dp[S][i]=min(dp[S][i],dp[sub][i]+dp[S^sub][i]);
		SegmentTree::build(1,0,n-1,dp[S]);
		while(SegmentTree::check(1)){
			reg int u=SegmentTree::query(1);
			SegmentTree::update(1,0,n-1,u,inf);
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(dp[S][v]>dp[S][u]+w[i]){
					dp[S][v]=dp[S][u]+w[i];
					SegmentTree::update(1,0,n-1,v,dp[S][v]);
				}
			}
		}
	}
	reg ll ans=inf;
	for(reg int i=0;i<n;++i)
		ans=min(ans,dp[(1<<k)-1][i]);
	printf("%lld\n",ans);
	return 0;
}