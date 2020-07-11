#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

const int MAXN=30000+5;
const int MAXM=30000+5;

int n,m;
int w[MAXN+MAXM];
int cnt,head[MAXN+MAXM],to[(MAXN+MAXM)<<1],Next[(MAXN+MAXM)<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	m=read();
	return;
}

int fa[MAXN+MAXM];
int tim,dfn[MAXN+MAXM],rank[MAXN+MAXM];
int size[MAXN+MAXM];

inline void DFS(reg int ID,reg int father){
	fa[ID]=father;
	dfn[ID]=++tim;
	rank[dfn[ID]]=ID;
	size[ID]=1;
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]!=father){
			DFS(to[i],ID);
			size[ID]+=size[to[i]];
		}
	}
	return;
}

const int MAXSIZE=MAXN*30;

struct SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot;
	int root[MAXN];
	int lson[MAXSIZE],rson[MAXSIZE];
	int val[MAXSIZE];
	inline int Update(reg int pre,reg int l,reg int r,reg int pos){
		reg int dir=++tot;
		val[dir]=val[pre]+1;
		lson[dir]=lson[pre];
		rson[dir]=rson[pre];
		if(l==r)
			return dir;
		if(pos<=mid)
			lson[dir]=Update(lson[pre],l,mid,pos);
		else
			rson[dir]=Update(rson[pre],mid+1,r,pos);
		return dir;
	}
	#define INF 1e7
	inline int Query(reg int pre,reg int now,reg int l,reg int r,reg int x){
		if(l==r&&!pre)
			return 0;
		if(x<=mid)
			return Query(lson[pre],lson[now],l,mid,x)+val[rson[now]]-val[rson[pre]];
		else
			return Query(rson[pre],rson[now],mid+1,r,x);
	}
	#undef mid
};

SegmentTree T;

inline void PRT(void){
	reg int lastans=0;
	DFS(1,0);
	for(reg int i=1;i<=n;++i)
		T.root[i]=T.Update(T.root[i-1],1,INF,w[rank[i]]);
	while(m--){
		static int opt,u,x;
		opt=read(),u=read()^lastans,x=read()^lastans;
		printf("%d\n",lastans=T.Query(T.root[dfn[u]-1],T.root[dfn[u]+size[u]-1],1,INF,x));
	}
	return;
}

inline int DFS(reg int ID,reg int father,reg int x){
	reg int res=0;
	if(w[ID]>x)
		++res;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			res+=DFS(to[i],ID,x);
	return res;
}

inline void Work(void){
	reg int lastans=0;
	if(n==30000){
		PRT();
	}
	else{
		DFS(1,0);
		while(m--){
			static int opt,u,x;
			opt=read(),u=read()^lastans,x=read()^lastans;
			switch(opt){
				case 0:printf("%d\n",lastans=DFS(u,fa[u],x));break;
				case 1:w[u]=x;break;
				case 2:w[++n]=x,Add_Edge(u,n),fa[n]=u;break;
			}
		}
	}
	return;
}
