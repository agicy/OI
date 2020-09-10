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

const int MAXN=1e5+5;
const int MAXM=3e5+5;
const int MAXLOG2N=17+1;
const int inf=0x3f3f3f3f;

int n,m,a,b,c;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

int Max[MAXN][3];
int from[MAXN];

inline void dfs1(reg int u,reg int father){
	Max[u][1]=-inf;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			reg int tmp=Max[v][0]+w[i];
			if(tmp>Max[u][0]){
				Max[u][1]=Max[u][0];
				Max[u][0]=tmp;
				from[u]=v;
			}
			else if(tmp>Max[u][1])
				Max[u][1]=tmp;
		}
	}
	return;
}

inline void dfs2(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			Max[v][2]=w[i]+Max[u][2];
			if(v==from[u])
				Max[v][2]=max(Max[v][2],w[i]+Max[u][1]);
			else
				Max[v][2]=max(Max[v][2],w[i]+Max[u][0]);
			dfs2(v,u);
		}
	}
	return;
}

int s[MAXN];
int fa[MAXN][MAXLOG2N],dep[MAXN];
int M[MAXN][MAXLOG2N];

inline void dfs3(reg int u,reg int father){
	M[u][0]=s[u];
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		M[u][i]=max(M[u][i-1],M[fa[u][i-1]][i-1]);
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs3(v,u);
	}
	return;
}

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

int main(void){
	n=read(),m=read(),a=read(),b=read(),c=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	dfs1(1,0);
	dfs2(1,0);
	for(reg int i=1;i<=n;++i)
		s[i]=1ll*(max(Max[i][0],Max[i][2])+a)%c*b%c;
	dfs3(1,0);
	while(m--){
		static int x,y,q;
		x=read(),y=read(),q=read();
		int lca=LCA(x,y);
		for(reg int i=MAXLOG2N-1;i>=0;--i)
			if(dep[fa[x][i]]>=dep[lca]&&M[x][i]<q)
				x=fa[x][i];
		if(s[x]>=q)
			printf("%d\n",x);
		else{
			reg int u=0,v=0;
			for(reg int i=MAXLOG2N-1;i>=0;--i)
				if(dep[fa[y][i]]>=dep[lca]){
					if(M[y][i]>=q)
						u=y,v=i;
					y=fa[y][i];
				}
			for(reg int i=v-1;i>=0;--i)
				if(M[fa[u][i]][i]>=q)
					u=fa[u][i];
			if(!u)
				puts("-1");
			else
				printf("%d\n",u);
		}
	}
	return 0;
}