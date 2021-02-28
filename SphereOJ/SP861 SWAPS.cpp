#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2.5e5+5;
const int MAXA=5e4+5;

int n,m;
int a[MAXN];

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXA];
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
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

const int A=5e4;

namespace BIT2{
	namespace SegmentTree{
		const int MAXSIZE=2e7+5;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			int siz;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define siz(x) unit[(x)].siz
		};
		int tot;
		Node unit[MAXSIZE];
		inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
			if(!p)
				p=++tot;
			siz(p)+=val;
			if(l!=r){
				if(pos<=mid)
					update(lson(p),l,mid,pos,val);
				else
					update(rson(p),mid+1,r,pos,val);
			}
			return;
		}
		inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
			if(!p)
				return 0;
			if(L<=l&&r<=R)
				return siz(p);
			if(L<=mid&&mid<R)
				return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
			else if(L<=mid)
				return query(lson(p),l,mid,L,R);
			else
				return query(rson(p),mid+1,r,L,R);
		}
		#undef mid
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,rt[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(rt,0,sizeof(rt));
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,A,pos,val);
		return;
	}
	inline int query(reg int id,reg int L,reg int R){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=SegmentTree::query(rt[i],1,A,L,R);
		return res;
	}
	inline int query(reg int l,reg int r,reg int L,reg int R){
		return query(r,L,R)-query(l-1,L,R);
	}
}

int main(void){
	n=read();
	BIT1::Init(A),BIT2::Init(n);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		BIT1::update(a[i],1);
		ans+=i-BIT1::query(a[i]);
		BIT2::update(i,a[i],1);
	}
	m=read();
	while(m--){
		static int x,y;
		x=read(),y=read();
		if(a[x]!=y){
			if(1<x){
				if(a[x]<A)
					ans-=BIT2::query(1,x-1,a[x]+1,A);
				if(y<A)
					ans+=BIT2::query(1,x-1,y+1,A);
			}
			if(x<n){
				if(1<a[x])
					ans-=BIT2::query(x+1,n,1,a[x]-1);
				if(1<y)
					ans+=BIT2::query(x+1,n,1,y-1);
			}
			BIT2::update(x,a[x],-1);
			a[x]=y;
			BIT2::update(x,a[x],1);
		}
		writeln(ans);
	}
	flush();
	return 0;
}