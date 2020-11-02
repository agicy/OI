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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	struct Node{
		int lson,rson,sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline int build(reg int l,reg int r){
		reg int k=++tot;
		if(l!=r)
			lson(k)=build(l,mid),rson(k)=build(mid+1,r);
		return k;
	}
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int k=++tot;
		unit[k]=unit[pre];
		++sum(k);
		if(l==r)
			return k;
		if(pos<=mid)
			lson(k)=update(lson(pre),l,mid,pos);
		else
			rson(k)=update(rson(pre),mid+1,r,pos);
		return k;
	}
	inline int query(reg int k,reg int pre,reg int l,reg int r,reg int cnt){
		if(l==r&&sum(k)-sum(pre)>cnt)
			return l;
		reg int lsum=sum(lson(k))-sum(lson(pre)),rsum=sum(rson(k))-sum(rson(pre));
		if(lsum>cnt)
			return query(lson(k),lson(pre),l,mid,cnt);
		if(rsum>cnt)
			return query(rson(k),rson(pre),mid+1,r,cnt);
		return 0;
	}
	#undef mid
}

int n,m;
int root[MAXN];

int main(void){
	n=read(),m=read();
	root[0]=SegmentTree::build(0,n);
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		root[i]=SegmentTree::update(root[i-1],0,n,a);
	}
	while(m--){
		static int l,r;
		l=read(),r=read();
		reg int cnt=(r-l+1)/2;
		reg int ans=SegmentTree::query(root[r],root[l-1],0,n,cnt);
		printf("%d\n",ans);
	}
	return 0;
}