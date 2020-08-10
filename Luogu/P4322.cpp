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

const int MAXN=2.5e3+5;
const int MAXK=2.5e3+5;

int K,n;
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int s[MAXN],p[MAXN];
double val[MAXN];
int size[MAXN];
double f[MAXN][MAXN];

inline void dfs(reg int u){
	size[u]=1;
	f[u][0]=0,f[u][1]=val[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dfs(v);
		static double tmp[MAXN];
		memset(tmp,0xc2,sizeof(tmp));
		tmp[0]=0;
		for(reg int j=1;j<=size[u];++j)
			for(reg int k=0;k<=size[v];++k)
				tmp[j+k]=max(tmp[j+k],f[u][j]+f[v][k]);
		size[u]+=size[v];
		for(reg int j=1;j<=size[u];++j)
			f[u][j]=tmp[j];
	}
	return;
}

inline bool check(reg double x){
	memset(f,0xc2,sizeof(f));
	for(reg int i=1;i<=n;++i)
		val[i]=p[i]-x*s[i];
	dfs(0);
	return f[0][K+1]>0;
}

const double eps=1e-4;

int main(void){
	K=read(),n=read();
	for(reg int i=1;i<=n;++i){
		static int r;
		s[i]=read(),p[i]=read(),r=read();
		Add_Edge(r,i);
	}
	reg double l=0,r=1e5,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%.3lf\n",l);
	return 0;
}