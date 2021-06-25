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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;
const int inf=0x3f3f3f3f;

namespace ST{
	int lg[MAXN];
	int Min[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			lg[i]=lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Min[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				Min[j][i]=min(Min[j-1][i],Min[j-1][i+(1<<(j-1))]);
		return;
	}
	inline int query(reg int l,reg int r){
		reg int k=lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

int n,k;
int b[MAXN];

inline int query(reg int l,reg int r){
	if(r-l+1>=n)
		return ST::query(1,n);
	else{
		reg int lef=(l-1)%n+1,rig=(r-1)%n+1;
		reg int ldep=(l-1)/n,rdep=(r-1)/n;
		if(ldep!=rdep)
			return min(ST::query(lef,n),ST::query(1,rig));
		else
			return ST::query(lef,rig);
	}
}

namespace SegmentTree{
	const int MAXSIZE=2e7+5;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int Min,tCov;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Min(x) unit[(x)].Min
		#define tCov(x) unit[(x)].tCov
	};
	int tot;
	Node unit[MAXSIZE];
	inline void Init(void){
		tot=0,Min(0)=inf;
		return;
	}
	inline int New(reg int l,reg int r){
		reg int p=++tot;
		lson(p)=rson(p)=0,Min(p)=query(l,r),tCov(p)=inf;
		return p;
	}
	inline void pushup(reg int p){
		Min(p)=min(Min(lson(p)),Min(rson(p)));
		return;
	}
	inline void cover(reg int p,reg int val){
		Min(p)=tCov(p)=val;
		return;
	}
	inline void pushdown(reg int p){
		if(tCov(p)!=inf){
			cover(lson(p),tCov(p)),cover(rson(p),tCov(p));
			tCov(p)=inf;
		}
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(!p)
			p=New(l,r);
		if(L<=l&&r<=R){
			cover(p,val);
			return;
		}
		if(!lson(p)) lson(p)=New(l,mid);
		if(!rson(p)) rson(p)=New(mid+1,r);
		pushdown(p);
		if(L<=mid)
			update(lson(p),l,mid,L,R,val);
		if(R>mid)
			update(rson(p),mid+1,r,L,R,val);
		pushup(p);
		return;
	}
	inline int query(reg int &p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			p=New(l,r);
		if(L<=l&&r<=R)
			return Min(p);
		if(!lson(p)) lson(p)=New(l,mid);
		if(!rson(p)) rson(p)=New(mid+1,r);
		pushdown(p);
		if(L<=mid&&mid<R)
			return min(query(lson(p),l,mid,L,R),query(rson(p),mid+1,r,L,R));
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef Min
	#undef tCov
}

int rt;

int main(void){
	n=read(),k=read();
	reg int m=n*k;
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	ST::Init(n,b);
	SegmentTree::Init();
	reg int q=read();
	while(q--){
		static int opt,l,r,x;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 1:{
				x=read();
				SegmentTree::update(rt,1,m,l,r,x);
				break;
			}
			case 2:{
				writeln(SegmentTree::query(rt,1,m,l,r));
				break;
			}
		}
	}
	flush();
	return 0;
}