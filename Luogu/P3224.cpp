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

const int MAXN=500000+5;

int n,m;

namespace Splay{
	int fa[MAXN],ch[MAXN][2];
	int val[MAXN];
	int size[MAXN];
	
	int ID[MAXN];
	int root[MAXN],tot;
	int hh[MAXN];
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void pushup(reg int k){
		size[k]=size[ch[k][0]]+size[ch[k][1]]+1;
		return;
	}
	inline bool get(reg int x){
		return ch[fa[x]][1]==x;
	}
	inline void rotate(reg int x){
		reg int f=fa[x],ff=fa[f];
		reg bool w=get(x);
		ch[f][w]=ch[x][w^1];
		fa[ch[f][w]]=f;
		fa[f]=x;
		fa[x]=ff;
		ch[x][w^1]=f;
		if(ff)
			ch[ff][ch[ff][1]==f]=x;
		pushup(x);
		pushup(f);
		return;
	}
	inline void splay(reg int x,reg int goal){
		for(reg int qwq;(qwq=fa[x])!=goal;rotate(x))
			if(fa[qwq]!=goal)
				rotate(get(x)==get(qwq)?qwq:x);
		if(goal<=n)
			root[goal]=x;
		return;
	}
	inline void insert(reg int x,reg int bh){
		reg int u=root[bh],FF=bh;
		while(u&&val[u]!=x)
			FF=u,u=ch[u][x>val[u]];
		u=++tot;
		size[u]=1;
		fa[u]=FF;
		if(FF>n)
			ch[FF][x>val[FF]]=u;
		val[u]=x;
		ch[u][0]=ch[u][1]=0;
		splay(u,bh);
		return;
	}
	inline void DFS(reg int u,reg int kk){
		if(ch[u][0])
			DFS(ch[u][0],kk);
		if(ch[u][1])
			DFS(ch[u][1],kk);
		insert(val[u],kk);
		return;
	}
	inline void merge(reg int a,reg int b){
		int ra=find(a),rb=find(b);
		if(ra==rb)
			return;
		if(size[root[ra]]>size[root[rb]])
			swap(ra,rb);
		ID[ra]=rb;
		DFS(root[ra],rb);
		return;
	}
	inline int kth(reg int ID,reg int k){
		reg int u=root[ID];
		if(size[u]<k)
			return -1;
		while(true){
			if(size[ch[u][0]]+1<k){
				k-=size[ch[u][0]]+1;
				u=size[ch[u][1]];
			}
			else
				if(size[ch[u][0]]>=k)
					u=size[ch[u][0]];
				else
					return val[u];
		}
	}
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			root[i]=i+n;
		for(reg int i=1;i<=n;++i)
			ID[i]=i;
		return;
	}
}

using namespace Splay;

int main(void){
	n=read(),m=read();
	Init(n);
	tot=n+n;
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		hh[x]=i;
		val[i+n]=x;
		size[i+n]=1;
		fa[i+n]=i;
	}
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		merge(x,y);
	}
	reg int Q=read();
	while(Q--){
		static char opt;
		static int a,b;
		do
			opt=getchar();
		while(opt!='B'&&opt!='Q');
		a=read(),b=read();
		switch(opt){
			case 'B':{
				merge(a,b);
				break;
			}
			case 'Q':{
				int ans=kth(find(a),b);
				printf("%d\n",ans==-1?ans:hh[ans]);
				break;
			}
			default:break;
		}
	}
	return 0;
}
