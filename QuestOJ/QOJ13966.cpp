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
const int inf=0x3f3f3f3f;

namespace Segmentunit{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int id,cnt;
		#define id(x) unit[(x)].id
		#define cnt(x) unit[(x)].cnt
	};
	inline Node operator+(const Node& a,const Node& rt){
		Node res;
		if(a.id==rt.id)
			res.id=a.id,res.cnt=a.cnt+rt.cnt;
		else if(a.cnt>=rt.cnt)
			res.id=a.id,res.cnt=a.cnt-rt.cnt;
		else
			res.id=rt.id,res.cnt=rt.cnt-a.cnt;
		return res;
	}
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			id(k)=a[l],cnt(k)=1;
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			id(k)=val,cnt(k)=1;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
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
}

namespace FHQTreap{
	const int MAXSIZE=MAXN*30;
	struct Node{
		int ch[2];
		int siz,val;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define lson(x) ch(x)[0]
		#define rson(x) ch(x)[1]
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int Val){
		reg int p=++tot;
		lson(p)=rson(p)=0;
		siz(p)=1;
		val(p)=Val;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
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
	inline void print(reg int p){
		if(p)
			print(lson(p)),printf("%d ",val(p)),print(rson(p));
		return;
	}
}

int n,m;
int a[MAXN];
int rt[MAXN];
using namespace FHQTreap;

int main(void){
	srand(time(0));
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		rt[i]=merge(New(-inf),New(inf));
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		static int rt1,rt2;
		split(rt[a[i]],i,rt1,rt2);
		rt[a[i]]=merge(merge(rt1,New(i)),rt2);
	}
	Segmentunit::build(1,1,n,a);
	for(reg int i=1;i<=m;++i){
		static int l,r,s,q;
		l=read(),r=read(),s=read(),q=read();
		reg int id=Segmentunit::query(1,1,n,l,r).id;
		static int rt1,mid,rt2;
		split(rt[id],r,rt1,rt2),split(rt1,l-1,rt1,mid);
		reg int sum=siz(mid);
		rt[id]=merge(merge(rt1,mid),rt2);
		if(sum>((r-l+1)>>1))
			s=id;
		printf("%d\n",s);
		while(q--){
			static int id;
			id=read();
			Segmentunit::update(1,1,n,id,s);
			static int rt1,mid,rt2;
			split(rt[a[id]],id,rt1,rt2),split(rt1,id-1,rt1,mid);
			rt[a[id]]=merge(rt1,rt2);
			a[id]=s;
			split(rt[a[id]],id,rt1,rt2);
			rt[a[id]]=merge(merge(rt1,mid),rt2);
		}
	}
	reg int id=Segmentunit::query(1,1,n,1,n).id;
	static int rt1,rt2;
	split(rt[id],n,rt1,rt2);
	reg int sum=siz(rt1)-1;
	printf("%d\n",sum>(n>>1)?id:-1);
	return 0;
}