#include<cstdio>
#include<algorithm>
using std::swap;
using std::sort;
#include<queue>
using std::queue;
#define reg register

const int MAXN=300000+5;
const int MAXLOG2N=19+1;

struct Node{
	int p,q,r;
	inline Node(void){
		p=q=r=0;
		return;
	}
	inline Node(reg int a,reg int b,reg int c){
		p=a,q=b,r=c;
		return;
	}
	inline bool operator<(const Node& a)const{
		return q<a.q;
	}
};

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXN];
	inline void Update(reg int ID,reg int val){
		if(!ID)
			return;
		while(ID<=n){
			unit[ID]+=val;
			ID+=lowbit(ID);
		}
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		while(ID){
			res+=unit[ID];
			ID-=lowbit(ID);
		}
		return res;
	}
	#undef lowbit
};

int n,m;
int cnt0,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int Time,dfn[MAXN];
int w[MAXN];
int s[MAXN],e[MAXN];
int ans[MAXN];
int fa[MAXN][MAXLOG2N],dep[MAXN],size[MAXN];
Node a[MAXN],b[MAXN];
int cnt[2];
Node c[2][MAXN];
TreeArray T;
queue<Node> Q;

inline void Add_Edge(reg int,reg int);
inline void DFS(reg int,reg int);
inline void LCA_Init(void);
inline int LCA(int,int);
inline void Add(reg int,reg int,reg int,reg int);
inline bool cmp(const Node&,const Node&);

int main(void){
	reg int i,j;
	reg int now1=1,now2=1;
	Node temp;
	scanf("%d%d",&n,&m);
	T.n=n;
	for(i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(i=1;i<=n;++i)
		scanf("%d",&w[i]);
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=m;++i)
		scanf("%d%d",&s[i],&e[i]);
	DFS(1,0);
	LCA_Init();
	for(i=1;i<=n;++i){
		a[i]=Node(i,dep[i]+w[i],0);
		b[i]=Node(i,dep[i]-w[i],0);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(i=1;i<=m;++i){
		reg int st=s[i],en=e[i],lca=LCA(st,en);
		if(lca==st)
			Add(en,st,1,0);
		else if(lca==en)
			Add(st,en,0,0);
		else{
			reg int x=st;
			for(j=MAXLOG2N-1;j>=0;--j)
				if(dep[fa[x][j]]>dep[lca])
					x=fa[x][j];
			Add(st,x,0,0);
			Add(en,lca,1,dep[st]-dep[x]+1);
		}
	}
	sort(c[0]+1,c[0]+cnt[0]+1,cmp);
	sort(c[1]+1,c[1]+cnt[1]+1,cmp);
	for(i=1;i<=n;++i){
		while(a[i].q!=a[i-1].q&&!Q.empty()){
			temp=Q.front();
			Q.pop();
			T.Update(temp.p,-1);
			T.Update(temp.q,1);
		}
		while(now1<=cnt[0] && c[0][now1].r<=a[i].q){
			if(a[i].q!=a[i-1].q && c[0][now1].r==a[i].q){
				T.Update(dfn[c[0][now1].p],1);
				T.Update(dfn[fa[c[0][now1].q][0]],-1);
				Q.push(Node(dfn[c[0][now1].p],dfn[fa[c[0][now1].q][0]],0));
			}
			++now1;
		}
		ans[a[i].p]+=T.Query(dfn[a[i].p]+size[a[i].p]-1)-T.Query(dfn[a[i].p]-1);
	}
	while(!Q.empty()){
		temp=Q.front();
		Q.pop();
		T.Update(temp.p,-1);
		T.Update(temp.q,1);
	}
	for(i=1;i<=n;++i){
		while(b[i].q!=b[i-1].q&&!Q.empty()){
			temp=Q.front();
			Q.pop();
			T.Update(temp.p,-1);
			T.Update(temp.q,1);
		}
		while(now2<=cnt[1]&&c[1][now2].r<=b[i].q){
			if(b[i].q!=b[i-1].q && c[1][now2].r==b[i].q){
				T.Update(dfn[c[1][now2].p],1);
				T.Update(dfn[fa[c[1][now2].q][0]],-1);
				Q.push(Node(dfn[c[1][now2].p],dfn[fa[c[1][now2].q][0]],0));
			}
			++now2;
		}
		ans[b[i].p]+=T.Query(dfn[b[i].p]+size[b[i].p]-1)-T.Query(dfn[b[i].p]-1);
	}
	for(i=1;i<=n;++i)
		printf("%d ",ans[i]);
	return 0;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt0]=head[u];
	to[cnt0]=v;
	head[u]=cnt0;
	return;
}

inline void DFS(reg int ID,reg int father){
	reg int i;
	dfn[ID]=++Time;
	dep[ID]=dep[father]+1;
	fa[ID][0]=father;
	size[ID]=1;
	for(i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			size[ID]+=size[to[i]];
		}
	return;
}

inline void LCA_Init(void){
	reg int i,j;
	for(j=1;j<MAXLOG2N;++j)
		for(i=1;i<=n;++i)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	return;
}

inline int LCA(int x,int y){
	if(x==y)
		return x;
	reg int i;
	if(dep[x]>dep[y])
		swap(x,y);
	for(i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline void Add(reg int x,reg int y,reg int k,reg int base){
	c[k][++cnt[k]]=Node(x,y,dep[k?y:x]-base);
	return;
}

inline bool cmp(const Node& x,const Node& y){
	return x.r<y.r;
}