#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXSIZE=MAXN*60+5;

struct SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int val;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define val(x) unit[(x)].val
	};
	int tot;
	int cnt;
	int root[MAXN];
	Node unit[MAXSIZE];
	inline SegmentTree(void){
		tot=cnt=0;
		memset(root,0,sizeof(root));
		return;
	}
	inline void build1(reg int &k,reg int l,reg int r){
		if(!k)
			k=++tot;
		if(l==r){
			val(k)=1;
			return;
		}
		build1(lson(k),l,mid),build1(rson(k),mid+1,r);
		return;
	}
	inline void buildi(reg int &k,reg int l,reg int r){
		if(!k)
			k=++tot;
		if(l==r){
			val(k)=l;
			return;
		}
		buildi(lson(k),l,mid),buildi(rson(k),mid+1,r);
		return;
	}
	inline void add(reg int &k,reg int pre,reg int l,reg int r,reg int pos,reg int Val){
		if(!k)
			k=++tot;
		if(l==r){
			val(k)=val(pre)+Val;
			return;
		}
		lson(k)=lson(pre),rson(k)=rson(pre);
		if(pos<=mid)
			rson(k)=rson(pre),add(lson(k),lson(pre),l,mid,pos,Val);
		else
			lson(k)=lson(pre),add(rson(k),rson(pre),mid+1,r,pos,Val);
		return;
	}
	inline void set(reg int &k,reg int pre,reg int l,reg int r,reg int pos,reg int Val){
		if(!k)
			k=++tot;
		if(l==r){
			val(k)=Val;
			return;
		}
		if(pos<=mid)
			rson(k)=rson(pre),set(lson(k),lson(pre),l,mid,pos,Val);
		else
			lson(k)=lson(pre),set(rson(k),rson(pre),mid+1,r,pos,Val);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos){
		if(!k)
			return 0;
		if(l==r)
			return val(k);
		if(pos<=mid)
			return query(lson(k),l,mid,pos);
		else
			return query(rson(k),mid+1,r,pos);
	}
	inline void print(reg int k,reg int l,reg int r){
		if(l==r){
			printf("%d ",val(k));
			return;
		}
		print(lson(k),l,mid),print(rson(k),mid+1,r);
		return;
	}
	#undef mid
};

namespace UnionFind{
	int n;
	int tot;
	pair<int,int> root[MAXN];
	SegmentTree fa,dep;
	inline void Init(reg int S){
		n=S;
		tot=0;
		fa.buildi(fa.root[0],1,n);
		dep.build1(dep.root[0],1,n);
		root[0]=make_pair(0,0);
		return;
	}
	inline int find(reg int id,reg int x){
		reg int tmp;
		while(tmp=fa.query(fa.root[root[id].first],1,n,x),x!=tmp)
			x=tmp;
		return x;
	}
	inline void merge(reg int id,reg int a,reg int b){
		int ra=fa.query(fa.root[root[id].first],1,n,a);
		int rb=fa.query(fa.root[root[id].first],1,n,b);
		int da=dep.query(dep.root[root[id].second],1,n,a);
		int db=dep.query(dep.root[root[id].second],1,n,b);
		if(ra!=rb){
			if(da<db)
				swap(ra,rb);
			fa.set(fa.root[++fa.cnt],fa.root[root[id].first],1,n,rb,ra);
			if(da==db)
				dep.add(dep.root[++dep.cnt],dep.root[root[id].second],1,n,ra,1);
			root[++tot]=make_pair(fa.cnt,dep.cnt);
		}
		return;
	}
	inline bool search(reg int id,reg int a,reg int b){
		reg int ra=fa.query(fa.root[root[id].first],1,n,a);
		reg int rb=fa.query(fa.root[root[id].second],1,n,b);
		return ra==rb;
	}
	inline void print(reg int id){
		printf("(%d,%d)\n",root[id].first,root[id].second);
		puts("fa");
		fa.print(fa.root[root[id].first],1,n);
		puts("");
		puts("dep");
		dep.print(dep.root[root[id].second],1,n);
		puts("");
		return;
	}
}

const int MAXM=2e5+5;

int n,m;
int id[MAXM];

int main(void){
	n=read(),m=read();
	UnionFind::Init(n);
	id[0]=UnionFind::tot;
	//UnionFind::print(UnionFind::tot);
	for(reg int i=1;i<=m;++i){
		static int op,k,a,b;
		op=read();
		switch(op){
			case 1:{
				a=read(),b=read();
				UnionFind::merge(UnionFind::tot,a,b);
				break;
			}
			case 2:{
				k=read();
				UnionFind::tot=id[k];
				break;
			}
			case 3:{
				a=read(),b=read();
				reg bool ans=UnionFind::search(UnionFind::tot,a,b);
				printf("%d\n",ans);
				break;
			}
		}
		id[i]=UnionFind::tot;
		//printf("i=%d tot=%d\n",i,UnionFind::tot);
		//UnionFind::print(UnionFind::tot);
		//puts("");
	}
	return 0;
}