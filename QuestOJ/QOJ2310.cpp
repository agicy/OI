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

struct Node{
	ll first,second;
	inline Node(reg ll first=0,reg ll second=0):first(first),second(second){
		return;
	}
	inline Node operator+(const Node& a)const{
		return Node(first+a.first,second+a.second);
	}
	inline void operator+=(const Node& a){
		first+=a.first,second+=a.second;
	}
	inline Node operator-(const Node& a)const{
		return Node(first-a.first,second-a.second);
	}
};

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	Node unit[MAXN];
	inline void Init(reg int s){
		n=s;/*
		for(reg int i=1;i<=s;++i)
			unit[i][0]=unit[i][1]=0;*/
		return;
	}
	inline void update(reg int id,const Node& val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline Node query(reg int id){
		if(!id)
			return Node(0,0);
		Node res(0,0);
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline Node query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

namespace SegmentTreeSum{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll sum;
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			sum(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		sum(k)=sum(lson)+sum(rson);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		while(true){
			sum(k)+=val;
			if(l==r)
				break;
			if(pos<=mid)
				k=lson,r=mid;
			else
				k=rson,l=mid+1;
		}
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg ll val){
		while(true){
			if(l==r)
				return l;
			reg ll Sum=sum(lson);
			if(val<=Sum)
				k=lson,r=mid;
			else
				k=rson,l=mid+1,val-=Sum;
		}
		return -1;
	}
	#undef lson
	#undef rson
	#undef mid
}

namespace SegmentTreeCnt{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int cnt,tag;
		#define cnt(x) unit[(x)].cnt
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void set0(reg int k){
		cnt(k)=tag(k)=0;
		return;
	}
	inline void set1(reg int k,reg int l,reg int r){
		cnt(k)=r-l+1,tag(k)=1;
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
		cnt(k)=cnt(lson)+cnt(rson);
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
		cnt(k)=cnt(lson)+cnt(rson);
		return;
	}
	inline int queryR(reg int k,reg int l,reg int r,reg int val){
		if(val>cnt(k))
			return 0;
		while(true){
			if(l==r)
				return l;
			pushdown(k,l,r);
			reg int V=cnt(lson);
			if(val<=V)
				k=lson,r=mid;
			else
				k=rson,l=mid+1,val-=V;
		}
		return -1;
	}
	inline int queryL(reg int k,reg int l,reg int r,reg int val){
		if(val>cnt(k))
			return n+1;
		while(true){
			if(l==r)
				return l;
			pushdown(k,l,r);
			reg int V=cnt(rson);
			if(val<=V)
				k=rson,l=mid+1;
			else
				k=lson,r=mid,val-=V;
		}
		return -1;
	}
	inline int queryCnt(reg int k,reg int l,reg int r,reg int L,reg int R){
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
	return BIT::query(1,pos).first*pos-BIT::query(1,pos).second+
		   BIT::query(pos,n).second-BIT::query(pos,n).first*pos;
}

int main(void){
	n=read(),q=read();
	BIT::Init(n);
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum+=a[i];
		BIT::update(i,Node(a[i],a[i]*i));
	}
	SegmentTreeSum::build(1,1,n,a);
	SegmentTreeCnt::set1(1,1,n);
	for(reg int i=1,mid,lcnt,rcnt,lpos,rpos;i<=q;++i){
		static int type,x,y;
		type=read(),x=read(),y=read();
		switch(type){
			case 1:{
				BIT::update(x,Node(y,1ll*y*x));
				sum+=y;
				SegmentTreeSum::update(1,1,n,x,y);
				break;
			}
			case 2:{
				BIT::update(x,Node(-y,-1ll*y*x));
				sum-=y;
				SegmentTreeSum::update(1,1,n,x,-y);
				break;
			}
			case 3:{
				SegmentTreeCnt::update1(1,1,n,x,y);
				break;
			}
			case 4:{
				SegmentTreeCnt::update0(1,1,n,x,y);
				break;
			}
		}
		mid=SegmentTreeSum::query(1,1,n,(sum+1)/2);
		lcnt=0,rcnt=0;
		if(mid>1)lcnt=SegmentTreeCnt::queryCnt(1,1,n,1,mid-1);
		if(mid<n)rcnt=SegmentTreeCnt::queryCnt(1,1,n,mid+1,n);
		lpos=SegmentTreeCnt::queryR(1,1,n,lcnt+1);
		rpos=SegmentTreeCnt::queryL(1,1,n,rcnt+1);

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
	return 0;
}