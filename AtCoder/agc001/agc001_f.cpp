#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

const int MAXN=5e5+5;
const int inf=0x3f3f3f3f;

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
	inline void build(reg int k,reg int l,reg int r){
		Min(k)=inf;
		if(l!=r)
			build(lson,l,mid),build(rson,mid+1,r);
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

int n,k;
int a[MAXN];
int b[MAXN];
int inDeg[MAXN];
vector<int> G[MAXN];

inline void Add_Edge(reg int u,int v){
	++inDeg[v];
	G[u].push_back(v);
	return;
}

inline void topo(void){
	priority_queue<int> Q;
	for(int i=1;i<=n;++i)
		if(!inDeg[i])
			Q.push(i);
	reg int tot=0;
	while(!Q.empty()){
		reg int u=Q.top();
		Q.pop();
		b[++tot]=u;
		for(int v:G[u]){
			--inDeg[v];
			if(!inDeg[v])
				Q.push(v);
		}
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[read()]=i;
	reverse(a+1,a+n+1);
	SegmentTree::build(1,1,n);
	for(reg int i=n;i>=1;--i){
		reg int x=SegmentTree::query(1,1,n,max(1,a[i]-k+1),a[i]);
		if(1<=x&&x<=n)
			Add_Edge(a[i],a[x]);
		x=SegmentTree::query(1,1,n,a[i],min(n,a[i]+k-1));
		if(1<=x&&x<=n)
			Add_Edge(a[i],a[x]);
		SegmentTree::update(1,1,n,a[i],i);
	}
	topo();
	reverse(b+1,b+n+1);
	static int ans[MAXN];
	for(reg int i=1;i<=n;++i)
		ans[b[i]]=i;
	for(reg int i=1;i<=n;++i)
		writeln(ans[i]);
	flush();
	return 0;
}