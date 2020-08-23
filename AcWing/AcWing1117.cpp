#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=20+5;
const int MAXL=20+5;

int n;
char str[MAXN][MAXL];

inline int check(reg int i,reg int j){
	int li=strlen(str[i]+1),lj=strlen(str[j]+1);
	reg int len=min(li,lj);
	int res=len;
	for(int ans=1;ans<len;++ans){
		reg bool flag=false;
		for(reg int ptr=1;ptr<=ans;++ptr)
			if(str[i][li-ans+ptr]!=str[j][ptr]){
				flag=true;
				break;
			}
		if(!flag)
			res=min(res,ans);
	}
	return res;
}

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int ans;
vector<Edge> G[MAXN];
int vis[MAXN];

inline void dfs(reg int u,int sum){
	ans=max(ans,sum);
	for(reg int i=0,size=G[u].size();i<size;++i){
		reg int v=G[u][i].v;
		if(vis[v]<2){
			++vis[v];
			dfs(v,sum+G[u][i].w);
			--vis[v];
		}
	}
	return;
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%s",str[i]+1);
	char ch;
	cin>>ch;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			int li=strlen(str[i]+1),lj=strlen(str[j]+1);
			reg int len=min(li,lj);
			reg int l=check(i,j);
			if(0<l&&l<len)
				G[i].push_back(Edge(j,lj-l));
		}
	for(reg int i=1;i<=n;++i)
		sort(G[i].begin(),G[i].end());
	for(reg int i=1;i<=n;++i)
		if(str[i][1]==ch){
			++vis[i];
			dfs(i,strlen(str[i]+1));
			--vis[i];
		}
	printf("%d\n",ans);
	return 0;
}