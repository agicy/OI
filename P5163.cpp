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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXQ=2e5+5;

int n,m,Q;
int a[MAXN];
vector<int> V;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*30;
	struct Node{
		int lson,rson;
		int cnt;
		ll sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=++tot;
		if(val==1)
			sum(p)+=V[pos-1],++cnt(p);
		else
			sum(p)-=V[pos-1],--cnt(p);
		if(l!=r){
			if(pos<=mid)
				update(lson(p),l,mid,pos,val);
			else
				update(rson(p),mid+1,r,pos,val);
		}
		return;
	}
	inline void merge(reg int &p,reg int q,reg int l,reg int r){
		if(!p||!q){
			p|=q;
			return;
		}
		cnt(p)+=cnt(q),sum(p)+=sum(q);
		if(l!=r){
			merge(lson(p),lson(q),l,mid);
			merge(rson(p),rson(q),mid+1,r);
		}
		return;
	}
	inline ll query(reg int p,reg int l,reg int r,reg int k){
		if(!k||!p)
			return 0;
		if(l==r)
			return 1ll*min(k,cnt(p))*V[l-1];
		if(cnt(rson(p))<=k)
			return sum(rson(p))+query(lson(p),l,mid,k-cnt(rson(p)));
		else
			return query(rson(p),mid+1,r,k);
	}
	#undef mid
}

int rt[MAXN];

struct Edge{
	int u,v,t;
	inline bool operator<(const Edge& a)const{
		return t<a.t;
	}
};

struct querys{
	int opt,x,y;
};

Edge e[MAXM];
querys q[MAXQ];
int ptr;

namespace UnionFind1{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb){
			fa[rb]=ra;
			SegmentTree::merge(rt[ra],rt[rb],1,V.size());
		}
		return;
	}
}

namespace UnionFind2{
	int fa[MAXN],siz[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return find(fa[x]);
	}
	struct Event{
		int ra,rb,ptr;
		inline Event(reg int ra=0,reg int rb=0,reg int ptr=0):ra(ra),rb(rb),ptr(ptr){
			return;
		}
	};
	stack<Event> S;
	inline bool merge(reg int a,reg int b){
		int ra=find(a),rb=find(b);
		if(ra!=rb){
			if(siz[ra]<siz[rb])
				swap(ra,rb);
			S.push(Event(ra,rb,ptr));
			fa[rb]=ra,siz[ra]+=siz[rb];
			return true;
		}
		else
			return false;
	}
	inline void back(reg int t){
		while(!S.empty()&&S.top().ptr==t){
			static Event s;
			s=S.top();
			S.pop();
			reg int ra=s.ra,rb=s.rb;
			fa[rb]=rb,siz[ra]-=siz[rb];
		}
		return;
	}
}

vector<int> G[MAXN];
bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(int v:G[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		while(S[top]!=u){
			reg int v=S[top--];
			vis[v]=false;
			UnionFind2::merge(v,u);
		}
		--top;
		vis[u]=false;
	}
	return;
}

int p[MAXM<<1],cnt;

inline void solve(reg int l,reg int r,reg int L,reg int R){
	if(L>R||l>r)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			e[i].t=l;
		return;
	}
	reg int mid=(l+r)>>1,las=cnt;
	reg int tmp=++ptr;
	for(reg int i=L;i<=R;++i){
		int u=UnionFind2::find(e[i].u),v=UnionFind2::find(e[i].v);
		if(u!=v&&e[i].t>mid)
			G[u].push_back(v),p[++cnt]=u,p[++cnt]=v;
	}
	tim=0;
	for(reg int i=las+1;i<=cnt;++i)
		if(!dfn[p[i]])
			tarjan(p[i]);
	reg int cntr=0,cntl=0;
	static Edge idr[MAXM],idl[MAXM];
	for(reg int i=L;i<=R;++i)
		if(UnionFind2::find(e[i].u)==UnionFind2::find(e[i].v)&&e[i].t>mid)
			idr[++cntr]=e[i];
		else
			idl[++cntl]=e[i];
	for(reg int i=1;i<=cntl;++i)
		e[L+i-1]=idl[i];
	for(reg int i=1;i<=cntr;++i)
		e[R-i+1]=idr[i];
	for(reg int i=las+1;i<=cnt;++i)
		G[p[i]].clear(),dfn[p[i]]=low[p[i]]=0,p[i]=0;
	cnt=las;
	solve(l,mid,L,L+cntl-1);
	UnionFind2::back(tmp);
	solve(mid+1,r,R-cntr+1,R);
	return;
}

ll ans[MAXQ];

signed main(void){
	n=read(),m=read(),Q=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	map<pair<int,int>,int> M;
	for(reg int i=1;i<=m;++i){
		e[i].u=read(),e[i].v=read(),e[i].t=Q;
		M[make_pair(e[i].u,e[i].v)]=i;
	}
	for(reg int i=1;i<=Q;++i){
		q[i].opt=read(),q[i].x=read(),q[i].y=read();
		if(q[i].opt==2)
			V.push_back(a[q[i].x]+=q[i].y);
		if(q[i].opt==1)
			e[M[make_pair(q[i].x,q[i].y)]].t=i-1;
	}
	sort(e+1,e+m+1);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	UnionFind2::Init(n);
	solve(0,Q,1,m);
	UnionFind1::Init(n);
	for(reg int i=1;i<=n;++i)
		SegmentTree::update(rt[i],1,V.size(),a[i],1);
	sort(e+1,e+m+1);
	reg int ptr=m+1;
	for(reg int i=Q;i>=1;--i){
		if(q[i].opt==1)
			continue;
		while(ptr&&e[ptr-1].t>=i)
			--ptr,UnionFind1::merge(e[ptr].u,e[ptr].v);
		if(q[i].opt==2){
			SegmentTree::update(rt[UnionFind1::find(q[i].x)],1,V.size(),a[q[i].x],-1);
			a[q[i].x]=lower_bound(V.begin(),V.end(),V[a[q[i].x]-1]-q[i].y)-V.begin()+1;
			SegmentTree::update(rt[UnionFind1::find(q[i].x)],1,V.size(),a[q[i].x],1);
		}
		else
			ans[i]=SegmentTree::query(rt[UnionFind1::find(q[i].x)],1,V.size(),q[i].y);
	}
	for(reg int i=1;i<=Q;++i)
		if(q[i].opt==3)
			writeln(ans[i]);
	flush();
	return 0;
}