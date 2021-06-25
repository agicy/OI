#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline void Yes(void){
	puts("YES");
	exit(0);
	return;
}

inline void No(void){
	puts("NO");
	exit(0);
	return;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];
int deg[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

ll f[MAXN];

inline void dfs(reg int u,reg int father){
	if(deg[u]==1){
		f[u]=a[u];
		return;
	}
	reg ll Max=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			f[u]+=f[v];
			Max=max(Max,f[v]);
		}
	}
	reg ll p=((Max<<1)>f[u])?(f[u]-Max):(f[u]>>1);
	if(f[u]<a[u]||f[u]-a[u]>p)
		No();
	f[u]=(a[u]<<1)-f[u];
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	if(n==2){
		if(a[1]==a[2])
			Yes();
		else
			No();
	}
	else{
		for(reg int i=1;i<n;++i){
			static int a,b;
			a=read(),b=read();
			++deg[a],++deg[b];
			Add_Edge(a,b),Add_Edge(b,a);
		}
		for(reg int i=1;i<=n;++i)
			if(deg[i]>1){
				dfs(i,0);
				if(f[i])
					No();
				else
					Yes();
			}
	}
	return 0;
}