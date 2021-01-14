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

inline void cMax(reg int &a,reg int b){
	if(a<b) a=b;
	return;
}

const int MAXN=5e5+5;
const int MAXM=1e6+5;

int n,m;
int ds[MAXN],dt[MAXN];

namespace DAG{
	int indeg[MAXN];
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		++indeg[v];
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int Q[MAXN];
	int tot,dfn[MAXN];
	inline void topo(void){
		reg int head_=0,tail_=0;
		for(reg int i=1;i<=n;++i)
			if(!indeg[i])
				Q[tail_++]=i;
		while(head_<tail_){
			reg int u=Q[head_++];
			dfn[++tot]=u;
			for(reg int i=head[u];i;i=Next[i]){
				reg int v=to[i];
				--indeg[v];
				if(!indeg[v])
					Q[tail_++]=v;
			}
		}
		return;
	}
}

namespace invG{
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

namespace Heap{
	priority_queue<int> p,q;
	inline void del(const int& x){
		q.push(x);
		return;
	}
	inline void push(const int& x){
		p.push(x);
		return;
	}
	inline int top(void){
		while(!q.empty()&&p.top()==q.top())
			p.pop(),q.pop();
		return p.top();
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1,a,b;i<=m;++i){
		a=read(),b=read();
		DAG::Add_Edge(a,b),invG::Add_Edge(b,a);
	}
	DAG::topo();
	for(reg int id=1,u;id<=n&&(u=DAG::dfn[id]);++id)
		for(reg int i=DAG::head[u];i;i=DAG::Next[i])
			cMax(dt[DAG::to[i]],dt[u]+1);
	for(reg int id=n,u;id>=1&&(u=DAG::dfn[id]);--id)
		for(reg int i=invG::head[u];i;i=invG::Next[i])
			cMax(ds[invG::to[i]],ds[u]+1);
	for(reg int i=1;i<=n;++i)
		Heap::push(ds[i]);
	pair<int,int> ans=make_pair(Heap::top(),n+1);
	for(reg int id=1;id<=n;++id){
		reg int u=DAG::dfn[id];
		Heap::del(ds[u]);
		for(reg int i=invG::head[u];i;i=invG::Next[i])
			Heap::del(dt[invG::to[i]]+ds[u]+1);
		ans=min(ans,make_pair(Heap::top(),u));
		Heap::push(dt[u]);
		for(reg int i=DAG::head[u];i;i=DAG::Next[i])
			Heap::push(dt[u]+ds[DAG::to[i]]+1);
	}
	printf("%d %d\n",ans.second,ans.first);
	return 0;
}