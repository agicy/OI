#include<cstdio>
#include<algorithm>
using std::min;
#define reg register
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

const int MAXN=1500+5;

bool vis[MAXN];
int n;
int root;
int w[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];
int f[MAXN][3];

inline void Add_Edge(reg int,reg int);
inline void DFS(reg int,reg int);

int main(void){
	reg int i;
	n=read();
	for(i=1;i<=n;++i){
		static int id,m;
		id=read(),w[id]=read(),m=read();
		while(m--){
			static int to;
			to=read();
			vis[to]=true;
			Add_Edge(id,to);
		}
	}
	root=1;
	while(vis[root])
		++root;
	DFS(root,0);
	printf("%d\n",min(f[root][1],f[root][2]));
	return 0;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID,reg int father){
	reg int i;
	reg int D=INF;
	for(i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			f[ID][0]+=min(f[to[i]][1],f[to[i]][2]);
			f[ID][1]+=min(f[to[i]][1],f[to[i]][2]);
			D=min((int)D,f[to[i]][2]-min(f[to[i]][1],f[to[i]][2]));
			f[ID][2]+=min(f[to[i]][0],min(f[to[i]][1],f[to[i]][2]));
		}
	f[ID][1]+=D;
	f[ID][2]+=w[ID];
	return;
}
