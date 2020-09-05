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
const int MAXM=MAXN;

int n,m;
int pos[MAXN];

namespace Splay{
	namespace UnionFind{
		int ID[MAXN];
		inline int find(reg int x){
			if(x==ID[x])
				return x;
			else
				return ID[x]=find(ID[x]);
		}
	}
	using namespace UnionFind;
	#define lson ( ch[p][0] )
	#define rson ( ch[p][1] )
	int tot,root[MAXN<<2];
	int fa[MAXN<<2],ch[MAXN<<2][2];
	int size[MAXN<<2];
	int val[MAXN<<2];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			root[i]=i+n;
		for(reg int i=1;i<=n;++i)
			ID[i]=i;
		tot=2*n;
		return;
	}
	inline bool get(reg int p){
		return ch[fa[p]][1]==p;
	}
	inline void pushup(reg int p){
		size[p]=size[lson]+size[rson]+1;
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa[x],z=fa[y],k=get(x),w=ch[x][!k];
		ch[z][get(y)]=x;
		ch[x][!k]=y;
		ch[y][k]=w;
		if(w)
			fa[w]=y;
		fa[y]=x,fa[x]=z;
		pushup(y),pushup(x);
		return;
	}
	inline void splay(reg int x,reg int goal){
		for(reg int f=fa[x];f=fa[x],f!=goal;rotate(x))
			if(fa[f]!=goal)
				rotate(get(x)==get(f)?f:x);
		if(goal<=n)
			root[goal]=x;
		return;
	}
	inline void insert(reg int x,reg int id){
		reg int p=root[id],f=id;
		while(p&&val[p]!=x)
			f=p,p=ch[p][x>val[p]];
		p=++tot;
		size[p]=1;
		fa[p]=f;
		if(f>n)
			ch[f][x>val[f]]=p;
		val[p]=x,lson=rson=0;
		splay(p,id);
		return;
	}
	inline void DFS(reg int p,reg int id){
		if(lson)
			DFS(lson,id);
		if(rson)
			DFS(rson,id);
		insert(val[p],id);
		return;
	}
	inline void merge(reg int a,reg int b){
		int ra=find(a),rb=find(b);
		if(ra!=rb){
			if(size[root[ra]]>size[root[rb]])
				swap(ra,rb);
			ID[ra]=rb;
			DFS(root[ra],rb);
		}
		return;
	}
	inline int kth(reg int id,reg int k){
		reg int p=root[id];
		if(size[p]<k)
			return -1;
		while(true){
			if(size[lson]+1<k){
				k-=size[lson]+1;
				p=rson;
			}
			else
				if(size[lson]>=k)
					p=lson;
				else
					return val[p];
		}
	}
	#undef lson
	#undef rson
}

using namespace Splay;

int main(void){
	n=read(),m=read();
	Init(n);
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		pos[x]=i;
		val[i+n]=x;
		fa[i+n]=i;
		size[i+n]=1;
	}
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		merge(a,b);
	}
	reg int q=read();
	while(q--){
		static char opt;
		static int x,k;
		do
			opt=getchar();
		while(opt!='Q'&&opt!='B');
		x=read(),k=read();
		switch(opt){
			case 'B':{
				merge(x,k);
				break;
			}
			case 'Q':{
				reg int ans=kth(UnionFind::find(x),k);
				printf("%d\n",ans!=-1?pos[ans]:-1);
				break;
			}
			default:break;
		}
	}
	return 0;
}