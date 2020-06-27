#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXH=2000+5;
const int MAXW=2000+5;
const int MAXP=200000+5;
const int MAXQ=200000+5;

int H,W,p,q;
char M[MAXH][MAXW];
int a[MAXP],b[MAXP];

struct Node{
	int x,y,d,id;
	inline Node(reg int x=0,reg int y=0,reg int d=0,reg int id=0):x(x),y(y),d(d),id(id){
		return;
	}
};

queue<Node> Q;

inline bool check(reg int x,reg int y){
	return 1<=x&&x<=H&&1<=y&&y<=W&&M[x][y]=='.';
}

bool vis[MAXH][MAXW];
int dis[MAXH][MAXW];
int color[MAXH][MAXW];

inline void BFS(void){
	for(reg int i=1;i<=p;++i){
		vis[a[i]][b[i]]=true;
		dis[a[i]][b[i]]=0;
		color[a[i]][b[i]]=i;
		Q.push(Node(a[i],b[i],0,i));
	}
	while(!Q.empty()){
		static Node t;
		t=Q.front();
		Q.pop();
		reg int x=t.x,y=t.y,d=t.d,id=t.id;
		const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(check(fx,fy))
				if(!vis[fx][fy]){
					vis[fx][fy]=true;
					dis[fx][fy]=d+1;
					color[fx][fy]=id;
					Q.push(Node(fx,fy,d+1,id));
				}
		}
	}
	return;
}

struct Edge{
	int from,to,len;
	inline Edge(reg int from=0,reg int to=0,reg int len=0):from(from),to(to),len(len){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return len<a.len;
	}
};

namespace UnionFind{
	int fa[MAXP*2];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int tot;
const int MAXSIZE=MAXH*MAXW;
Edge E[MAXSIZE];

namespace Tree{
	const int MAXV=MAXP*2;
	int root;
	int cnt,head[MAXV],to[MAXV],Next[MAXV];
	int v[MAXV],inDeg[MAXV];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	const int MAXLOG2V=19+1;
	int fa[MAXV][MAXLOG2V],dep[MAXV];
	inline void DFS(reg int ID,reg int father){
		fa[ID][0]=father;
		dep[ID]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2V;++i)
			fa[ID][i]=fa[fa[ID][i-1]][i-1];
		for(reg int i=head[ID];i;i=Next[i])
			DFS(to[i],ID);
		return;
	}
	inline int LCA(int x,int y){
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x])
				y=fa[y][i];
		if(x==y)
			return x;
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
}

inline void Build(void){
	for(reg int i=1;i<=H;++i)
		for(reg int j=1;j<=W;++j)
			if(M[i][j]!='#'){
				const int dx[]={0,1},dy[]={1,0};
				for(reg int k=0;k<2;++k){
					reg int fx=i+dx[k],fy=j+dy[k];
					if(check(fx,fy)&&color[i][j]!=color[fx][fy])
						E[++tot]=Edge(color[i][j],color[fx][fy],dis[i][j]+dis[fx][fy]);
				}
			}
	sort(E+1,E+tot+1);
	using namespace UnionFind;
	Init(2*p);
	reg int pcnt=p;
	for(reg int i=1;i<=tot;++i)
		if(!search(E[i].from,E[i].to)){
			reg int k=++pcnt;
			reg int a=find(E[i].from),b=find(E[i].to);
			Tree::Add_Edge(k,a);
			Tree::Add_Edge(k,b);
			++Tree::inDeg[a];
			++Tree::inDeg[b];
			Tree::v[k]=E[i].len;
			merge(k,a),merge(k,b);
		}
	for(reg int i=1;i<=pcnt;++i)
		if(!Tree::inDeg[i])
			Tree::DFS(i,0);
	return;
}

int main(void){
	scanf("%d%d%d%d",&H,&W,&p,&q);
	for(reg int i=1;i<=H;++i)
		scanf("%s",M[i]+1);
	for(reg int i=1;i<=p;++i)
		scanf("%d%d",&a[i],&b[i]);
	BFS();
	Build();
	while(q--){
		static int s,t;
		scanf("%d%d",&s,&t);
		reg int lca=Tree::LCA(s,t);
		if(lca==0)
			puts("-1");
		else{
			reg int ans=Tree::v[lca];
			printf("%d\n",ans);
		}
	}
	return 0;
}