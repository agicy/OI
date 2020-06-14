#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 1000000007
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=res*10+ch-'0',ch=getchar();
	return res;
}

inline int Add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=MOD?sum-MOD:sum;
}

inline int Mul(reg int a,reg int b){
	return 1ll*a*b%MOD;
}

const int MAXN=100000+5;
const int MAXM=100000+5;
const int MAXX=200000+5;

const int X=100000+50;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

const ull base=17;

int base2p[MAXX<<1];
ull basep[MAXX<<1];

inline void InitBase(reg int size){
	base2p[0]=basep[0]=1;
	for(reg int i=1;i<=size;++i){
		base2p[i]=Add(base2p[i-1],base2p[i-1]);
		basep[i]=basep[i-1]*base;
	}
	return;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		ull cnt,sum;
		ull Hash;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define cnt(x) unit[(x)].cnt
		#define sum(x) unit[(x)].sum
		#define Hash(x) unit[(x)].Hash
	};
	const int MAXSIZE=MAXN*50;
	int tot,root[MAXN];
	Node unit[MAXSIZE];
	inline void pushup(reg int k){
		cnt(k)=cnt(lson(k))+cnt(rson(k));
		sum(k)=Add(sum(lson(k)),sum(rson(k)));
		Hash(k)=Hash(lson(k))+Hash(rson(k));
		return;
	}
	inline int Build(reg int l,reg int r,reg int val){
		reg int k=++tot;
		if(l==r){
			cnt(k)=val;
			sum(k)=Mul(base2p[l],val);
			Hash(k)=basep[l]*val;
			return k;
		}
		lson(k)=Build(l,mid,val);
		rson(k)=Build(mid+1,r,val);
		pushup(k);
		return k;
	}
	inline int QueryCnt(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return cnt(k);
		reg int res=0;
		if(L<=mid)
			res+=QueryCnt(lson(k),l,mid,L,R);
		if(R>mid)
			res+=QueryCnt(rson(k),mid+1,r,L,R);
		return res;
	}
	inline int QuerySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k);
		reg int res=0;
		if(L<=mid)
			res=Add(res,QuerySum(lson(k),l,mid,L,R));
		if(R>mid)
			res=Add(res,QuerySum(rson(k),mid+1,r,L,R));
		return res;
	}
	inline ull QueryHash(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Hash(k);
		reg ull res=0;
		if(L<=mid)
			res=res+QueryHash(lson(k),l,mid,L,R);
		if(R>mid)
			res=res+QueryHash(rson(k),mid+1,r,L,R);
		return res;
	}
	inline int find(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return l;
		if(pos>mid)
			return find(rson(k),mid+1,r,pos);
		if(QueryCnt(lson(k),l,mid,pos,mid)==mid-pos+1)
			return find(rson(k),mid+1,r,mid+1);
		else
			return find(lson(k),l,mid,pos);
	}
	inline int insert(reg int pre,reg int l,reg int r,reg int pos){
		reg int k=++tot;
		lson(k)=lson(pre),rson(k)=rson(pre);
		if(l==r){
			cnt(k)=1;
			sum(k)=base2p[l];
			Hash(k)=basep[l];
			return k;
		}
		if(pos<=mid)
			lson(k)=insert(lson(pre),l,mid,pos);
		else
			rson(k)=insert(rson(pre),mid+1,r,pos);
		pushup(k);
		return k;
	}
	inline int move(reg int p,reg int q,reg int l,reg int r,reg int L,reg int R){
		if(R<l||r<L)
			return p;
		if(L<=l&&r<=R)
			return q;
		reg int k=++tot;
		lson(k)=move(lson(p),lson(q),l,mid,L,R);
		rson(k)=move(rson(p),rson(q),mid+1,r,L,R);
		pushup(k);
		return k;
	}
	inline int Add(reg int k,reg int l,reg int r,reg int w){
		reg int pos=find(k,l,r,w);
		reg int temp=insert(k,l,r,pos);
		if(pos==w)
			return temp;
		temp=move(temp,root[0],l,r,w,pos-1);
		return temp;
	}
	inline bool same(reg int p,reg int q){
		return cnt(p)==cnt(q)&&sum(p)==sum(q)&&Hash(p)==Hash(q);
	}
	inline bool cmp(reg int p,reg int q,reg int l,reg int r){
		if(l==r)
			return cnt(p)<=cnt(q);
		if(same(rson(p),rson(q)))
			return cmp(lson(p),lson(q),l,mid);
		else
			return cmp(rson(p),rson(q),mid+1,r);
	}
	#undef lson
	#undef rson
	#undef cnt
	#undef sum
	#undef Hash
	#undef mid
}

struct Node{
	int id,root;
	inline Node(reg int id=0,reg int root=0):id(id),root(root){
		return;
	}
};

namespace Heap{
	#define lson(x) ch[(x)][0]
	#define rson(x) ch[(x)][1]
	const int MAXSIZE=400000+5;
	int tot,Root,size;
	Node unit[MAXSIZE];
	int ch[MAXSIZE][2],dep[MAXSIZE];
	inline int merge(int p,int q){
		if(!p||!q)
			return p+q;
		if(SegmentTree::cmp(unit[q].root,unit[p].root,0,X))
			swap(p,q);
		rson(p)=merge(rson(p),q);
		if(dep[rson(p)]>dep[lson(p)])
			swap(lson(p),rson(p));
		dep[p]=dep[lson(p)]+1;
		return p;
	}
	inline void push(const Node& a){
		++size;
		unit[++tot]=a;
		Root=merge(tot,Root);
		return;
	}
	inline void pop(void){
		--size;
		Root=merge(lson(Root),rson(Root));
		return;
	}
	inline Node top(void){
		return unit[Root];
	}
	inline bool empty(void){
		return size==0;
	}
	#undef lson
	#undef rson
}

bool vis[MAXN];
int from[MAXN];

using SegmentTree::Build;
using SegmentTree::cmp;
using SegmentTree::Add;
using SegmentTree::QuerySum;
using SegmentTree::root;

inline void Dijkstra(reg int s,reg int t){
	int inf=Build(0,X,1);
	for(reg int i=1;i<=n;++i)
		root[i]=inf;
	root[0]=root[s]=Build(0,X,0);
	Heap::push(Node(s,root[s]));
	while(!Heap::empty()){
		while(!Heap::empty()&&vis[Heap::top().id])
			Heap::pop();
		if(Heap::empty())
			break;
		reg int ID=Heap::top().id;
		Heap::pop();
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i]){
			reg int v=to[i];
			if(vis[to[i]])
				continue;
			int temp=Add(root[ID],0,X,w[i]);
			if(cmp(root[v],temp,0,X))
				continue;
			root[v]=temp;
			from[v]=ID;
			Heap::push(Node(v,root[v]));
		}
	}
	if(root[t]==inf)
		puts("-1");
	else{
		printf("%d\n",QuerySum(root[t],0,X,0,X));
		static int path[MAXN];
		reg int tot=0;
		for(reg int i=t;i!=s;i=from[i])
			path[++tot]=i;
		path[++tot]=s;
		printf("%d\n",tot);
		for(reg int i=tot;i>=1;--i)
			printf("%d%c",path[i],i==1?'\n':' ');
	}
	return;
}

signed main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,x;
		u=read(),v=read(),x=read();
		Add_Edge(u,v,x);
		Add_Edge(v,u,x);
	}
	InitBase(X);
	reg int s=read(),t=read();
	Dijkstra(s,t);
	return 0;
}