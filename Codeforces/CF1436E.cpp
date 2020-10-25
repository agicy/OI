#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];
int lst[MAXN];
bool vis[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Min;
		#define Min(x) unit[(x)].Min
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Min(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Min(k);
		if(L<=mid&&mid<R)
			return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i){
		if(a[i]!=1)
			vis[1]=true;
		if(a[i]>1&&SegmentTree::query(1,1,n,1,a[i]-1)>lst[a[i]])
			vis[a[i]]=true;
		lst[a[i]]=i;
		SegmentTree::update(1,1,n,a[i],i);
	}
	for(reg int i=2;i<=n+1;++i)
		if(SegmentTree::query(1,1,n,1,i-1)>lst[i])
			vis[i]=true;
	reg int ans=1;
	while(vis[ans]&&ans<=n+1)
		++ans;
	printf("%d\n",ans);
	return 0;
}