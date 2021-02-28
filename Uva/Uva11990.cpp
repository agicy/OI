#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;

int n,m;
int a[MAXN];

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
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

namespace BIT2{
	namespace SegmentTree{
		const int MAXSIZE=4e7+5;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			int siz;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define siz(x) unit[(x)].siz
		};
		int tot;
		Node unit[MAXSIZE];
		inline int New(void){
			reg int p=++tot;
			lson(p)=rson(p)=siz(p)=0;
			return p;
		}
		inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
			if(!p)
				p=New();
			siz(p)+=val;
			if(l!=r){
				if(pos<=mid)
					update(lson(p),l,mid,pos,val);
				else
					update(rson(p),mid+1,r,pos,val);
			}
			return;
		}
		inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
			if(!p)
				return 0;
			if(L<=l&&r<=R)
				return siz(p);
			if(L<=mid&&mid<R)
				return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
			else if(L<=mid)
				return query(lson(p),l,mid,L,R);
			else
				return query(rson(p),mid+1,r,L,R);
		}
		#undef mid
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,rt[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(rt,0,sizeof(rt));
		SegmentTree::tot=0;
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,n,pos,val);
		return;
	}
	inline int query(reg int id,reg int L,reg int R){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=SegmentTree::query(rt[i],1,n,L,R);
		return res;
	}
	inline int query(reg int l,reg int r,reg int L,reg int R){
		return query(r,L,R)-query(l-1,L,R);
	}
}

int pos[MAXN];

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		BIT1::Init(n),BIT2::Init(n);
		reg ll ans=0;
		for(reg int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			pos[a[i]]=i;
			BIT1::update(a[i],1);
			ans+=i-BIT1::query(a[i]);
			BIT2::update(i,a[i],1);
		}
		while(m--){
			printf("%lld\n",ans);
			static int x,y;
			scanf("%d",&y);
			x=pos[y];
			if(1<x&&y<n)
				ans-=BIT2::query(1,x-1,y+1,n);
			if(x<n&&1<y)
				ans-=BIT2::query(x+1,n,1,y-1);
			BIT2::update(x,y,-1);
		}
	}
	return 0;
}