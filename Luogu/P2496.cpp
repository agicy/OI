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

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum,Max,pos;
		int tag;
		#define sum(x) unit[(x)].sum
		#define Max(x) unit[(x)].Max
		#define pos(x) unit[(x)].pos
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		if(Max(lson)>sum(lson)+Max(rson))
			pos(k)=pos(lson),Max(k)=Max(lson);
		else
			pos(k)=pos(rson),Max(k)=sum(lson)+Max(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			sum(k)=Max(k)=a[l];
			pos(k)=l;
			return;
		}
		build(lson,l,mid,a);
		build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,reg int val){
		sum(k)+=(r-l+1)*val;
		Max(k)+=(pos(k)-l+1)*val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			add(lson,l,mid,tag(k));
			add(rson,mid+1,r,tag(k));
			tag(k)=0;
			pushup(k);
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			sum(k)=Max(k)+=val;
			return;
		}
		pushdown(k,l,r);
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		if(pos>mid)
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			add(k,l,r,val);
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
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R){
			int left=query(lson,l,mid,L,R);
			int right=sum(lson)+query(rson,mid+1,r,L,R);
			return max(left,right);
		}
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else if(R>mid)
			return sum(lson)+query(rson,mid+1,r,L,R);
		else
			return 0;
	}
	inline int querysum(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return sum(k);
		pushdown(k,l,r);
		if(pos<=mid)
			return querysum(lson,l,mid,pos);
		else
			return sum(lson)+querysum(rson,mid+1,r,pos);
	}
	inline int querydelta(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return sum(k);
		pushdown(k,l,r);
		if(pos<=mid)
			return querydelta(lson,l,mid,pos);
		else
			return querydelta(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
int a[MAXN];
int h[MAXN];

int main(void){/*
	freopen("1.in","r",stdin);
	freopen("a.out","w",stdout);*/
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		h[i]=a[i]-a[i-1];
	SegmentTree::build(1,1,n,h);/*
	for(reg int i=1;i<=n;++i)
		printf("%d%c",SegmentTree::querysum(1,1,n,i),i==n?'\n':' ');
	for(reg int i=1;i<=n;++i)
		printf("%d%c",SegmentTree::querydelta(1,1,n,i),i==n?'\n':' ');*/
	while(m--){
		static int type,l,r,t;
		type=l=r=t=0;
		type=read();
		switch(type){
			case 1:{
				l=read(),r=read();
				int p=SegmentTree::query(1,1,n,l,r)-SegmentTree::querysum(1,1,n,1);
				printf("%d\n",max(p,0));
				break;
			}
			case 2:{
				l=read(),r=read();
				if(l>r)
					swap(l,r);
				if(l==r)
					break;
				reg int al=SegmentTree::querysum(1,1,n,l);
				reg int ar=SegmentTree::querysum(1,1,n,r);
				SegmentTree::update(1,1,n,l,ar-al);
				SegmentTree::update(1,1,n,r,al-ar);
				if(l+1<=n)
					SegmentTree::update(1,1,n,l+1,al-ar);
				if(r+1<=n)
					SegmentTree::update(1,1,n,r+1,ar-al);
				break;
			}
			case 3:{
				l=read(),r=read(),t=read();
				SegmentTree::update(1,1,n,l,r,t);
				if(r+1<=n)
					SegmentTree::update(1,1,n,r+1,r+1,-(r-l+1)*t);
				break;
			}
			default:break;
		}/*
		printf("opt=%d %d %d ",type,l,r);
		if(type==3)
			printf("%d",t);
		putchar('\n');
		puts("sum:");
		for(reg int i=1;i<=n;++i)
			printf("%d%c",SegmentTree::querysum(1,1,n,i),i==n?'\n':' ');
		puts("delta:");
		for(reg int i=1;i<=n;++i)
			printf("%d%c",SegmentTree::querydelta(1,1,n,i),i==n?'\n':' ');
		puts("");*/
	}
	return 0;
}
