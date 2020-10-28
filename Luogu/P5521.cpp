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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e5+4+5;

int n;
int w[MAXN],ans[MAXN];
vector<int> son[MAXN];

inline bool cmp(reg int a,reg int b){
	return ans[a]-w[a]>ans[b]-w[b];
}

inline void dfs(reg int u){
	ans[u]=w[u];
	for(auto v:son[u]){
		dfs(v);
		ans[u]+=w[v];
	}
	sort(son[u].begin(),son[u].end(),cmp);
	reg int sum=0;
	for(auto v:son[u]){
		cMax(ans[u],ans[v]+sum);
		sum+=w[v];
	}
	return;
}

int main(void){
	n=read();
	for(int i=2;i<=n;++i){
		static int p;
		p=read();
		son[p].push_back(i);
	}
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	dfs(1);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}