#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}


int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int u[MAXN],v[MAXN],W[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read(),W[i]=read();
		Add_Edge(u[i],v[i],W[i]);
		Add_Edge(v[i],u[i],W[i]);
	}
	return;
}

int val[MAXN];
int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			val[to[i]]=w[i];
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[son[ID]]<size[to[i]])
				son[ID]=to[i];
		}
	return;
}

int tim,dfn[MAXN],rank[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++tim;
	rank[dfn[ID]]=ID;
	if(!son[ID])
		return;
	DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val;
		inline Node(reg int val=0):val(val){
			return;
		}
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=Node(max(unit[lson].val,unit[rson].val));
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg int v[],reg int rank[]){
		if(l==r){
			unit[k]=Node(v[rank[l]]);
			return;
		}
		Build(lson,l,mid,v,rank);
		Build(rson,mid+1,r,v,rank);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int x){
		if(l==pos&&r==pos){
			unit[k]=Node(x);
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,x);
		if(pos>mid)
			Update(rson,mid+1,r,pos,x);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].val;
		int res=0;
		if(L<=mid)
			res=max(res,Query(lson,l,mid,L,R));
		if(R>mid)
			res=max(res,Query(rson,mid+1,r,L,R));
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline int Query(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		res=max(res,T.Query(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	if(x!=y)
		res=max(res,T.Query(1,1,n,dfn[x]+1,dfn[y]));
	return res;
}

inline void Work(void){
	DFS1(1,0);
	DFS2(1,0,1);
	T.Build(1,1,n,val,rank);
	while(true){
		static char opt;
		do
			opt=getchar();
		while(opt!='C'&&opt!='Q'&&opt!='D');
		if(opt=='D')
			break;
		switch(opt){
			case 'C':{
				reg int i=read(),t=read();
				reg int son=dep[u[i]]>dep[v[i]]?u[i]:v[i];
				T.Update(1,1,n,dfn[son],t);
				break;
			}
			case 'Q':{
				reg int a=read(),b=read();
				printf("%d\n",Query(a,b));
				break;
			}
			default:break;
		}
	}
	return;
}
