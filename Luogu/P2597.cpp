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

const int MAXN=65534+5;
const int MAXLOG2N=16+1;
const int MAXM=1000000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Graph{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
};

int n;
int inDeg[MAXN];
Graph G1,G2;

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int x;
		do{
			x=read();
			if(x){
				++inDeg[i];
				G1.Add_Edge(x,i);
			}
		}while(x);
	}
	return;
}

int dep[MAXN];
int fa[MAXN][MAXLOG2N];

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int size[MAXN];

inline void DFS(reg int ID,const Graph& G){
	size[ID]=1;
	for(reg int i=G.head[ID];i;i=G.Next[i]){
		DFS(G.to[i],G);
		size[ID]+=size[G.to[i]];
	}
	return;
}

int father[MAXN];
queue<int> Q;

inline void Topo(void){
	memset(father,-1,sizeof(father));
	for(int i=1;i<=n;++i)
		if(!inDeg[i]){
			father[i]=0;
			Q.push(i);
		}
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		G2.Add_Edge(father[ID],ID);
		dep[ID]=dep[father[ID]]+1;
		fa[ID][0]=father[ID];
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[ID][i]=fa[fa[ID][i-1]][i-1];
		for(reg int i=G1.head[ID];i;i=G1.Next[i]){
			if(father[G1.to[i]]==-1)
				father[G1.to[i]]=ID;
			else
				father[G1.to[i]]=LCA(father[G1.to[i]],ID);
			--inDeg[G1.to[i]];
			if(!inDeg[G1.to[i]])
				Q.push(G1.to[i]);
		}
	}
	return;
}

inline void Work(void){
	Topo();
	DFS(0,G2);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",size[i]-1);
	return;
}
