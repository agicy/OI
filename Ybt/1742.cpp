#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=1e5+5;
const int MAXR=1e5+5;
const int p=123456789;

inline int add(int a,int b){
	int sum=a+b;
	return sum>=p?sum-p:sum;
}

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
	int tot;
	int root[MAXN];
	Node unit[MAXSIZE];
	inline void update(int &k,int l,int r,int pos,int Val){
		if(!k)
			k=++tot;
		val(k)=add(val(k),Val);
		if(l!=r){
			if(pos<=mid)
				update(lson(k),l,mid,pos,Val);
			else
				update(rson(k),mid+1,r,pos,Val);
		}
		return;
	}
	inline int query(int k,int l,int r,int pos){
		if(r<=pos)
			return val(k);
		if(pos<=mid)
			return query(lson(k),l,mid,pos);
		else
			return add(val(lson(k)),query(rson(k),mid+1,r,pos));
	}
	#undef mid
}

namespace BIT{
	inline int lowbit(int x){
		return x&(-x);
	}
	int n,unit[MAXR];
	inline void Init(int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(int id,int val){
		for(int i=id;i<=n;i+=lowbit(i))
			unit[i]=max(unit[i],val);
		return;
	}
	inline int query(int id){
		int res=0;
		for(int i=id;i;i-=lowbit(i))
			res=max(res,unit[i]);
		return res;
	}
}

int n,type;
int f[MAXN],g[MAXN];

int main(void){
	scanf("%d%d",&n,&type);
	BIT::Init(1e5);
	int ans1=0,ans2=0;
	for(int i=1;i<=n;++i){
		static int r;
		scanf("%d",&r);
		f[i]=BIT::query(r-1);
		if(f[i]==0)
			g[i]=1;
		else
			g[i]=SegmentTree::query(SegmentTree::root[f[i]],0,1e5,r-1);
		++f[i];
		if(f[i]>ans1)
			ans1=f[i],ans2=0;
		if(f[i]==ans1)
			ans2=add(ans2,g[i]);
		SegmentTree::update(SegmentTree::root[f[i]],0,1e5,r,g[i]);
		BIT::update(r,f[i]);
	}
	if(!type)
		printf("%d\n",ans1);
	else
		printf("%d\n%d\n",ans1,ans2);
	return 0;
}