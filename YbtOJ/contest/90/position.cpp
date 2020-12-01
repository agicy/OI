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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXQ=2e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

struct querys{
	int type,x,y;
};

int n,q;
ll a[MAXN];

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
		n=s;
		for(reg int i=1;i<=s;++i)
			unit[i]=0;
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		if(!id)
			return 0;
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline ll query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
};

BIT T,Ti;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum;
		int cnt;
		int tag;
		#define sum(x) unit[(x)].sum
		#define cnt(x) unit[(x)].cnt
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		cnt(k)=cnt(lson)+cnt(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg ll a[]){
		tag(k)=-1;
		if(l==r){
			sum(k)=a[l],cnt(k)=1;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void set0(reg int k){
		cnt(k)=0;
		tag(k)=0;
		return;
	}
	inline void set1(reg int k,reg int l,reg int r){
		cnt(k)=r-l+1;
		tag(k)=1;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)!=-1){
			if(tag(k)==0)
				set0(lson),set0(rson);
			if(tag(k)==1)
				set1(lson,l,mid),set1(rson,mid+1,r);
			tag(k)=-1;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			sum(k)=val;
			return;
		}
		pushdown(k,l,r);
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline void update0(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			set0(k);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update0(lson,l,mid,L,R);
		if(R>mid)
			update0(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline void update1(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			set1(k,l,r);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update1(lson,l,mid,L,R);
		if(R>mid)
			update1(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg ll val){
		if(l==r)
			return l;
		pushdown(k,l,r);
		reg ll Sum=sum(lson);
		if(val<=Sum)
			return query(lson,l,mid,val);
		else
			return query(rson,mid+1,r,val-Sum);
	}
	inline int queryR(reg int k,reg int l,reg int r,reg int val){
		if(val>cnt(k))
			return 0;
		if(l==r)
			return l;
		pushdown(k,l,r);
		reg int V=cnt(lson);
		if(val<=V)
			return queryR(lson,l,mid,val);
		else
			return queryR(rson,mid+1,r,val-V);
	}
	inline int queryL(reg int k,reg int l,reg int r,reg int val){
		if(val>cnt(k))
			return n+1;
		if(l==r)
			return l;
		pushdown(k,l,r);
		reg int V=cnt(rson);
		if(val<=V)
			return queryL(rson,mid+1,r,val);
		else
			return queryL(lson,l,mid,val-V);
	}
	inline int queryCnt(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L>R)
			return 0;
		if(L<=l&&r<=R)
			return cnt(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return queryCnt(lson,l,mid,L,R)+queryCnt(rson,mid+1,r,L,R);
		else if(L<=mid)
			return queryCnt(lson,l,mid,L,R);
		else
			return queryCnt(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

inline ll getVal(reg int pos){
	return T.query(1,pos)*pos-Ti.query(1,pos)+
		   Ti.query(pos,n)-T.query(pos,n)*pos;
}

int main(void){
	freopen("position.in","r",stdin);
	freopen("position.out","w",stdout);

	n=read(),q=read();
	T.Init(n),Ti.Init(n);
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum+=a[i];
		T.update(i,a[i]);
		Ti.update(i,a[i]*i);
	}
	SegmentTree::build(1,1,n,a);
	for(reg int i=1;i<=q;++i){
		static int type,x,y;
		type=read(),x=read(),y=read();
		switch(type){
			case 1:{
				T.update(x,y);
				Ti.update(x,1ll*y*x);
				a[x]+=y;
				sum+=y;
				SegmentTree::update(1,1,n,x,a[x]);
				break;
			}
			case 2:{
				T.update(x,-y);
				Ti.update(x,-1ll*y*x);
				a[x]-=y;
				sum-=y;
				SegmentTree::update(1,1,n,x,a[x]);
				break;
			}
			case 3:{
				SegmentTree::update1(1,1,n,x,y);
				break;
			}
			case 4:{
				SegmentTree::update0(1,1,n,x,y);
				break;
			}
		}
		reg int mid=SegmentTree::query(1,1,n,(sum+1)/2);

		reg int lcnt=SegmentTree::queryCnt(1,1,n,1,mid-1);
		reg int rcnt=SegmentTree::queryCnt(1,1,n,mid+1,n);

		reg int lpos=SegmentTree::queryR(1,1,n,lcnt+1);
		reg int rpos=SegmentTree::queryL(1,1,n,rcnt+1);

		reg ll val=inf;
		reg int ans=-1;
		if(1<=lpos&&lpos<=n){
			reg ll lval=getVal(lpos);
			if(val>lval||(val==lval&&lpos<ans))
				ans=lpos,val=lval;
		}
		if(1<=rpos&&rpos<=n){
			reg ll rval=getVal(rpos);
			if(val>rval||(val==rval&&rpos<ans))
				ans=rpos,val=rval;
		}
		printf("%d\n",ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}