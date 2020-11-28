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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e6+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum,cnt;
		#define sum(x) unit[(x)].sum
		#define cnt(x) unit[(x)].cnt
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		sum(k)=sum(lson)+sum(rson);
		cnt(k)=cnt(lson)+cnt(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			sum(k)=a[l],cnt(k)=(a[l]==1);
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			sum(k)=val,cnt(k)=(val==1);
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int querysum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		if(L<=mid&&mid<R)
			return querysum(lson,l,mid,L,R)+querysum(rson,mid+1,r,L,R);
		else if(L<=mid)
			return querysum(lson,l,mid,L,R);
		else
			return querysum(rson,mid+1,r,L,R);
	}
	inline int querycnt(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return cnt(k);
		if(L<=mid&&mid<R)
			return querycnt(lson,l,mid,L,R)+querycnt(rson,mid+1,r,L,R);
		else if(L<=mid)
			return querycnt(lson,l,mid,L,R);
		else
			return querycnt(rson,mid+1,r,L,R);
	}
	inline int Bquerysum(reg int k,reg int l,reg int r,reg int val){
		if(l>r)
			return 0;
		if(l==r)
			return l;
		if(val<=sum(lson))
			return Bquerysum(lson,l,mid,val);
		else
			return Bquerysum(rson,mid+1,r,val-sum(lson));
	}
	inline int Bquerycnt(reg int k,reg int l,reg int r,reg int val){
		if(l>r)
			return 0;
		if(l==r)
			return l;
		if(val<=cnt(lson))
			return Bquerycnt(lson,l,mid,val);
		else
			return Bquerycnt(rson,mid+1,r,val-cnt(lson));
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
int a[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	a[n+1]=1;
	SegmentTree::build(1,1,n+1,a);
	while(m--){
		static char opt;
		static int i,val,s;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'A':{
				s=read();
				if(s>SegmentTree::querysum(1,1,n+1,1,n+1)-1||!s)
					puts("none");
				else{
					reg int pos=SegmentTree::Bquerysum(1,1,n+1,s);
					if(SegmentTree::querysum(1,1,n+1,1,pos)==s)
						printf("%d %d\n",1,pos);
					else if(a[1]==1)
						printf("%d %d\n",2,pos);
					else{
						reg int lnxt=SegmentTree::Bquerycnt(1,1,n+1,1),rnxt=SegmentTree::Bquerycnt(1,1,n+1,SegmentTree::querycnt(1,1,n+1,1,pos)+1);
						if(pos+lnxt-1>n&&rnxt>n)
							puts("none");
						else if(rnxt-pos+1<lnxt+1)
							printf("%d %d\n",rnxt-pos+1,rnxt);
						else
							printf("%d %d\n",lnxt+1,pos+lnxt-1);
					}
				}
				break;
			}
			case 'C':{
				i=read(),val=read();
				a[i]=val;
				SegmentTree::update(1,1,n+1,i,val);
				break;
			}
		}
	}
	return 0;
}