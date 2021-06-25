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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e4+5;
const int inf=0x7fffffff;

int n,m;
int a[MAXN];

namespace SegmentTree{
	namespace FHQTreap{
		const int MAXSIZE=MAXN*40;
		struct Node{
			int lson,rson,siz;
			int val;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define siz(x) unit[(x)].siz
			#define val(x) unit[(x)].val
		};
		int tot;
		Node unit[MAXSIZE];
		int top,S[MAXSIZE];
		inline int getId(void){
			if(top)
				return S[top--];
			else
				return ++tot;
		}
		inline int New(reg int v){
			reg int p=getId();
			lson(p)=rson(p)=0,siz(p)=1;
			val(p)=v;
			return p;
		}
		inline void pushup(reg int p){
			siz(p)=siz(lson(p))+siz(rson(p))+1;
			return;
		}
		inline int merge(reg int x,reg int y){
			if(!x||!y)
				return x|y;
			if(rand()%(siz(x)+siz(y))<siz(x)){
				rson(x)=merge(rson(x),y);
				pushup(x);
				return x;
			}
			else{
				lson(y)=merge(x,lson(y));
				pushup(y);
				return y;
			}
		}
		inline void split(reg int p,reg int v,reg int &x,reg int &y){
			if(!p){
				x=y=0;
				return;
			}
			if(val(p)<=v){
				x=p;
				split(rson(x),v,rson(x),y);
				pushup(x);
			}
			else{
				y=p;
				split(lson(y),v,x,lson(y));
				pushup(y);
			}
			return;
		}
		inline int insert(reg int rt,reg int v){
			static int rt1,rt2;
			split(rt,v,rt1,rt2);
			rt=merge(merge(rt1,New(v)),rt2);
			return rt;
		}
		inline int del(reg int rt,reg int v){
			static int rt1,mid,rt2;
			split(rt,v-1,rt1,mid);
			split(mid,v,mid,rt2);
			rt=merge(merge(rt1,merge(lson(mid),rson(mid))),rt2);
			S[++top]=mid;
			return rt;
		}
		inline int pre(reg int &rt,reg int v){
			static int rt1,rt2;
			split(rt,v-1,rt1,rt2);
			reg int p=rt1;
			while(rson(p))
				p=rson(p);
			reg int res=val(p);
			rt=merge(rt1,rt2);
			return res;
		}
		inline int suf(reg int &rt,reg int v){
			static int rt1,rt2;
			split(rt,v,rt1,rt2);
			reg int p=rt2;
			while(lson(p))
				p=lson(p);
			reg int res=val(p);
			rt=merge(rt1,rt2);
			return res;
		}
		inline int getRnk(reg int &rt,reg int v){
			static int rt1,rt2;
			split(rt,v-1,rt1,rt2);
			reg int res=siz(rt1);
			rt=merge(rt1,rt2);
			return res;
		}
		#undef lson
		#undef rson
		#undef siz
		#undef val
	}
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int rt;
		#define rt(x) unit[(x)].rt
	};
	Node unit[MAXN<<2];
	inline void build(reg int k,reg int l,reg int r){
		rt(k)=FHQTreap::New(inf);
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		rt(k)=FHQTreap::del(rt(k),a[pos]);
		rt(k)=FHQTreap::insert(rt(k),val);
		if(l==r){
			a[pos]=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		return;
	}
	inline void insert(reg int k,reg int l,reg int r,reg int pos,reg int val){
		rt(k)=FHQTreap::insert(rt(k),val);
		if(l==r)
			return;
		if(pos<=mid)
			insert(lson,l,mid,pos,val);
		else
			insert(rson,mid+1,r,pos,val);
		return;
	}
	inline int queryRnk(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R)
			return FHQTreap::getRnk(rt(k),val);
		if(L<=mid&&mid<R)
			return queryRnk(lson,l,mid,L,R,val)+queryRnk(rson,mid+1,r,L,R,val);
		else if(L<=mid)
			return queryRnk(lson,l,mid,L,R,val);
		else
			return queryRnk(rson,mid+1,r,L,R,val);
	}
	inline int queryPre(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R)
			return FHQTreap::pre(rt(k),val);
		if(L<=mid&&mid<R)
			return max(queryPre(lson,l,mid,L,R,val),queryPre(rson,mid+1,r,L,R,val));
		else if(L<=mid)
			return queryPre(lson,l,mid,L,R,val);
		else
			return queryPre(rson,mid+1,r,L,R,val);
	}
	inline int querySuf(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R)
			return FHQTreap::suf(rt(k),val);
		if(L<=mid&&mid<R)
			return min(querySuf(lson,l,mid,L,R,val),querySuf(rson,mid+1,r,L,R,val));
		else if(L<=mid)
			return querySuf(lson,l,mid,L,R,val);
		else
			return querySuf(rson,mid+1,r,L,R,val);
	}
	#undef lson
	#undef rson
	#undef mid
	#undef rt
	inline int queryKth(reg int L,reg int R,reg int k){
		reg int l=-inf,r=inf,mid;
		while(l<r){
			mid=(0ll+l+r)>>1;
			reg int val=queryRnk(1,1,n,L,R,mid+1)+1;
			if(val<=k)
				l=mid+1;
			else
				r=mid;
		}
		return l;
	}
}

int main(void){
	n=read(),m=read();
	SegmentTree::build(1,1,n);
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		SegmentTree::insert(1,1,n,i,a[i]);
	while(m--){
		static int opt,l,r,pos,k;
		opt=read();
		switch(opt){
			case 1:{
				l=read(),r=read(),k=read();
				writeln(SegmentTree::queryRnk(1,1,n,l,r,k)+1);
				break;
			}
			case 2:{
				l=read(),r=read(),k=read();
				writeln(SegmentTree::queryKth(l,r,k));
				break;
			}
			case 3:{
				pos=read(),k=read();
				SegmentTree::update(1,1,n,pos,k);
				break;
			}
			case 4:{
				l=read(),r=read(),k=read();
				writeln(SegmentTree::queryPre(1,1,n,l,r,k));
				break;
			}
			case 5:{
				l=read(),r=read(),k=read();
				writeln(SegmentTree::querySuf(1,1,n,l,r,k));
				break;
			}
		}
	}
	flush();
	return 0;
}