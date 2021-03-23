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

const int MAXN=5e5+5;

struct Node{
	int x,y,z;
	inline bool operator<(const Node& a)const{
		return x<a.x;
	}
};

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum;
		int Min;
		int tag;
		#define sum(x) unit[(x)].sum
		#define Min(x) unit[(x)].Min
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tag(k)=-1;
		if(l==r){
			sum(k)=Min(k)=1;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void cover(reg int k,reg int l,reg int r,reg int val){
		sum(k)=(r-l+1)*val;
		Min(k)=val;
		tag(k)=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)!=-1){
			cover(lson,l,mid,tag(k));
			cover(rson,mid+1,r,tag(k));
			tag(k)=-1;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cover(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline ll querySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return querySum(lson,l,mid,L,R)+querySum(rson,mid+1,r,L,R);
		else if(L<=mid)
			return querySum(lson,l,mid,L,R);
		else
			return querySum(rson,mid+1,r,L,R);
	}
	inline int find(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(l==r)
			return Min(k)<val?l:0;
		pushdown(k,l,r);
		if(L<=mid&&mid<R){
			if(Min(lson)<val)
				return find(lson,l,mid,L,R,val);
			else
				return find(rson,mid+1,r,L,R,val);
		}
		else if(L<=mid)
			return find(lson,l,mid,L,R,val);
		else
			return find(rson,mid+1,r,L,R,val);
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,p,q,r;
Node a[MAXN];
int Maxy[MAXN],Maxz[MAXN];

inline void update(reg int y,reg int z){
	reg int pos=SegmentTree::find(1,1,q,1,y,z);
	if(pos)
		SegmentTree::update(1,1,q,pos,y,z);
	return;
}

inline ll query(reg int y,reg int z){
	if(y>q)
		return 0;
	reg int pos=SegmentTree::find(1,1,q,y,q,z);
	reg ll sum=0;
	if(!pos)
		sum=SegmentTree::querySum(1,1,q,y,q);
	else
		sum=((y<pos)?SegmentTree::querySum(1,1,q,y,pos-1):0)+1ll*z*(q-pos+1);
	return 1ll*(r+1)*(q-y+1)-sum;
}

int main(void){
	n=read(),p=read(),q=read(),r=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read(),a[i].z=read();
	sort(a+1,a+n+1);
	for(reg int i=n;i>=1;--i){
		Maxy[i]=max(Maxy[i+1],a[i].y);
		Maxz[i]=max(Maxz[i+1],a[i].z);
	}
	reg ll ans=0;
	a[0].x=a[1].x;
	if(a[n].x!=p)
		a[++n].x=p;
	SegmentTree::build(1,1,q);
	reg int ptr=1;
	for(reg int i=1;i<=n;++i)
		if(a[i].x!=a[i-1].x){
			while(ptr<i){
				update(a[ptr].y,a[ptr].z+1);
				++ptr;
			}
			ans+=1ll*(a[i].x-a[i-1].x)*query(Maxy[i]+1,Maxz[i]+1);
		}
	ans+=1ll*a[1].x*(q-Maxy[1])*(r-Maxz[1]);
	printf("%lld\n",ans);
	return 0;
}