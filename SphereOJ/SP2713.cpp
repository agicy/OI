#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;

struct SegmentTree{
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid ((l+r)>>1)
	struct Node{
		ll sum;
		bool flag;
		inline Node(void){
			sum=0,flag=true;
			return;
		}
		inline Node(reg ll a){
			sum=a;
			if(a==0||a==1)
				flag=true;
			else
				flag=false;
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].sum=unit[lson].sum+unit[rson].sum;
		unit[k].flag=(unit[lson].flag&&unit[rson].flag);
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg ll a[]){
		if(l==r){
			unit[k]=Node(a[l]);
			return;
		}
		Build(lson,l,mid,a);
		Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(unit[k].flag)
			return;
		if(l==r){
			unit[k]=Node((ll)floor(sqrt(unit[k].sum)));
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R);
		if(R>mid)
			Update(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline ll Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].sum;
		reg ll res=0;
		if(L<=mid)
			res+=Query(lson,l,mid,L,R);
		if(R>mid)
			res+=Query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

int n,m;
ll a[MAXN];
SegmentTree T;

int main(void){
	reg int cnt=0;
	while(++cnt,scanf("%d",&n)!=EOF){
		for(reg int i=1;i<=n;++i)
			scanf("%lld",&a[i]);
		T.Build(1,1,n,a);
		scanf("%d",&m);
		printf("Case #%d:\n",cnt);
		for(reg int i=1;i<=m;++i){
			static int k,l,r;
			scanf("%d%d%d",&k,&l,&r);
			if(l>r)
				swap(l,r);
			if(k==0)
				T.Update(1,1,n,l,r);
			if(k==1)
				printf("%lld\n",T.Query(1,1,n,l,r));
		}
		putchar('\n');
	}
	return 0;
}
