#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;

struct Edge{
	int v,w;
	inline Edge(reg int v=0,reg int w=0):v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

struct Path{
	int u,v,id;
	ll w;
	inline Path(reg int u=0,reg int v=0,reg int id=0,reg ll w=0):u(u),v(v),id(id),w(w){
		return;
	}
	inline bool operator<(const Path& a)const{
		return w<a.w;
	}
	inline bool operator>(const Path& a)const{
		return w>a.w;
	}
};

int n,m,k;
vector<Edge> G[MAXN];
priority_queue<Path,vector<Path>,greater<Path>/**/> Q;
map<pair<int,int>,bool> M;

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		G[u].push_back(Edge(v,w)),G[v].push_back(Edge(u,w));
	}
	for(reg int i=1;i<=n;++i){
		sort(G[i].begin(),G[i].end());
		M[make_pair(i,i)]=true;
		Q.push(Path(i,i,0,G[i][0].w));
	}
	k<<=1;
	while(!Q.empty()){
		static Path s;
		s=Q.top();
		Q.pop();
		reg int u=s.u,v=s.v,id=s.id;
		reg ll w=s.w;
		if(!M[make_pair(u,G[v][id].v)]){
			M[make_pair(u,G[v][id].v)]=true;
			--k;
			if(!k){
				printf("%lld\n",w);
				break;
			}
			Q.push(Path(u,G[v][id].v,0,w+G[G[v][id].v][0].w));
		}
		if(id+1<(int)G[v].size())
			Q.push(Path(u,v,id+1,w-G[v][id].w+G[v][id+1].w));
	}
	return 0;
}