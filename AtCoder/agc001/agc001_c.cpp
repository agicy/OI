#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e3+5;

int n,k;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dis[MAXN];

inline int dfs(reg int u,reg int father){
	reg int sum=dis[u]>(k>>1);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dis[v]=dis[u]+1;
			sum+=dfs(v,u);
		}
	}
	return sum;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	reg int ans=n;
	if(k&1)
		for(reg int u=1;u<=n;++u)
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				if(u<v){
					dis[u]=dis[v]=0;
					ans=min(ans,dfs(u,v)+dfs(v,u));
				}
			}
	else
		for(reg int i=1;i<=n;++i){
			dis[i]=0;
			ans=min(ans,dfs(i,0));
		}
	printf("%d\n",ans);
	return 0;
}