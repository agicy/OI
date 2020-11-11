#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;
const int inf=0x3f3f3f3f;

int n,q;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXN];
int fa[MAXN][MAXLOG2N],val[MAXN][MAXLOG2N];

inline void dfs(int u,int father){
    dep[u]=dep[father]+1;
	fa[u][0]=father;
	val[u][0]=father?min(u,father):u;
	for(reg int i=1;i<MAXLOG2N;++i){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		val[u][i]=min(val[u][i-1],val[fa[u][i-1]][i-1]);
		if(!fa[u][i])
			break;
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	return;
}

inline pair<int,int> LCA(int x,int y){
	int Min=inf;
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x]){
			Min=min(Min,val[y][i]);
			y=fa[y][i];
		}
	if(x==y)
		return make_pair(x,Min);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i]){
			Min=min(Min,min(val[x][i],val[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	return make_pair(fa[x][0],min(Min,min(val[x][0],val[y][0])));
}

int sLca,Min;

inline void update(reg int x){
	if(!sLca)
		sLca=Min=x;
	else{
		pair<int,int> p=LCA(sLca,x);
		sLca=p.first,Min=min(Min,p.second);
	}
	return;
}

inline int query(reg int x){
	pair<int,int> p=LCA(x,sLca);
	return min(p.second,Min);
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs(1,0);
	while(q--){
		static int opt,x;
		opt=read(),x=read();
		switch(opt){
			case 1:{
				update(x);
				break;
			}
			case 2:{
				reg int ans=query(x);
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}