#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXM=500000+5;
const int MAXLOG2N=18+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Edge{
	int from,to,len;
	inline Edge(reg int from=0,reg int to=0,reg int len=0):from(from),to(to),len(len){
		return;
	}
	inline bool operator<(const Edge &a)const{
		return len<a.len;
	}
};

int n,m,q;
int h[MAXN];
vector<int> V;
Edge E[MAXM];
int v[MAXN<<1];

inline void Read(void){
	n=read(),m=read(),q=read();
	for(reg int i=1;i<=n;++i){
		h[i]=read();
		V.push_back(h[i]);
	}
	sort(V.begin(),V.end());
	for(reg int i=1;i<=n;++i)
		h[i]=lower_bound(V.begin(),V.end(),h[i])-V.begin()+1;
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		E[i]=Edge(a,b,c);
	}
	return;
}

namespace UnionFind{
	int ID[MAXN<<1];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

using namespace UnionFind;

int Count;

int cnt,head[MAXN<<1],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	int tot;
	int root[MAXN<<1];
	int lson[MAXSIZE],rson[MAXSIZE];
	int size[MAXSIZE];
	inline void pushup(reg int k){
		size[k]=size[lson[k]]+size[rson[k]];
		return;
	}
	inline int Build(reg int l,reg int r){
		reg int k=++tot;
		if(l!=r){
			lson[k]=Build(l,mid);
			rson[k]=Build(mid+1,r);
			pushup(k);
		}
		return k;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg int pos,reg int val){
		reg int k=++tot;
		lson[k]=lson[pre],rson[k]=rson[pre],size[k]=size[pre]+val;
		if(l!=r){
			if(pos<=mid)
				lson[k]=Update(lson[pre],l,mid,pos,val);
			if(pos>mid)
				rson[k]=Update(rson[pre],mid+1,r,pos,val);
			pushup(k);
		}
		return k;
	}
	inline int Query(reg int pre,reg int now,reg int l,reg int r,reg int K){
		if(l==r)
			return l;
		reg int sum=size[rson[now]]-size[rson[pre]];
		if(K<=sum)
			return Query(rson[pre],rson[now],mid+1,r,K);
		else
			return Query(lson[pre],lson[now],l,mid,K-sum);
	}
	#undef mid
}

using namespace SegmentTree;

int fa[MAXN<<1][MAXLOG2N];
int tim,l[MAXN<<1],r[MAXN<<1];

inline void DFS(reg int ID,reg int father){
	fa[ID][0]=father;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	l[ID]=tim;
	if(!head[ID]){
		l[ID]=++tim;
		root[l[ID]]=Update(root[l[ID]-1],1,n,h[ID],1);
		return;
	}
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID);
	r[ID]=tim;
	return;
}

inline void Work(void){
	sort(E+1,E+m+1);
	reg int cnt=0;
	Init(2*n);
	Count=n;
	for(reg int i=1;i<=m&&cnt<n-1;++i)
		if(!search(E[i].from,E[i].to)){
			++cnt;
			reg int k=++Count,fa=find(E[i].from),fb=find(E[i].to);
			v[k]=E[i].len;
			Add_Edge(k,fa),Add_Edge(k,fb);
			merge(k,fa),merge(k,fb);
		}
	root[0]=Build(1,n);
	DFS(Count,0);
	while(q--){
		static int ID,x,k;
		ID=read(),x=read(),k=read();
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(fa[ID][i]&&v[fa[ID][i]]<=x)
				ID=fa[ID][i];
		if(r[ID]-l[ID]<k)
			puts("-1");
		else
			printf("%d\n",V[Query(root[l[ID]],root[r[ID]],1,n,k)-1]);
	}
	return;
}