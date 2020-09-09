#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;
const int MAX=1e9+5;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	struct Node{
		int lson,rson;
		int val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define val(x) unit[(x)].val
	};
	int tot,root[MAXN];
	Node unit[MAXSIZE];
	inline void pushup(reg int k){
		val(k)=min(val(lson(k)),val(rson(k)));
		return;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos,reg int Val){
		reg int k=++tot;
		lson(k)=lson(pre),rson(k)=rson(pre);
		if(l==r){
			val(k)=Val;
			return k;
		}
		if(pos<=mid)
			lson(k)=update(lson(pre),l,mid,pos,Val);
		else
			rson(k)=update(rson(pre),mid+1,r,pos,Val);
		pushup(k);
		return k;
	}
	inline int query(reg int k,reg int l,reg int r,reg int Val){
		if(l==r)
			return l;
		if(val(lson(k))<Val)
			return query(lson(k),l,mid,Val);
		else
			return query(rson(k),mid+1,r,Val);
	}
}

using namespace SegmentTree;

int n,m;
int a[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		root[i]=update(root[i-1],0,MAX,a[i],i);
	}
	for(reg int i=1;i<=m;++i){
		static int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",query(root[r],0,MAX,l));
	}
	return 0;
}