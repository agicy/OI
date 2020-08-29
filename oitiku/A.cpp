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

const int MAXN=1e6+5;

int n;
int fa[MAXN],val[MAXN];

int top,S[MAXN];
int ans[MAXN];

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

vector<Node> G[MAXN];

inline void dfs(reg int u){
	stack<int> s;
	S[++top]=val[u];
	ans[u]=top;
	for(vector<Node>::iterator it=G[u].begin();it!=G[u].end();++it){
		reg int v=it->id;
		while(top&&S[top]<val[v]){
			s.push(S[top]);
			--top;
		}
		dfs(v);
	}
	while(!s.empty()){
		S[++top]=s.top();
		s.pop();
	}
	--top;
	return;
}

int main(void){
	freopen("suffix.in","r",stdin);
	freopen("suffix.out","w",stdout);
	n=read();
	for(reg int i=2;i<=n;++i)
		fa[i]=read();
	for(reg int i=1;i<=n;++i)
		val[i]=read();
	for(reg int i=2;i<=n;++i)
		G[fa[i]].push_back(Node(i,val[i]));
	for(reg int i=1;i<=n;++i)
		sort(G[i].begin(),G[i].end());
	dfs(1);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}