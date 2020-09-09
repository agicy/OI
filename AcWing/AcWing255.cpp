#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;

int n,m;
int a[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*40;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
	};
	int tot,root[MAXN];
	Node unit[MAXSIZE];
	inline int build(reg int l,reg int r){
		reg int k=++tot;
		cnt(k)=0;
		if(l!=r)
			lson(k)=build(l,mid),rson(k)=build(mid+1,r);
		return k;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos,reg int val){
		reg int k=++tot;
		lson(k)=lson(pre),rson(k)=rson(pre),cnt(k)=cnt(pre)+val;
		if(l==r)
			return k;
		if(pos<=mid)
			lson(k)=update(lson(pre),l,mid,pos,val);
		else
			rson(k)=update(rson(pre),mid+1,r,pos,val);
		return k;
	}
	inline int query(reg int k,reg int pre,reg int l,reg int r,reg int val){
		if(l==r)
			return l;
		reg int sum=cnt(lson(k))-cnt(lson(pre));
		if(val<=sum)
			return query(lson(k),lson(pre),l,mid,val);
		else
			return query(rson(k),rson(pre),mid+1,r,val-sum);
	}
}

vector<int> V;

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]),V.push_back(a[i]);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	using namespace SegmentTree;
	root[0]=build(1,n);
	for(reg int i=1;i<=n;++i){
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		root[i]=update(root[i-1],1,n,a[i],1);
	}
	while(m--){
		static int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		reg int pos=query(root[r],root[l-1],1,n,k);
		printf("%d\n",V[pos-1]);
	}
	return 0;
}