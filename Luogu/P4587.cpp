#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int Max=1e9+5;

int n,m;
int a[MAXN];
int root[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*200;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson,sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int k){
		sum(k)=sum(lson(k))+sum(rson(k));
		return;
	}
	inline int update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		reg int id=++tot;
		sum(id)=sum(k)+val,lson(id)=lson(k),rson(id)=rson(k);
		if(l!=r){
			if(pos<=mid)
				lson(id)=update(lson(k),l,mid,pos,val);
			else
				rson(id)=update(rson(k),mid+1,r,pos,val);
		}
		return id;
	}
	inline int query(reg int pre,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k)-sum(pre);
		reg int res=0;
		if(L<=mid)
			res+=query(lson(pre),lson(k),l,mid,L,R);
		if(R>mid)
			res+=query(rson(pre),rson(k),mid+1,r,L,R);
		return res;
	}
	inline int query(reg int l,reg int r){
		reg int las=0,ptr=0;
		while(true){
			reg int tmp=query(root[l-1],root[r],1,Max,las+1,ptr+1);
			if(!tmp)
				return ptr+1;
			las=ptr+1,ptr+=tmp;
		}
		return ptr+1;
	}
	#undef mid
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		root[i]=SegmentTree::update(root[i-1],1,Max,a[i],a[i]);
	m=read();
	while(m--){
		static int l,r;
		l=read(),r=read();
		printf("%d\n",SegmentTree::query(l,r));
	}
	return 0;
}