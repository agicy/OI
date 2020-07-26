#include<bits/stdc++.h>
using namespace std;
#define reg register
#define MOD 201314
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

const int MAXN=50000+5;
const int MAXM=50000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Querys{
	int id,pos,z;
	bool flag;
	inline Querys(reg int id=0,reg int pos=0,reg int z=0,reg bool flag=false):id(id),pos(pos),z(z),flag(flag){
		return;
	}
	inline bool operator<(const Querys &a)const{
		return pos<a.pos;
	}
};

int n,m;
int tot;
Querys Q[MAXM<<1];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=2;i<=n;++i){
		static int fa;
		fa=read()+1;
		Add_Edge(fa,i);
	}
	for(reg int i=1;i<=m;++i){
		static int l,r,z;
		l=read(),r=read()+1,z=read()+1;
		Q[++tot]=Querys(i,l,z,0);
		Q[++tot]=Querys(i,r,z,1);
	}
	return;
}

int fa[MAXN],dep[MAXN];
int size[MAXN],son[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i]){
		DFS1(to[i],ID);
		size[ID]+=size[to[i]];
		if(size[to[i]]>size[son[ID]])
			son[ID]=to[i];
	}
	return;
}

int tim,dfn[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int topf){
	top[ID]=topf;
	dfn[ID]=++tim;
	if(son[ID])
		DFS2(son[ID],topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=son[ID])
			DFS2(to[i],to[i]);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int val[MAXN<<2],tag[MAXN<<2];
	inline void pushup(reg int k){
		val[k]=(val[lson]+val[rson])%MOD;
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg int Val){
		val[k]=(val[k]+(r-l+1)*Val%MOD)%MOD;
		tag[k]=(tag[k]+Val)%MOD;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag[k]){
			Add(lson,l,mid,tag[k]);
			Add(rson,mid+1,r,tag[k]);
			tag[k]=0;
		}
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val[k];
		pushdown(k,l,r);
		reg int res=0;
		if(L<=mid)
			res=(res+Query(lson,l,mid,L,R))%MOD;
		if(R>mid)
			res=(res+Query(rson,mid+1,r,L,R))%MOD;
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

using SegmentTree::Update;

inline void Update(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		Update(1,1,n,dfn[top[y]],dfn[y],1);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	Update(1,1,n,dfn[x],dfn[y],1);
	return;
}

using SegmentTree::Query;

inline int Query(int x,int y){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=Query(1,1,n,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res+=Query(1,1,n,dfn[x],dfn[y]);
	return res%MOD;
}

int ans[MAXM][2];

inline void Work(void){
	DFS1(1,0);
	DFS2(1,1);
	sort(Q+1,Q+tot+1);
	reg int now=0;
	for(reg int i=1;i<=tot;++i){
		while(now<Q[i].pos)
			Update(1,++now);
		reg int ID=Q[i].id;
		if(Q[i].flag)
			ans[ID][0]=Query(1,Q[i].z);
		else
			ans[ID][1]=Query(1,Q[i].z);
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",(ans[i][0]-ans[i][1]+MOD)%MOD);
	return;
}