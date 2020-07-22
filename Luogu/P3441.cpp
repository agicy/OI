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

const int MAXN=1000000+5;

int n,l;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Node{
	int u,dep;
	inline Node(reg int u=0,reg int dep=0):u(u),dep(dep){
		return;
	}
};

int deg[MAXN];
int T[MAXN];
queue<Node> Q;

int main(void){
	n=read(),l=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
		++deg[a],++deg[b];
	}
	for(int i=1;i<=n;++i)
		if(deg[i]==1)
			Q.push(Node(i,1));
	while(!Q.empty()){
		int u=Q.front().u,dep=Q.front().dep;
		Q.pop();
		++T[dep];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			--deg[v];
			if(deg[v]==1)
				Q.push(Node(v,dep+1));
		}
	}
	reg int ans=0;
	for(reg int i=1;T[i];++i)
		ans+=min(2*l,T[i]);
	printf("%d\n",ans);
	return 0;
}
