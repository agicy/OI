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

const int MAXN=2e5+5;
const int MAXA=1e5;
const int MAXLOG2A=17+1;

namespace SegmentTree{
	const int MAXSIZE=MAXA*40;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int cnt;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
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
		unit[k]=unit[pre],++cnt(k);
		if(l!=r){
			if(pos<=mid)
				lson(k)=update(lson(pre),l,mid,pos);
			else
				rson(k)=update(rson(pre),mid+1,r,pos);
		}
		return k;
	}
	inline int query(reg int pre,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return cnt(k)-cnt(pre);
		if(L<=mid&&mid<R)
			return query(lson(pre),lson(k),l,mid,L,R)+query(rson(pre),rson(k),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(pre),lson(k),l,mid,L,R);
		else
			return query(rson(pre),rson(k),mid+1,r,L,R);
	}
	#undef mid
}

int n,m;
int a[MAXN];
int rt[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	rt[0]=SegmentTree::build(0,MAXA);
	for(reg int i=1;i<=n;++i)
		rt[i]=SegmentTree::update(rt[i-1],0,MAXA,a[i]);
	while(m--){
		static int b,x,l,r;
		b=read(),x=read(),l=read(),r=read();
		reg int ans=0;
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			reg int c=(b>>i)&1;
			reg int L=max((ans|((c^1)<<i))-x,0),R=min(((ans|((c^1)<<i))|((1<<i)-1))-x,MAXA);
			reg int cnt;
			if(L>R)
				cnt=0;
			else
				cnt=SegmentTree::query(rt[l-1],rt[r],0,MAXA,L,R);
			if(cnt)
				ans|=(c^1)<<i;
			else
				ans|=c<<i;
		}
		printf("%d\n",ans^b);
	}
	return 0;
}