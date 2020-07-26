#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int Z=100000+5;

int n,m;
int ans[MAXN];

namespace S{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	int tot;
	int root[MAXN],lson[MAXSIZE],rson[MAXSIZE];
	int id[MAXSIZE],Max[MAXSIZE];
	int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int top,S[MAXSIZE];
	inline int New(void){
		if(top)
			return S[top--];
		else
			return ++cnt;
	}
	inline void del(reg int k){
		S[++top]=k;
		lson[k]=rson[k]=Max[k]=id[k]=0;
		return;
	}
	inline void pushup(reg int k){
		if(Max[lson[k]]>=Max[rson[k]])
			Max[k]=Max[lson[k]],id[k]=id[lson[k]];
		else
			Max[k]=Max[rson[k]],id[k]=id[rson[k]];
		return;
	}
	inline void Update(reg int &k,reg int l,reg int r,int pos,int val){
		if(!k)
			k=New();
		if(l==r){
			Max[k]+=val,id[k]=l;
		}
		else{
			if(pos<=mid)
				Update(lson[k],l,mid,pos,val);
			else
				Update(rson[k],mid+1,r,pos,val);
			pushup(k);
		}
		if(!Max[k])
			id[k]=0;
		return;
	}
	inline int Merge(reg int l,reg int r,reg int u,reg int v){
		if(!u||!v)
			return u|v;
		reg int k=New();
		if(l==r)
			Max[k]=Max[u]+Max[v],id[k]=l;
		else{
			lson[k]=Merge(l,mid,lson[u],lson[v]);
			rson[k]=Merge(mid+1,r,rson[u],rson[v]);
			pushup(k);
		}
		del(u),del(v);
		return k;
	}
	#undef mid
}

namespace T{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXN],dep[MAXN];
	int son[MAXN],size[MAXN];
	int top[MAXN];
	inline void DFS1(reg int ID,reg int father){
		size[ID]=1;
		fa[ID]=father;
		dep[ID]=dep[father]+1;
		for(reg int i=head[ID];i;i=Next[i])
			if(to[i]!=father){
				DFS1(to[i],ID);
				size[ID]+=size[to[i]];
				if(size[son[ID]]<size[to[i]])
					son[ID]=to[i];
			}
		return;
	}
	inline void DFS2(reg int ID,reg int father,reg int topf){
		top[ID]=topf;
		if(son[ID])
			DFS2(son[ID],ID,topf);
		for(reg int i=head[ID];i;i=Next[i])
			if(to[i]!=father&&to[i]!=son[ID])
				DFS2(to[i],ID,to[i]);
		return;
	}
	inline int LCA(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]])
				swap(u,v);
			u=fa[top[u]];
		}
		return dep[u]<dep[v]?u:v;
	}
}

using namespace T;
using namespace S;

inline void DFS(reg int ID,reg int father){
	for(reg int i=T::head[ID];i;i=T::Next[i])
		if(T::to[i]!=father)
			DFS(T::to[i],ID);
	for(reg int i=S::head[ID];i;i=S::Next[i])
		Update(root[ID],1,Z,S::to[i],S::w[i]);
	ans[ID]=id[root[ID]];
	if(fa[ID])
		root[fa[ID]]=Merge(1,Z,root[fa[ID]],root[ID]);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		T::Add_Edge(a,b);
		T::Add_Edge(b,a);
	}
	DFS1(1,0);
	DFS2(1,0,1);
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		x=read(),y=read(),z=read();
		reg int lca=LCA(x,y),f=fa[lca];
		S::Add_Edge(x,z,1);
		S::Add_Edge(y,z,1);
		S::Add_Edge(lca,z,-1);
		S::Add_Edge(f,z,-1);
	}
	DFS(1,0);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}