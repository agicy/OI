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
const int MAXM=1e5+5;

int n,m;

namespace DAG{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int indeg[MAXN];
	int tot,ans[MAXN];
	priority_queue<int> Q;
	inline void topo(void){
		for(int i=1;i<=n;++i)
			if(!indeg[i])
				Q.push(i);
		while(!Q.empty()){
			reg int u=Q.top();
			Q.pop();
			ans[++tot]=u;
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				--indeg[v];
				if(!indeg[v])
					Q.push(v);
			}
		}
		return;
	}
	inline void Init(void){
		cnt=0,memset(head,0,sizeof(head));
		memset(indeg,0,sizeof(indeg));
		tot=0;
		return;
	}
}

int main(void){
	reg int D=read();
	while(D--){
		n=read(),m=read();
		DAG::Init();
		for(reg int i=1;i<=m;++i){
			static int x,y;
			x=read(),y=read();
			++DAG::indeg[x];
			DAG::Add_Edge(y,x);
		}
		DAG::topo();
		if(DAG::tot!=n)
			puts("Impossible!");
		else
			for(reg int i=1;i<=n;++i)
				printf("%d%c",DAG::ans[n-i+1],i==n?'\n':' ');
	}
	return 0;
}