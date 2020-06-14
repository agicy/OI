#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=500+5;
const int MAXM=500+5;
const int MAXP=1000+5;
const int MAXLEN=1000;

namespace UnionFind{
	int ID[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
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

struct Edge{
	int u,v;
	bitset<MAXLEN> w;
	inline Edge(void){
		return;
	}
	inline Edge(reg int U,reg int V,const bitset<MAXLEN> &W){
		u=U,v=V,w=W;
		return;
	}
};

struct Event{
	int l,r,u,v;
	bitset<MAXLEN> w;
	inline Event(void){
		return;
	}
	inline Event(reg int L,reg int R,reg int U,reg int V,const bitset<MAXLEN> &W){
		l=L,r=R,u=U,v=V,w=W;
		return;
	}
};

struct Basis{
	bitset<MAXLEN> p[MAXLEN];
	inline Basis(void){
		return;
	}
	inline void insert(const bitset<MAXLEN> &val){
		bitset<MAXLEN> x=val;
		for(reg int i=MAXLEN-1;i>=0;--i){
			if(!x[i])
				continue;
			if(!p[i].any()){
				p[i]=x;
				break;
			}
			else
				x^=p[i];
		}
		return;
	}
	inline bitset<MAXLEN> query(void){
		bitset<MAXLEN> res;
		res.reset();
		for(reg int i=MAXLEN-1;i>=0;--i)
			if(!res[i])
				res^=p[i];
		return res;
	}
};

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
bitset<MAXLEN> w[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,const bitset<MAXLEN> &len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bitset<MAXLEN> dis[MAXN];

inline void DFS(reg int ID,reg int father){
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			dis[to[i]]=dis[ID]^w[i];
			DFS(to[i],ID);
		}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	vector<Edge> val[MAXP<<2];
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,const Edge& E){
		if(L<=l&&r<=R){
			val[k].push_back(E);
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R,E);
		if(R>mid)
			Update(rson,mid+1,r,L,R,E);
		return;
	}
	inline void Query(reg int k,reg int l,reg int r,Basis B){
		for(reg int i=0,size=val[k].size();i<size;++i)
			B.insert(dis[val[k][i].u]^dis[val[k][i].v]^val[k][i].w);
		if(l==r){
			bitset<MAXLEN> res=B.query();
			reg bool flag=false;
			for(reg int i=MAXLEN-1;i>=0;--i){
				if(!flag&&res[i])
					flag=true;
				if(flag)
					putchar(res[i]+'0');
			}
			if(!flag)
				putchar('0');
			putchar('\n');
			return;
		}
		Query(lson,l,mid,B);
		Query(rson,mid+1,r,B);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m,P;
Edge E[MAXM];
Event Ev[MAXM+MAXP];
int pos[MAXP];

int main(void){
	scanf("%d%d%d",&n,&m,&P);
	using namespace UnionFind;
	Init(n);
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		static char str[1024];
		static bitset<MAXLEN> w;
		scanf("%d%d%s",&u,&v,str);
		w=bitset<MAXLEN>(str);
		E[i]=Edge(u,v,w);
		if(!search(E[i].u,E[i].v)){
			merge(E[i].u,E[i].v);
			Add_Edge(E[i].u,E[i].v,E[i].w);
			Add_Edge(E[i].v,E[i].u,E[i].w);
		}
		else
			Ev[++tot]=Event(0,P,E[i].u,E[i].v,E[i].w);
	}
	DFS(1,0);
	reg int num=0;
	for(reg int i=1;i<=P;++i){
		static char opt[8],str[1024];
		static bitset<MAXLEN> z;
		scanf("%s",opt);
		if(opt[0]=='A'){
			static int x,y;
			scanf("%d%d%s",&x,&y,str);
			z=bitset<MAXLEN>(str);
			Ev[++tot]=Event(i,P,x,y,z);
			pos[++num]=tot;
		}
		else if(opt[1]=='a'){
			static int k;
			scanf("%d",&k);
			Ev[pos[k]].r=i-1;
			pos[k]=0;
		}
		else if(opt[1]=='h'){
			static int k;
			scanf("%d%s",&k,str);
			z=bitset<MAXLEN>(str);
			Ev[pos[k]].r=i-1;
			Ev[++tot]=Event(i,P,Ev[pos[k]].u,Ev[pos[k]].v,z);
			pos[k]=tot;
		}
	}
	using namespace SegmentTree;
	for(reg int i=1;i<=tot;++i)
		Update(1,0,P,Ev[i].l,Ev[i].r,Edge(Ev[i].u,Ev[i].v,Ev[i].w));
	Basis B;
	Query(1,0,P,B);
	return 0;
}