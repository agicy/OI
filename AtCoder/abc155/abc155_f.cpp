#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int ans=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')ans=10*ans+ch-'0',ch=getchar();
	return ans;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;

int n,m;
int a[MAXN],b[MAXN];
vector<int> V;
int c[MAXN],diff[MAXN];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int tot,ans[MAXM];

inline int dfs(reg int u,reg int father,reg int x){
	vis[u]=true;
	reg int t=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v])
			t^=dfs(v,u,i);
	}
	if(u==father)
		return t;
	if(diff[u]^t){
		ans[++tot]=w[x];
		return 1;
	}
	return 0;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read(),b[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		c[a[i]]=b[i];
	}
	for(reg int i=1;i<=n;++i)
		diff[i]=c[i-1]^c[i];
	for(reg int i=1;i<=m;++i){
		static int L,R;
		L=read(),R=read();
		L=lower_bound(V.begin(),V.end(),L)-V.begin()+1;
		R=upper_bound(V.begin(),V.end(),R)-V.begin();
		if(L<=R){
			Add_Edge(L,R+1,i);
			Add_Edge(R+1,L,i);
		}
	}
	dfs(n+1,n+1,0);
	for(reg int i=1;i<=n;++i){
		if(vis[i])
			continue;
		if(dfs(i,i,0)!=diff[i]){
			puts("-1");
			exit(0);
		}
	}
	printf("%d\n",tot);
	sort(ans+1,ans+tot+1);
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i==tot?'\n':' ');
	return 0;
}