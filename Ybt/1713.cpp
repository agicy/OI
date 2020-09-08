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

const int MAXN=1e3+5;
const int MAXM=1e5+5;
const int MAXSIZE=(1<<15)+5;

struct Edge{
	int s,t,d;
	inline Edge(reg int s=0,reg int t=0,reg int d=0):s(s),t(t),d(d){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return d>a.d;
	}
};

namespace UnionFind{
	int fa[MAXN],dep[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,dep[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra==rb)
			return;
		if(dep[ra]<dep[rb])
			fa[ra]=rb;
		else if(dep[ra]>dep[rb])
			fa[rb]=ra;
		else
			fa[rb]=ra,++dep[ra];
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

bool vis[MAXSIZE];
int tot,prime[MAXSIZE];
int rnk[MAXSIZE];
int from[MAXSIZE];

inline void Init(reg int n){
	from[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			rnk[i]=tot;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true,from[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

inline ll fpow(reg ll x,reg ll exp){
	reg ll res=1;
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}

int n,m;
Edge E[MAXM];
vector<Edge> V[MAXSIZE];

int main(void){
	Init((1<<15)-1);
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int s,t,d;
		s=read(),t=read(),d=read();
		E[i]=Edge(s,t,d);
	}
	int Maxptr=0;
	for(reg int i=1;i<=m;++i){
		reg int tmp=E[i].d;
		while(from[tmp]>1){
			reg int las=from[tmp],cnt=0;
			while(tmp%las==0){
				++cnt;
				tmp/=las;
			}
			V[rnk[las]].push_back(Edge(E[i].s,E[i].t,cnt));
			Maxptr=max(Maxptr,rnk[las]);
		}
	}
	reg ll ans=1;
	for(reg int i=1;i<=Maxptr;++i){
		reg int cnt=n,Min=0;
		UnionFind::Init(n);
		sort(V[i].begin(),V[i].end());
		for(reg int j=0,siz=V[i].size();j<siz&&cnt>1;++j){
			static Edge E;
			E=V[i][j];
			if(!UnionFind::search(E.s,E.t)){
				--cnt;
				Min=E.d;
				UnionFind::merge(E.s,E.t);
			}
		}
		if(cnt==1)
			ans=ans*fpow(prime[i],Min);
	}
	printf("%lld\n",ans);
	return 0;
}