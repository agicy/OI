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

const int MAXN=150+5;
const int MAXM=5e3+5;
const int inf=0x3f3f3f3f;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m,q;
int f[MAXN][MAXN][MAXN];
Edge E[MAXM];

inline void cMin(reg int& a,reg int b){
	if(a>b)
		a=b;
	return;
}

int main(void){
	n=read(),m=read(),q=read();
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=m;++i)
		E[i].u=read(),E[i].v=read(),E[i].w=read();
	sort(E+1,E+m+1);
	for(reg int i=1;i<=n;++i)
		f[i][i][0]=0;
	for(reg int k=1;k<=m;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				cMin(f[i][E[k].v][j],f[i][E[k].u][j-1]+E[k].w);
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				cMin(f[i][j][k],f[i][j][k-1]);
	while(q--){
		static int a,b,c;
		a=read(),b=read(),c=read();
		cMin(c,n);
		if(f[a][b][c]==inf)
			puts("-1");
		else
			printf("%d\n",f[a][b][c]);
	}
	return 0;
}