#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXM=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Node{
	int t,l,r,c;
	inline bool operator<(const Node& a)const{
		return t<a.t;
	}
};

int n,m;
Node a[MAXM];
ll dis[MAXM];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Min[2];
		#define Min(x) unit[(x)].Min
	};
	Node unit[MAXM<<2];
	inline void pushup(reg int k){
		Min(k)[0]=min(Min(lson)[0],Min(rson)[0]);
		Min(k)[1]=min(Min(lson)[1],Min(rson)[1]);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int ptr,reg int len){
		if(l==r){
			Min(k)[0]=ptr-len,Min(k)[1]=ptr+len;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,ptr,len);
		else
			update(rson,mid+1,r,pos,ptr,len);
		pushup(k);
		return;
	}
	inline void query(reg int k,int l,reg int r,reg int L,reg int R,reg int lim,reg int flag,reg ll val){
		if(lim<Min(k)[flag])
			return;
		if(l==r){
			dis[l]=a[l].c+val;
			Q.push(make_pair(dis[l],l));
			Min(k)[0]=Min(k)[1]=INT_MAX;
			return;
		}
		if(L<=mid)
			query(lson,l,mid,L,R,lim,flag,val);
		if(R>mid)
			query(rson,mid+1,r,L,R,lim,flag,val);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef Min
};

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		a[i].t=read(),a[i].l=read(),a[i].r=read(),a[i].c=read();
	sort(a+1,a+m+1);
	fill(dis+1,dis+m+1,inf);
	for(int i=1;i<=m;++i)
		if(a[i].l==1)
			dis[i]=a[i].c,Q.push(make_pair(dis[i],i)),SegmentTree::update(1,1,m,i,INT_MAX,0);
		else
			SegmentTree::update(1,1,m,i,a[i].l,a[i].t);
	while(!Q.empty()){
		reg int u=Q.top().second;
		Q.pop();
		SegmentTree::query(1,1,m,1,u-1,a[u].r-a[u].t+1,0,dis[u]);
		SegmentTree::query(1,1,m,u+1,m,a[u].r+a[u].t+1,1,dis[u]);
	}
	reg ll ans=inf;
	for(reg int i=1;i<=m;++i)
		if(a[i].r==n)
			ans=min(ans,dis[i]);
	printf("%lld\n",ans==inf?-1:ans);
	return 0;
}