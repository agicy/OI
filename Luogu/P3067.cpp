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

const int MAXN=20+1;
const int MAXSIZE=3*3*3*3*3*3*3*3*3*3+5;

int n;
int a[MAXN];
int tot;
vector<int> V[MAXSIZE];
map<ll,int> M;

inline void dfs1(reg int dep,ll sum,int S){
	if(dep==(n/2)+1){
		if(!M.count(sum))
			M[sum]=++tot;
		V[M[sum]].push_back(S);
		return;
	}
	dfs1(dep+1,sum+a[dep],S|(1<<(dep-1)));
	dfs1(dep+1,sum-a[dep],S|(1<<(dep-1)));
	dfs1(dep+1,sum,S);
	return;
}

int ans;
bool vis[1<<MAXN];

inline void dfs2(reg int dep,reg ll sum,reg int S){
	if(dep==n+1){
		if(M.count(-sum)){
			reg int id=M[-sum];
			for(reg int i=0,siz=V[id].size();i<siz;++i)
				vis[S|V[id][i]]=true;
		}
		return;
	}
	dfs2(dep+1,sum+a[dep],S|(1<<(dep-1)));
	dfs2(dep+1,sum-a[dep],S|(1<<(dep-1)));
	dfs2(dep+1,sum,S);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	dfs1(1,0,0);
	dfs2((n/2)+1,0,0);
	reg int ans=0;
	for(reg int i=1;i<(1<<n);++i)
		if(vis[i])
			++ans;
	printf("%d\n",ans);
	return 0;
}