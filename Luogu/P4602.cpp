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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
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

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Node{
	int d,p,l;
	inline bool operator<(const Node& a)const{
		return d<a.d;
	}
};

struct querys{
	ll g,L;
};

int n,m;
Node a[MAXN];
querys q[MAXM];
int id[MAXM];
int ans[MAXM];

namespace SegmentTree{
	const int MAXSIZE=5e6+5;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		ll sump,suml;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sump(x) unit[(x)].sump
		#define suml(x) unit[(x)].suml
	};
	int tot;
	Node unit[MAXSIZE];
	inline int insert(reg int pre,reg int l,reg int r,reg int pos,reg int P,reg int L){
		reg int p=++tot;
		unit[p]=unit[pre];
		sump(p)+=1ll*P*L,suml(p)+=L;
		if(l!=r){
			if(pos<=mid)
				lson(p)=insert(lson(pre),l,mid,pos,P,L);
			else
				rson(p)=insert(rson(pre),mid+1,r,pos,P,L);
		}
		return p;
	}
	inline ll query(reg int p,reg int pre,reg int l,reg int r,reg ll L){
		if(suml(p)-suml(pre)<L)
			return inf;
		if(l==r)
			return l*L;
		reg ll sum=suml(lson(p))-suml(lson(pre));
		if(L<=sum)
			return query(lson(p),lson(pre),l,mid,L);
		else
			return sump(lson(p))-sump(lson(pre))+query(rson(p),rson(pre),mid+1,r,L-sum);
	}
	#undef mid
}

int P;
int rt[MAXN];

inline void solve(reg int L,reg int R,reg int l,reg int r){
	if(L>R||l>r)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			if(SegmentTree::query(rt[n],rt[l-1],1,P,q[id[i]].L)<=q[id[i]].g)
				ans[id[i]]=a[l].d;
		return;
	}
	reg int mid=(l+r)>>1;
	reg int cntl=0,cntr=0;
	static int idl[MAXN],idr[MAXN];
	for(reg int i=L;i<=R;++i)
		if(SegmentTree::query(rt[n],rt[mid],1,P,q[id[i]].L)<=q[id[i]].g)
			idr[++cntr]=id[i];
		else
			idl[++cntl]=id[i];
	for(reg int i=1;i<=cntl;++i)
		id[L+i-1]=idl[i];
	for(reg int i=1;i<=cntr;++i)
		id[R-i+1]=idr[i];
	solve(L,L+cntl-1,l,mid),solve(R-cntr+1,R,mid+1,r);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i].d=read(),a[i].p=read(),a[i].l=read();
		P=max(P,a[i].p);
	}
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		rt[i]=SegmentTree::insert(rt[i-1],1,P,a[i].p,a[i].p,a[i].l);
	for(reg int i=1;i<=m;++i){
		id[i]=i;
		q[i].g=readll(),q[i].L=readll();
	}
	fill(ans+1,ans+m+1,-1);
	solve(1,m,1,n);
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}