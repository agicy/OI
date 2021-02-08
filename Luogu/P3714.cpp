#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int inf=0x3f3f3f3f;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m,l,r;
int c[MAXM];
vector<Edge> G[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	G[u].push_back(Edge(v,len));
	return;
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*40;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson,val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define val(x) unit[(x)].val
	};
	int tot;
	Node unit[MAXSIZE];
	inline void Init(void){
		tot=0;
		return;
	}
	inline int New(void){
		reg int p=++tot;
		lson(p)=rson(p)=0,val(p)=-inf;
		return p;
	}
	inline void pushup(reg int k){
		val(k)=max(val(lson(k)),val(rson(k)));
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int Val){
		if(!p)
			p=New();
		if(l==r){
			val(p)=max(val(p),Val);
			return;
		}
		if(pos<=mid)
			update(lson(p),l,mid,pos,Val);
		else
			update(rson(p),mid+1,r,pos,Val);
		pushup(p);
		return;
	}
	inline int merge(reg int p,reg int q,reg int l,reg int r){
		if(!p||!q)
			return p|q;
		if(l==r)
			val(p)=max(val(p),val(q));
		else{
			lson(p)=merge(lson(p),lson(q),l,mid),
			rson(p)=merge(rson(p),rson(q),mid+1,r);
			pushup(p);
		}
		return p;
	}
	inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return -inf;
		if(L<=l&&r<=R)
			return val(p);
		if(L<=mid&&mid<R)
			return max(query(lson(p),l,mid,L,R),query(rson(p),mid+1,r,L,R));
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef val
}

int rt,MaxPart,sum;
bool del[MAXN];
int siz[MAXN];

inline void getRt(reg int u,reg int father){
	siz[u]=1;
	reg int Max=0;
	for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
		reg int v=it->v;
		if(v!=father&&!del[v]){
			getRt(v,u);
			siz[u]+=siz[v];
			Max=max(Max,siz[v]);
		}
	}
	Max=max(Max,sum-siz[u]);
	if(Max<MaxPart)
		rt=u,MaxPart=Max;
	return;
}

struct Node{
	int dep,val;
	inline Node(reg int dep=0,reg int val=0):dep(dep),val(val){
		return;
	}
};

int top;
Node S[MAXN];

inline void dfs(reg int u,reg int father,reg int val,reg int dep,reg int las){
	if(dep>r)
		return;
	S[++top]=Node(dep,val);
	for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
		reg int v=it->v,w=it->w;
		if(v!=father&&!del[v])
			dfs(v,u,(las==w)?val:val+c[w],dep+1,w);
	}
	return;
}

int ans=-inf;

inline void calc(reg int u){
	int rt1=0,rt2=0;
	SegmentTree::Init();
	reg int las=0;
	for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
		reg int v=it->v;
		if(!del[v]){
			top=0;
			reg bool flag=false;
			dfs(v,u,c[it->w],1,it->w);
			if(it->w==las)
				flag=true;
			else{
				rt1=SegmentTree::merge(rt1,rt2,1,n);
				rt2=0;
			}
			for(reg int j=1;j<=top;++j){
				if(flag)
					ans=max(ans,SegmentTree::query(rt2,1,n,max(1,l-S[j].dep),r-S[j].dep)+S[j].val-c[las]);
				ans=max(ans,SegmentTree::query(rt1,1,n,max(1,l-S[j].dep),r-S[j].dep)+S[j].val);
				if(l<=S[j].dep&&S[j].dep<=r)
					ans=max(ans,S[j].val);
			}
			for(reg int j=1;j<=top;++j)
				SegmentTree::update(rt2,1,n,S[j].dep,S[j].val);
			las=it->w;
		}
	}
	return;
}

inline void solve(reg int u){
	calc(u);
	del[u]=true;
	for(vector<Edge>::iterator it=G[u].begin();it!=G[u].end();++it){
		reg int v=it->v;
		if(!del[v]){
			rt=0,MaxPart=inf,sum=siz[v];
			getRt(v,u),solve(rt);
		}
	}
	return;
}

int main(void){
	SegmentTree::unit[0].val=-inf;
	n=read(),m=read(),l=read(),r=read();
	for(reg int i=1;i<=m;++i)
		c[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v,c;
		u=read(),v=read(),c=read();
		Add_Edge(u,v,c),Add_Edge(v,u,c);
	}
	for(reg int i=1;i<=n;++i)
		sort(G[i].begin(),G[i].end());
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	printf("%d\n",ans);
	return 0;
}