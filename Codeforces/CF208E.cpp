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
const int MAXLOG2N=17+1;

int n;
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Node{
	int val,id;
	inline Node(reg int val=0,reg int id=0):val(val),id(id){
		return;
	}
};

int fa[MAXN][MAXLOG2N],dep[MAXN];

inline void DFS(reg int ID,reg int father){
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID);
	return;
}

inline int Getkth(reg int ID,reg int k){
	for(reg int i=0;i<MAXLOG2N;++i)
		if((k>>i)&1)
			ID=fa[ID][i];
	return ID;
}

vector<Node> V[MAXN];
int T[MAXN];
vector<int> Dep[MAXN];
int ans[MAXN];
bool vis[MAXN];

inline void GetAns(reg int ID,reg int father){
	vis[ID]=true;
	++T[dep[ID]];
	Dep[ID].resize(V[ID].size());
	for(reg int i=0,size=V[ID].size();i<size;++i)
		Dep[ID][i]=T[V[ID][i].val+dep[ID]];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			GetAns(to[i],ID);
	for(reg int i=0,size=V[ID].size();i<size;++i)
		ans[V[ID][i].id]=T[V[ID][i].val+dep[ID]]-Dep[ID][i];
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int r;
		r=read();
		if(r)
			Add_Edge(r,i);
	}
	for(reg int i=1;i<=n;++i)
		if(!dep[i])
			DFS(i,0);
	reg int m=read();
	for(reg int i=1;i<=m;++i){
		static int v,p;
		v=read(),p=read();
		reg int fa=Getkth(v,p);
		if(fa)
			V[fa].push_back(Node(p,i));
	}
	for(reg int i=1;i<=n;++i)
		if(!vis[i])
			GetAns(i,0);
	for(reg int i=1;i<=m;++i)
		printf("%d%c",ans[i]?ans[i]-1:ans[i],i==m?'\n':' ');
	return 0;
}