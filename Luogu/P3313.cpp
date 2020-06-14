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

const int MAXN=100000+5;
const int MAXC=100000+5;

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];

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

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++tim;
	rnk[tim]=ID;
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXSIZE=MAXN*40;
	struct Node{
		int lson,rson;
		int Max,sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
		#define sum(x) unit[(x)].sum
	};
	int tot;
	int root[MAXC];
	Node unit[MAXSIZE];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson(k)),Max(rson(k)));
		sum(k)=sum(lson(k))+sum(rson(k));
		return;
	}
	inline void Update(reg int &k,reg int l,reg int r,reg int pos,reg int val){
		if(!k)
			k=++tot;
		if(l==r){
			Max(k)=sum(k)=val;
			return;
		}
		if(pos<=mid)
			Update(lson(k),l,mid,pos,val);
		if(pos>mid)
			Update(rson(k),mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int QuerySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!k)
			return 0;
		if(L<=l&&r<=R)
			return sum(k);
		reg int res=0;
		if(L<=mid)
			res+=QuerySum(lson(k),l,mid,L,R);
		if(R>mid)
			res+=QuerySum(rson(k),mid+1,r,L,R);
		return res;
	}
	inline int QueryMax(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(!k)
			return 0;
		if(L<=l&&r<=R)
			return Max(k);
		int res=0;
		if(L<=mid)
			res=max(res,QueryMax(lson(k),l,mid,L,R));
		if(R>mid)
			res=max(res,QueryMax(rson(k),mid+1,r,L,R));
		return res;
	}
	#undef mid
}

using namespace SegmentTree;

int n,q;
int w[MAXN],c[MAXN];

inline int QueryMax(int x,int y,int c){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res=max(res,QueryMax(root[c],1,n,dfn[top[y]],dfn[y]));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=max(res,QueryMax(root[c],1,n,dfn[x],dfn[y]));
	return res;
}

inline int QuerySum(int x,int y,int c){
	reg int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=QuerySum(root[c],1,n,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res+=QuerySum(root[c],1,n,dfn[x],dfn[y]);
	return res;
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		w[i]=read(),c[i]=read();
	}
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	DFS1(1,0);
	DFS2(1,0,1);
	for(reg int i=1;i<=n;++i)
		Update(root[c[i]],1,n,dfn[i],w[i]);
	while(q--){
		static char opt1,opt2;
		static int x,y;
		do
			opt1=getchar();
		while(opt1<'A'||'Z'<opt1);
		do
			opt2=getchar();
		while(opt2<'A'||'Z'<opt2);
		x=read(),y=read();
		switch(opt1){
			case 'C':{
				switch(opt2){
					case 'C':{
						Update(root[c[x]],1,n,dfn[x],0);
						c[x]=y;
						Update(root[c[x]],1,n,dfn[x],w[x]);
						break;
					}
					case 'W':{
						w[x]=y;
						Update(root[c[x]],1,n,dfn[x],w[x]);
						break;
					}
					default:break;
				}
				break;
			}
			case 'Q':{
				switch(opt2){
					case 'S':{
						printf("%d\n",QuerySum(x,y,c[x]));
						break;
					}
					case 'M':{
						printf("%d\n",QueryMax(x,y,c[x]));
						break;
					}
					default:break;
				}
				break;
			}
			default:break;
		}
	}
	return 0;
}