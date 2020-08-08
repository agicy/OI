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

const int MAXN=1.5e5+5;
const int MAXQ=2e5+5;
const int inf=0x3f3f3f3f;

int n,Q,A;
int x[MAXN];

namespace Tree{
	struct Edge{
		int to,w;
		inline Edge(reg int to=0,reg int w=0):to(to),w(w){
			return;
		}
	};
	vector<Edge> G[MAXN];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		G[u].push_back(Edge(v,len));
		return;
	}
	struct Nodef{
		int id,fa,dis;
		inline Nodef(reg int id=0,reg int fa=0,reg int dis=0):id(id),fa(fa),dis(dis){
			return;
		}
	};
	struct Nodes{
		int age,cnt;
		ll dis;
		inline Nodes(reg int age=0,reg int cnt=0,reg ll dis=0):age(age),cnt(cnt),dis(dis){
			return;
		}
		inline bool operator<(const Nodes& a)const{
			return age<a.age;
		}
	};
	vector<Nodef> fa[MAXN];
	vector<Nodes> son[MAXN][3];
	bitset<MAXN> del;
	int root,MaxPart;
	int size[MAXN];
	int _tot;
	inline void DFS1(reg int u,reg int father){
		size[u]=1;
		int Max=0;
		for(auto E:G[u]){
			reg int v=E.to;
			if(v!=father&&!del[v]){
				DFS1(v,u);
				size[u]+=size[v];
				Max=max(Max,size[v]);
			}
		}
		Max=max(Max,_tot-size[u]);
		if(Max<MaxPart)
			root=u,MaxPart=Max;
		return;
	}
	int dis[MAXN];
	int _id;
	inline void DFS2(reg int u,reg int father){
		fa[u].push_back(Nodef(_id,root,dis[u]));
		son[root][_id].push_back(Nodes(x[u],1,dis[u]));
		for(auto E:G[u]){
			reg int v=E.to,w=E.w;
			if(v!=father&&!del[v]){
				dis[v]=dis[u]+w;
				DFS2(v,u);
			}
		}
		return;
	}
	inline void solve(reg int u,reg int tot){
		if(tot==1){
			del[u]=true;
			fa[u].push_back(Nodef(-1,u,0));
			return;
		}
		MaxPart=inf;
		_tot=tot;
		DFS1(u,0);
		del[root]=true;
		fa[root].push_back(Nodef(-1,root,0));
		reg int id=0;
		for(auto E:G[root]){
			reg int v=E.to,w=E.w;
			if(del[v])
				continue;
			dis[v]=w;
			_id=id;
			DFS2(v,0);
			son[root][id].push_back(Nodes(inf,0,0));
			sort(son[root][id].begin(),son[root][id].end());
			for(reg int j=son[root][id].size()-2;j>=0;--j){
				son[root][id][j].cnt+=son[root][id][j+1].cnt;
				son[root][id][j].dis+=son[root][id][j+1].dis;
			}
			++id;
		}
		for(auto E:G[root]){
			reg int v=E.to;
			if(!del[v])
				solve(v,size[v]);
		}
		return;
	}
	inline ll query(reg int l,reg int r,reg int u){
		reg ll res=0;
		static vector<Nodes>::iterator L,R;
		for(reg int i=fa[u].size()-1;i>=0;--i){
			reg int f=fa[u][i].fa;
			for(reg int id=0;id<3;++id){
				if(id==fa[u][i].id||son[f][id].empty())
					continue;
				L=lower_bound(son[f][id].begin(),son[f][id].end(),Nodes(l,0,0));
				R=upper_bound(son[f][id].begin(),son[f][id].end(),Nodes(r,0,0));
				res+=1ll*fa[u][i].dis*(L->cnt-R->cnt)+L->dis-R->dis;
			}
			if(l<=x[f]&&x[f]<=r)
				res+=fa[u][i].dis;
		}
		return res;
	}
}

int main(void){
	n=read(),Q=read(),A=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read();
	for(reg int i=1;i<n;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Tree::Add_Edge(a,b,c);
		Tree::Add_Edge(b,a,c);
	}
	Tree::solve(1,n);
	reg ll lastans=0;
	for(reg int i=1;i<=Q;++i){
		static int u;
		static ll a,b;
		u=read(),a=read(),b=read();
		a=(a+lastans)%A,b=(b+lastans)%A;
		if(a>b)
			swap(a,b);
		printf("%lld\n",lastans=Tree::query(a,b,u));
	}
	return 0;
}