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

int n;
int x[MAXN],y[MAXN];
vector<int> G[MAXN];
int dep[MAXN];
int cnt[2];
bool vis[2][MAXN];

inline void bfs(reg int s){
	reg int _head=0,_tail=0;
	static int Q[MAXN];
	fill(dep+1,dep+n+1,-1);
	dep[s]=0,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(int v:G[u])
			if(dep[v]==-1)
				dep[v]=dep[u]+1,Q[_tail++]=v;
	}
	return;
}

inline bool check(reg int st,reg int ed,reg int len){
	if(n&1)
		return false;
	cnt[0]=cnt[1]=0;
	fill(vis[0]+1,vis[0]+n+1,false);
	fill(vis[1]+1,vis[1]+n+1,false);
	for(reg int i=1;i<=n;++i) G[i].clear();
	for(reg int i=1;i<n;++i)
		if(x[i]!=st&&y[i]!=st&&x[i]!=ed&&y[i]!=ed)
			G[x[i]].push_back(y[i]),G[y[i]].push_back(x[i]);
	for(reg int i=1;i<=n;++i)
		if(G[i].size()){
			bfs(i);
			break;
		}
	reg int s=1;
	for(reg int i=1;i<=n;++i)
		if(dep[s]<dep[i])
			s=i;
	bfs(s);
	reg int e=s;
	for(reg int i=1;i<=n;++i)
		if(dep[e]<dep[i])
			e=i;
	reg int l=dep[e];
	if(l!=len-2)
		return false;
	for(reg int i=1;i<=n;++i)
		if(dep[i]==dep[e])
			++cnt[1],vis[1][i]=true;
	bfs(e);
	for(reg int i=1;i<=n;++i)
		if(dep[i]==dep[s])
			++cnt[0],vis[0][i]=true;
	reg bool flag=false;
	for(reg int i=1;i<=n;++i)
		if(vis[0][i]&&vis[1][i]){
			flag=true;
			break;
		}
	if(cnt[0]==1&&cnt[1]==1)
		return true;
	else if(cnt[0]>=3&&cnt[1]>=3)
		return false;
	else if(cnt[0]>=2&&cnt[1]>=2&&!flag)
		return false;
	else if(cnt[0]>=2&&cnt[1]>=2&&max(cnt[0],cnt[1])>=3)
		return false;
	else
		return true;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		x[i]=read(),y[i]=read();
		G[x[i]].push_back(y[i]),G[y[i]].push_back(x[i]);
	}
	bfs(1);
	reg int st=1;
	for(reg int i=1;i<=n;++i)
		if(dep[st]<dep[i])
			st=i;
	bfs(st);
	reg int ed=st;
	for(reg int i=1;i<=n;++i)
		if(dep[ed]<dep[i])
			ed=i;
	reg int len=dep[ed];
	for(reg int i=1;i<=n;++i)
		if(dep[i]==dep[ed])
			++cnt[1],vis[1][i]=true;
	bfs(ed);
	for(reg int i=1;i<=n;++i)
		if(dep[i]==dep[st])
			++cnt[0],vis[0][i]=true;
	reg bool flag=false;
	for(reg int i=1;i<=n;++i)
		if(vis[0][i]&&vis[1][i]){
			flag=true;
			break;
		}
	reg int ans;
	if(cnt[0]==1&&cnt[1]==1)
		if(check(st,ed,len))
			ans=len-2;
		else
			ans=len-1;
	else if(cnt[0]>=3&&cnt[1]>=3)
		ans=len;
	else if(cnt[0]>=2&&cnt[1]>=2&&!flag)
		ans=len;
	else if(cnt[0]>=2&&cnt[1]>=2&&max(cnt[0],cnt[1])>=3)
		ans=len;
	else if(n&1)
		ans=len;
	else
		ans=len-1;
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf ms\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}