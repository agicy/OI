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

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

namespace SegmentTree{
	const int MAXSIZE=MAXN*180;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson,Max;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson(k)),Max(rson(k)));
		return;
	}
	inline void update(reg int &k,reg int l,reg int r,reg int pos,reg int val){
		if(!k)
			k=++tot;
		if(l==r){
			Max(k)=max(Max(k),val);
			return;
		}
		if(pos<=mid)
			update(lson(k),l,mid,pos,val);
		else
			update(rson(k),mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!k)
			return 0;
		if(L<=l&&r<=R)
			return Max(k);
		if(L<=mid&&mid<R)
			return max(query(lson(k),l,mid,L,R),query(rson(k),mid+1,r,L,R));
		else if(L<=mid)
			return query(lson(k),l,mid,L,R);
		else
			return query(rson(k),mid+1,r,L,R);
	}
	#undef mid
}

int n,m;
int rt[MAXN];

int main(void){
	n=read(),m=read();
	reg int ans=0;
	for(reg int i=1;i<=m;++i){
		static int a,b,k;
		a=read(),b=read(),k=read();
		reg int Max=SegmentTree::query(rt[a],0,1e5,0,k-1)+1;
		ans=max(ans,Max);
		SegmentTree::update(rt[b],0,1e5,k,Max);
	}
	printf("%d\n",ans);
	return 0;
}