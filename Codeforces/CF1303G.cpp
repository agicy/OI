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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1.5e5+5;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN];
vector<int> G[MAXN];

int rt,MaxPart,sum;
bool del[MAXN];
int siz[MAXN];

inline void getRt(reg int u,reg int father){
	siz[u]=1;
	reg int Max=0;
	for(int v:G[u])
		if(v!=father&&!del[v]){
			getRt(v,u);
			siz[u]+=siz[v];
			Max=max(Max,siz[v]);
		}
	Max=max(Max,sum-siz[u]);
	if(Max<MaxPart)
		rt=u,MaxPart=Max;
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Line{
		ll k,b;
		inline Line(reg ll k=0,reg ll b=0):k(k),b(b){
			return;
		}
	};
	inline ll getVal(const Line& a,reg int x){
		return a.k*x+a.b;
	}
	struct Node{
		Line val;
		int tag;
		#define val(x) unit[(x)].val
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void update(reg int k,reg int l,reg int r,Line Val){
		if(!tag(k)){
			tag(k)=true;
			val(k)=Val;
			return;
		}
		reg ll lef=getVal(val(k),l),rig=getVal(val(k),r);
		reg ll tmpl=getVal(Val,l),tmpr=getVal(Val,r);
		if(lef>=tmpl&&rig>=tmpr)
			return;
		if(tmpl>lef&&tmpr>rig){
			swap(val(k),Val);
			return;
		}
		reg ll midv=getVal(val(k),mid),tmpv=getVal(Val,mid);
		if(midv>=tmpv){
			if(tmpl>lef)
				update(lson,l,mid,Val);
			else
				update(rson,mid+1,r,Val);
		}
		else{
			swap(val(k),Val);
			if(lef>=tmpl)
				update(lson,l,mid,Val);
			else
				update(rson,mid+1,r,Val);
		}
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int x){
		reg ll res=0;
		if(tag(k))
			res=max(res,getVal(val(k),x));
		if(l==r)
			return res;
		if(x<=mid)
			res=max(res,query(lson,l,mid,x));
		else
			res=max(res,query(rson,mid+1,r,x));
		return res;
	}
	inline void clear(reg int k,reg int l,reg int r){
		if(tag(k)){
			tag(k)=false;
			if(l!=r)
				clear(lson,l,mid),clear(rson,mid+1,r);
		}
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef val
	#undef tag
}

ll ans;
int top;
pair<ll,ll> S[MAXN];

inline void dfs(reg int u,reg int father,reg int rt,reg int dep,ll v1,reg ll v2,ll sum){
	v1+=1ll*dep*a[u];
	sum+=a[u];
	v2=v2+sum;
	ans=max(ans,SegmentTree::query(1,1,n,dep+1)+v2);
	S[++top]=make_pair(v1,sum);
	for(int v:G[u])
		if(v!=father&&!del[v])
			dfs(v,u,rt,dep+1,v1,v2,sum);
	return;
}

inline void calc(reg int u){
	SegmentTree::clear(1,1,n);
	for(int v:G[u])
		if(!del[v]){
			dfs(v,u,u,1,0,a[u],a[u]);
			while(top){
				pair<ll,ll> p=S[top--];
				SegmentTree::update(1,1,n,SegmentTree::Line(p.second-a[u],p.first));
			}
		}
	ans=max(ans,SegmentTree::query(1,1,n,1)+a[u]);
	reverse(G[u].begin(),G[u].end());
	SegmentTree::clear(1,1,n);
	for(int v:G[u])
		if(!del[v]){
			dfs(v,u,u,1,0,a[u],a[u]);
			while(top){
				pair<ll,ll> p=S[top--];
				SegmentTree::update(1,1,n,SegmentTree::Line(p.second-a[u],p.first));
			}
		}
	ans=max(ans,SegmentTree::query(1,1,n,1)+a[u]);
	return;
}

inline void solve(reg int u){
	del[u]=true;
	calc(u);
	for(int v:G[u])
		if(!del[v]){
			rt=0,MaxPart=inf,sum=siz[v];
			getRt(v,0),solve(rt);
		}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	printf("%lld\n",ans);
	return 0;
}