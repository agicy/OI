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

const int MAXN=2500+5;

int n,m,s;
int deg[MAXN],inDeg[MAXN];
bool vis[MAXN],tot;
vector<pair<int,int>/**/> E[MAXN];
ll sum;

int bak_fa[MAXN],bak_size[MAXN],bak_deg[MAXN];

namespace UnionFind{
	int fa[MAXN],size[MAXN];
	inline void Init(void){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,size[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(int a,int b){
		if(size[a]>size[b])
			swap(a,b);
		fa[a]=b;
		size[b]+=size[a];
		return;
	}
}

using namespace UnionFind;

inline ll Solve(reg int t){
	++inDeg[t];
	for(reg int i=1;i<=n;++i){
		vis[i]=false;
		fa[i]=bak_fa[i],size[i]=bak_size[i],deg[i]=bak_deg[i];
		E[i].clear();
	}
	if(s!=t)
		deg[s]^=1,deg[t]^=1;
	reg ll ans=sum;
	reg int last=0;
	for(reg int i=1;i<=n;++i)
		if(deg[i]==1){
			if(last){
				for(reg int j=last;j<i;++j){
					++ans;
					merge(find(j),find(j+1));
				}
				last=0;
			}
			else
				last=i;
		}
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		if(inDeg[i]){
			reg int x=find(i);
			if(!vis[x]){
				vis[x]=true;
				++tot;
			}
		}
	for(int l=1,r;l<n;l=r){
		r=l+1;
		if(!inDeg[l])
			continue;
		while(r<=n&&!inDeg[r])
			++r;
		if(inDeg[r])
			E[r-l].push_back(make_pair(l,r));
	}
	for(reg int i=1;i<n&&tot>1;++i)
		for(reg int j=0,size=E[i].size();j<size;++j){
			pair<int,int> p=E[i][j];
			reg int u=find(p.first),v=find(p.second);
			u=find(u),v=find(v);
			if(u!=v){
				merge(u,v);
				--tot;
				ans+=2*i;
				if(tot==1)
					break;
			}
		}
	--inDeg[t];
	return ans;
}

int main(void){
	n=read(),m=read(),s=read();
	inDeg[s]=1;
	Init();
	for(reg int i=1;i<=m;++i){
		reg int u=read(),v=read();
		sum+=abs(u-v);
		bak_deg[u]^=1,bak_deg[v]^=1;
		inDeg[u]=inDeg[v]=1;
		u=find(u),v=find(v);
		if(u!=v)
			merge(u,v);
	}
	for(reg int i=1;i<=n;++i)
		bak_fa[i]=fa[i],bak_size[i]=size[i];
	for(reg int t=1;t<=n;++t)
		printf("%lld%c",Solve(t),t==n?'\n':' ');
	return 0;
}