#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXQ=3e5+5;

namespace SegmentTree{
	const int MAXSIZE=15005000;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum,tag;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int l,reg int r){
		reg int p=++tot;
		lson(p)=rson(p)=0,sum(p)=r-l+1,tag(p)=-1;
		return p;
	}
	inline void pushup(reg int p){
		sum(p)=sum(lson(p))+sum(rson(p));
		return;
	}
	inline void cover(reg int p,reg int l,reg int r,reg int val){
		sum(p)=(r-l+1)*val,tag(p)=val;
		return;
	}
	inline void pushdown(reg int p,reg int l,reg int r){
		if(tag(p)!=-1){
			if(!lson(p))
				lson(p)=New(l,mid);
			cover(lson(p),l,mid,tag(p));
			if(!rson(p))
				rson(p)=New(mid+1,r);
			cover(rson(p),mid+1,r,tag(p));
			tag(p)=-1;
		}
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(!p)
			p=New(l,r);
		if(L<=l&&r<=R){
			cover(p,l,r,val);
			return;
		}
		pushdown(p,l,r);
		if(L<=mid)
			update(lson(p),l,mid,L,R,val);
		if(R>mid)
			update(rson(p),mid+1,r,L,R,val);
		pushup(p);
		return;
	}
	#undef mid
	#undef lson
	#undef rson
	#undef sum
	#undef tag
}

int n,q,rt;

int main(void){
	n=read(),q=read();
	SegmentTree::update(rt,1,n,1,n,0);
	while(q--){
		static int l,r,k;
		l=read(),r=read(),k=read();
		SegmentTree::update(rt,1,n,l,r,2-k);
		writeln(n-SegmentTree::unit[rt].sum);
	}
	flush();
	return 0;
}