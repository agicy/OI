#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

const int MAXN=1e3+5;
const int L=2e9;

int n,m;
int del;
int col[MAXN],deg[MAXN];
int ans[MAXN];
vector<int> G[MAXN];
bitset<MAXN> f[MAXN];

inline bool dfs(reg int u,reg int c){
	if(col[u]>=0)
		return col[u]==c;
	col[u]=c;
	for(int v:G[u])
		if(v!=del&&!dfs(v,c^1))
			return false;
	return true;
}

inline bool check(reg int x){
	del=x;
	fill(col+1,col+n+1,-1);
	for(reg int i=1;i<=n;++i)
		if(i!=del&&col[i]==-1&&!dfs(i,0))
			return false;
	return true;
}

inline bool check(reg int u,reg int c){
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		if(col[i]==c)
			cnt++;
	for(int v:G[u])
		if(col[v]==c)
			--cnt;
	return !cnt;
}

inline bool cmp(reg int x,reg int y){
	return deg[x]<deg[y];
}

inline bool gen(reg int x,reg int y){
	fill(ans+1,ans+n+1,-1);
	ans[del]=(L>>1);
	ans[x]=0;
	reg int colR=col[y];
	for(int v:G[del])
		f[v][del]=false;
	for(reg int i=1;i<=n;++i)
		deg[i]=f[i].count();
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			if(i!=del&&j!=del&&col[i]==col[j]&&(f[i]&f[j]).count()!=0u+min(deg[i],deg[j]))
				return false;
	vector<int> V;
	for(int i=1;i<=n;++i)
		if(i!=del&&col[i]==colR)
			V.push_back(i);
	sort(V.begin(),V.end(),cmp);
	map<int,bool> M;
	reg int cnt=0;
	for(int u:V){
		reg int Max=0;
		for(int v:G[u])
			if(v!=del){
				if(ans[v]==-1)
					ans[v]=++cnt;
				Max=max(Max,ans[v]);
			}
		if(!Max)
			++Max,++cnt;
		while(M.count(Max+(L>>1)))
			++Max,++cnt;
		ans[u]=Max+(L>>1);
		M[Max+(L>>1)]=true;
	}
	ans[y]=L;
	return true;
}

inline void print(reg bool flag){
	if(flag){
		puts("Yes");
		printf("%d ",L);
		for(reg int i=1;i<=n;++i)
			printf("%d%c",ans[i]-(L>>1),i==n?'\n':' ');
	}
	else
		puts("No");
	return;
}

inline void solve(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		G[i].clear(),f[i].reset();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
		f[u][v]=f[v][u]=true;
	}
	if(check(0))
		print(gen(0,0));
	else{
		for(reg int i=1;i<=n;++i)
			if(G[i].size()==2u&&check(i)){
				reg int x=G[i][0],y=G[i][1];
				if(check(x,col[x]^1)&&check(y,col[y]^1)){
					print(gen(x,y));
					return;
				}
			}
		print(false);
	}
	return;
}

int main(void){
	reg int t=read();
	while(t--)
		solve();
	return 0;
}