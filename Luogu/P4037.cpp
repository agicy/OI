#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=51+5;
const int MAXM=2e3+5;
const int MAXL=100+5;
const int inf=0x3f3f3f3f;

int n,m;
int w[MAXN],v[MAXN],lim[MAXN];
int cnt,head[MAXN],to[MAXN],c[MAXN],Next[MAXN];
int indeg[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	c[cnt]=len;
	head[u]=cnt;
	return;
}

int f[MAXN][MAXL][MAXM];

inline void dfs(reg int u){
	if(!head[u]){
		lim[u]=min(lim[u],m/v[u]);
		for(reg int i=lim[u],j;i>=0;--i)
			for(j=i;j<=lim[u];++j)
				f[u][i][j*v[u]]=w[u]*(j-i);
		return;
	}
	lim[u]=inf;
	for(reg int i=head[u],p;i;i=Next[i]){
		p=to[i];
		dfs(p);
		lim[u]=min(lim[u],lim[p]/c[i]);
		v[u]+=v[p]*c[i];
	}
	lim[u]=min(lim[u],m/v[u]);
	for(reg int i=lim[u],j,k,l,p,tmp;i>=0;--i){
		static int g[MAXM];
		memset(g,-0x3f,sizeof(g));
		g[0]=0;
		for(j=head[u];j;j=Next[j]){
			p=to[j];
			for(k=m;k>=0;--k){
				tmp=-inf;
				for(l=0;l<=k;++l)
					tmp=max(tmp,g[k-l]+f[p][i*c[j]][l]);
				g[k]=tmp;
			}
		}
		for(j=0;j<=i;++j)
			for(k=0;k<=m;++k)
				f[u][j][k]=max(f[u][j][k],g[k]+(i-j)*w[u]);
	}
	return;
}

int ans[MAXM];

int main(void){
	memset(f,-0x3f,sizeof(f));
	n=read(),m=read();
	for(reg int i=1,c,x,y;i<=n;++i){
		w[i]=read();
		switch(getchar()){
			case 'A':{
				c=read();
				while(c--){
					x=read(),y=read();
					++indeg[x],Add_Edge(i,x,y);
				}
				break;
			}
			case 'B':{
				v[i]=read(),lim[i]=read();
				break;
			}
		}
	}
	for(reg int i=1,j,k;i<=n;++i)
		if(!indeg[i]){
			dfs(i);
			for(j=m;j>=0;--j)
				for(k=0;k<=j;++k)
					ans[j]=max(ans[j],ans[j-k]+f[i][0][k]);
		}
	printf("%d\n",ans[m]);
	return 0;
}