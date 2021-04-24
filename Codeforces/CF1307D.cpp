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

const int MAXN=2e5+5;

int n,m,k;
int a[MAXN];
vector<int> G[MAXN];
int dis1[MAXN],dis2[MAXN];

inline void bfs(reg int s,reg int dis[]){
	reg int _head=0,_tail=0;
	static int Q[MAXN];
	fill(dis+1,dis+n+1,-1);
	dis[s]=0,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(int v:G[u])
			if(dis[v]==-1)
				dis[v]=dis[u]+1,Q[_tail++]=v;
	}
	return;
}

inline bool cmp(reg int a,reg int b){
	return dis1[a]<dis1[b];
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=k;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	bfs(1,dis1),bfs(n,dis2);
	sort(a+1,a+k+1,cmp);
	reg int res=dis1[n];
	reg int ans=0;
	for(reg int i=1;i<k;++i)
		ans=max(ans,min(res,min(dis1[a[i]]+dis2[a[i+1]],dis1[a[i+1]]+dis2[a[i]])+1));
	printf("%d\n",ans);
	return 0;
}