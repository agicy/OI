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

const int MAXN=2e4+5;

int n;
int h[MAXN];

namespace Tree{
	#define lowbit(x) ( (x) & ( - (x) ) )
	namespace SegmentTree{
		#define mid ( ( (l) + (r) ) >> 1 )
		const int MAXSIZE=400*MAXN;
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
		inline int New(void){
			return ++tot;
		}
		inline void update(reg int& k,reg int l,reg int r,reg int pos,reg int cnt){
			if(!k)
				k=New();
			val(k)+=cnt;
			if(l==r)
				return;
			if(pos<=mid)
				update(lson(k),l,mid,pos,cnt);
			else
				update(rson(k),mid+1,r,pos,cnt);
			return;
		}
		inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
			if(!k)
				return 0;
			if(L<=l&&r<=R)
				return val(k);
			reg int res=0;
			if(L<=mid)
				res+=query(lson(k),l,mid,L,R);
			if(R>mid)
				res+=query(rson(k),mid+1,r,L,R);
			return res;
		}
		#undef mid
	}
	inline void update(reg int id,reg int val,reg int cnt){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(SegmentTree::root[i],1,n,val,cnt);
		return;
	}
	inline int query(reg int pos,reg int vall,reg int valr){
		reg int res=0;
		for(reg int i=pos;i;i-=lowbit(i))
			res+=SegmentTree::query(SegmentTree::root[i],1,n,vall,valr);
		return res;
	}
	inline int query(reg int posl,reg int posr,reg int vall,reg int valr){
		if(posl>posr||vall>valr)
			return 0;
		return query(posr,vall,valr)-query(posl-1,vall,valr);
	}
	#undef lowbit
}

namespace TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int unit[MAXN];
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
}

vector<int> V;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		h[i]=read();
		V.push_back(h[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		h[i]=lower_bound(V.begin(),V.end(),h[i])-V.begin()+1;
	reg int ans=0;
	for(reg int i=n;i>=1;--i){
		ans+=TreeArray::query(h[i]-1);
		TreeArray::update(h[i],1);
	}
	for(reg int i=1;i<=n;++i)
		Tree::update(i,h[i],1);
	printf("%d\n",ans);
	reg int m=read();
	while(m--){
		static int a,b;
		a=read(),b=read();
		if(a>b)
			swap(a,b);
		ans+=Tree::query(a+1,b-1,1,h[b]-1);
		ans-=Tree::query(a+1,b-1,h[b]+1,n);
		ans+=Tree::query(a+1,b-1,h[a]+1,n);
		ans-=Tree::query(a+1,b-1,1,h[a]-1);
		if(h[a]>h[b])
			--ans;
		if(h[a]<h[b])
			++ans;
		Tree::update(a,h[a],-1),Tree::update(b,h[b],-1);
		swap(h[a],h[b]);
		Tree::update(a,h[a],1),Tree::update(b,h[b],1);
		printf("%d\n",ans);
	}
	return 0;
}