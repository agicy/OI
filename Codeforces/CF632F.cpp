#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2500+5;

int n;
int a[MAXN][MAXN];

bool vis[MAXN];
int fa[MAXN],dep[MAXN];
int dis[MAXN];

inline void Prim(void){
	for(reg int i=1;i<=n;++i)
		fa[i]=1,dis[i]=a[1][i];
	vis[1]=true;
	dep[1]=1;
	for(reg int i=1;i<n;++i){
		reg int Min=INF;
		reg int id=0;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&dis[j]<Min)
				id=j,Min=dis[j];
		vis[id]=true;
		dep[id]=dep[fa[id]]+1;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&a[id][j]<dis[j])
				fa[j]=id,dis[j]=a[id][j];
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			a[i][j]=read();
	for(reg int i=1;i<=n;++i){
		if(a[i][i]){
			puts("NOT MAGIC");
			return 0;
		}
		for(reg int j=i+1;j<=n;++j)
			if(a[i][j]!=a[j][i]){
				puts("NOT MAGIC");
				return 0;
			}
	}
	Prim();
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j){
			int x=i,y=j;
			if(dep[x]<dep[y])
				swap(x,y);
			if(a[x][y]>max(a[fa[x]][y],a[fa[x]][x])){
				puts("NOT MAGIC");
				return 0;
			}
		}
	puts("MAGIC");
	return 0;
}