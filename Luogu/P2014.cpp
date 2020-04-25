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

const int MAXN=300+5;
const int MAXM=300+5;

int n,m;
int fa[MAXN];
int f[MAXN][MAXM];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int,reg int);
inline void DFS(reg int);

int main(void){
	reg int i;
	n=read(),m=read();
	for(i=1;i<=n;++i){
		static int fa;
		fa=read(),f[i][1]=read();
		Add_Edge(fa,i);
	}
	DFS(0);
	printf("%d\n",f[0][m+1]);
	return 0;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID){
	reg int i,j,k;
	for(i=head[ID];i;i=Next[i]){
		DFS(to[i]);
		for(j=m+1;j>=1;--j)
			for(k=0;k<j;++k)
				f[ID][j]=max(f[ID][j],f[ID][j-k]+f[to[i]][k]);
	}
	return;
}