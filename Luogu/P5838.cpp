#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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
const int MAXM=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int t[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int a[MAXM],b[MAXM],c[MAXM];
vector<int> V;

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		t[i]=read();
		V.push_back(t[i]);
	}
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read(),c[i]=read();
		V.push_back(c[i]);
	}
	return;
}

int fa[MAXN],dep[MAXN];
int size[MAXN],son[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[to[i]]>size[son[ID]])
				son[ID]=to[i];
		}
	return;
}

int tim,dfn[MAXN];
int top[MAXN];

const int MAXSIZE=30*MAXN;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot;
	int root[MAXN];
	int lson[MAXSIZE],rson[MAXSIZE];
	int val[MAXSIZE];
	inline int Build(reg int l,reg int r){
		reg int k=++tot;
		if(l!=r){
			lson[k]=Build(l,mid);
			rson[k]=Build(mid+1,r);
		}
		return k;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg int pos,reg int Val){
		reg int k=++tot;
		lson[k]=lson[pre],rson[k]=rson[pre],val[k]=val[pre]+Val;
		if(l==r)
			return k;
		if(pos<=mid)
			lson[k]=Update(lson[pre],l,mid,pos,Val);
		if(pos>mid)
			rson[k]=Update(rson[pre],mid+1,r,pos,Val);
		return k;
	}
	inline bool Query(reg int pre,reg int k,reg int l,reg int r,reg int x){
		if(l==r&&l==x){
			return val[k]-val[pre];
		}
		if(x<=mid)
			return Query(lson[pre],lson[k],l,mid,x);
		if(x>mid)
			return Query(rson[pre],rson[k],mid+1,r,x);
		return false;
	}
	#undef mid
}

using namespace SegmentTree;

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++tim;
	root[dfn[ID]]=Update(root[dfn[ID]-1],1,V.size(),t[ID],1);
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	}
	return;
}

inline int Query(int u,int v,int x){
	reg int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		res|=Query(root[dfn[top[u]]-1],root[dfn[u]],1,V.size(),x);
		if(res)
			return res;
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	res|=Query(root[dfn[u]-1],root[dfn[v]],1,V.size(),x);
	return res;
}

inline void Work(void){
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		t[i]=lower_bound(V.begin(),V.end(),t[i])-V.begin()+1;
	for(reg int i=1;i<=m;++i)
		c[i]=lower_bound(V.begin(),V.end(),c[i])-V.begin()+1;
	DFS1(1,0);
	root[0]=Build(1,V.size());
	DFS2(1,0,1);
	for(reg int i=1;i<=m;++i)
		printf("%d",Query(a[i],b[i],c[i])?1:0);
	putchar('\n');
	return;
}