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

static char wbuf[1<<21];
int wp1;
const int wp2=1<<21;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
	return;
}

#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n,m;

namespace BIT0{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		if(id>n)
			id=n;
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		if(id>n)
			id=n;
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

namespace Treap{
	const int MAXSIZE=MAXN*20;
	struct Node{
		int ch[2];
		int siz,val;
		int key;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define key(x) unit[(x)].key
	};
	#define lson(x) (ch(x)[0])
	#define rson(x) (ch(x)[1])
	int tot,rt[MAXN];
	int top,S[MAXSIZE];
	Node unit[MAXSIZE];
	inline int New(void){
		return top?S[top--]:++tot;
	}
	inline void Del(reg int p){
		S[++top]=p;
		siz(p)=val(p)=key(p)=lson(p)=rson(p)=0;
		return;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline int merge(reg int u,reg int v){
		if(!u||!v)
			return u|v;
		reg int rt;
		if(key(u)<key(v))
			rt=u,rson(u)=merge(rson(u),v);
		else
			rt=v,lson(v)=merge(u,lson(v));
		pushup(rt);
		return rt;
	}
	inline void split(reg int p,reg int &u,reg int &v,reg int k){
		if(!p){
			u=v=0;
			return;
		}
		if(val(p)<=k)
			u=p,split(rson(u),rson(p),v,k);
		else
			v=p,split(lson(v),u,lson(p),k);
		pushup(p);
		return;
	}
	inline void insert(reg int l,reg int r){
		int lef,rig;
		split(rt[l],lef,rig,r);
		reg int u=New();
		key(u)=rand(),siz(u)=1,val(u)=r;
		rt[l]=merge(merge(lef,u),rig);
		return;
	}
	inline void del(reg int l,reg int r){
		int lef,rig,mid;
		split(rt[l],lef,rig,r);
		split(lef,lef,mid,r-1);
		rt[l]=merge(lef,rig);
		Del(mid);
		return;
	}
	inline int getVal(reg int l){
		reg int p=rt[l];
		while(rson(p))
			p=rson(p);
		return val(p);
	}
	#undef lson
	#undef rson
	#undef ch
	#undef siz
	#undef val
	#undef key
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,pMax;
		#define Max(x) unit[(x)].Max
		#define pMax(x) unit[(x)].pMax
	};
	inline Node operator+(Node a,Node b){
		return a.Max>b.Max?a:b;
	}
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r){
			if(Treap::rt[l])
				Max(k)=Treap::getVal(l),pMax(k)=l;
			else
				Max(k)=pMax(k)=0;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos);
		else
			update(rson,mid+1,r,pos);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
	#undef Max
	#undef pMax
}

int main(void){
	srand(time(0));
	n=read(),m=read();
	BIT0::Init(n),BIT1::Init(n);
	for(reg int i=1;i<=n;++i){
		BIT1::update(i,1);
		Treap::insert(1,i);
		SegmentTree::update(1,1,n,1);
	}
	while(m--){
		static int opt,x,l,r;
		opt=read();
		switch(opt){
			case 1:{
				x=read();
				BIT0::update(x,1);
				while(true){
					static SegmentTree::Node s;
					s=SegmentTree::query(1,1,n,1,x);
					if(s.Max<x)
						break;
					Treap::del(s.pMax,s.Max);
					SegmentTree::update(1,1,n,s.pMax);
					reg int len=s.Max-s.pMax+1,l=s.pMax,r=s.Max;
					while(BIT0::query(l,r)>0&&l<=n){
						l+=len,r+=len;
						BIT1::update(len,1);
					}
					if(l<=n){
						Treap::insert(l,r);
						SegmentTree::update(1,1,n,l);
					}
				}
				break;
			}
			case 2:{
				l=read(),r=read();
				writeln(BIT1::query(l,r));
				break;
			}
		}
	}
	flush();
	return 0;
}
