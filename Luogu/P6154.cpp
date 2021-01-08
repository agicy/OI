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

const int MAXN=1e5+5;
const int MAXM=7e5+5;
const int p=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int pow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int n,m;
int indeg[MAXN];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	++indeg[v];
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int Q[MAXN];
int f[MAXN],g[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(y,x);
	}
	reg int head_=0,tail_=0;
	for(reg int i=1;i<=n;++i){
		g[i]=1;
		if(!indeg[i]){
			f[i]=0;
			Q[tail_++]=i;
		}
	}
	while(head_<tail_){
		reg int u=Q[head_++];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			--indeg[v];
			f[v]=add(f[v],add(f[u],g[u]));
			g[v]=add(g[v],g[u]);
			if(!indeg[v])
				Q[tail_++]=v;
		}
	}
	reg int sumf=0,sumg=0;
	for(reg int i=1;i<=n;++i)
		sumf=add(sumf,f[i]),sumg=add(sumg,g[i]);
	printf("%lld\n",1ll*sumf*pow(sumg,p-2)%p);
	return 0;
}