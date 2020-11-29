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
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int k;
int siz[MAXN];

inline int dfs(reg int u,reg int father){
	siz[u]=0;
	unordered_map<int,int> M;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(!dfs(v,u))
				return false;
			int tmp=k-siz[v];
			if(M.count(tmp)&&M[tmp]){
				--M[tmp];
				if(!M[tmp])
					M.erase(tmp);
				siz[u]-=tmp;
			}
			else if(k!=siz[v])
				siz[u]+=siz[v],++M[siz[v]];
		}
	}
	++siz[u];
	if(M.size()>1)
		return false;
	else
		return true;
}

bool ans[MAXN];
bool vis[MAXN];
int tot,prime[MAXN];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

int main(void){
	n=read();
	Init(n-1);
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for(reg int i=n-1;i>=1;--i){
		if((n-1)%i)
			continue;
		for(reg int j=1;j<=tot&&i*prime[j]<n;++j)
			if(ans[i*prime[j]]){
				ans[i]=true;
				break;
			}
		if(!ans[i]){
			k=i;
			ans[i]=dfs(1,0);
		}
	}
	for(reg int i=1;i<n;++i)
		putchar(ans[i]+'0');
	putchar('\n');
	return 0;
}