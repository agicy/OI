#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int MAXM=3*MAXN;

struct Node{
	int id;
	int r;
	int L,pos,R;
	int cnt;
	inline bool operator<(const Node& a)const{
		return r<a.r;
	}
};

struct querys{
	int id;
	int x,y,Min;
	inline bool operator<(const querys& a)const{
		return Min<a.Min;
	}
};

namespace BIT{
	inline int lowbit(int x){
		return x&(-x);
	}
	int n,unit[MAXM];
	inline void Init(int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(int id,int val){
		for(int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(int id){
		int res=0;
		for(int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max;
		#define Max(x) unit[(x)].Max
	};
	Node unit[MAXM<<2];
	inline void pushup(int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void update(int k,int l,int r,int pos,int val){
		if(l==r){
			Max(k)=max(Max(k),val);
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R)
			return Max(k);
		int res=0;
		if(L<=mid)
			res=max(res,query(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,Q,K;
vector<int> V;
Node a[MAXN];
querys q[MAXQ];
int pos[MAXN];
int ans[MAXQ];

int main(void){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i].r);
	for(int i=1;i<=n;++i){
		static int age;
		scanf("%d",&age);
		a[i].id=i,a[i].L=age-K,a[i].pos=age,a[i].R=age+K;
		V.push_back(a[i].L),V.push_back(a[i].pos),V.push_back(a[i].R);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	int m=V.size();
	for(int i=1;i<=n;++i){
		a[i].L=lower_bound(V.begin(),V.end(),a[i].L)-V.begin()+1;
		a[i].pos=lower_bound(V.begin(),V.end(),a[i].pos)-V.begin()+1;
		a[i].R=lower_bound(V.begin(),V.end(),a[i].R)-V.begin()+1;
	}
	scanf("%d",&Q);
	for(int i=1;i<=Q;++i){
		q[i].id=i;
		scanf("%d%d",&q[i].x,&q[i].y);
		q[i].Min=max(a[q[i].x].r,a[q[i].y].r);
	}
	sort(a+1,a+n+1),sort(q+1,q+Q+1);
	BIT::Init(m);
	for(int l=1,r;l<=n;l=r+1){
		r=l;
		while(r<n&&a[r].r==a[r+1].r)
			++r;
		for(int i=l;i<=r;++i)
			BIT::update(a[i].pos,1);
		for(int i=l;i<=r;++i)
			a[i].cnt=BIT::query(a[i].R)-BIT::query(a[i].L-1);
	}
	for(int i=1;i<=n;++i)
		pos[a[i].id]=i;
	for(int i=Q,ptr=n;i>=1;--i){
		while(ptr>=1&&a[ptr].r>=q[i].Min){
			SegmentTree::update(1,1,m,a[ptr].pos,a[ptr].cnt);
			--ptr;
		}
		int x=pos[q[i].x],y=pos[q[i].y],l=max(a[x].L,a[y].L),r=min(a[x].R,a[y].R);
		if(l<=r)
			ans[q[i].id]=SegmentTree::query(1,1,m,l,r);
	}
	for(int i=1;i<=Q;++i)
		printf("%d\n",ans[i]?ans[i]:-1);
	return 0;
}