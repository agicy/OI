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

const int MAXN=5e4+5;
const int MAXM=5e5+5;

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
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
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w>a.w;
	}
};

int n,m,k;
Edge W[MAXM],B[MAXM];

int main(void){
	reg int T=read();
	while(T--){
		n=read(),m=read(),k=read();
		reg int totB=0,totW=0;
		for(reg int i=1;i<=m;++i){
			static int u,v,w,c;
			u=read(),v=read(),w=read(),c=read();
			if(c)
				W[++totW]=Edge(u,v,w);
			else
				B[++totB]=Edge(u,v,w);
		}
		UnionFind::Init(n);
		reg ll ans=0;
		reg int cnt=0;
		for(reg int i=1;i<=totB;++i){
			ans+=B[i].w;
			if(!UnionFind::search(B[i].u,B[i].v)){
				++cnt;
				UnionFind::merge(B[i].u,B[i].v);
			}
		}
		//sort(B+1,B+totB+1);
		sort(W+1,W+totW+1);
		priority_queue<int> Q;
		for(reg int i=1;i<=totW&&k;++i)
			if(!UnionFind::search(W[i].u,W[i].v)){
				++cnt,--k;
				ans+=W[i].w;
				UnionFind::merge(W[i].u,W[i].v);
			}
			else
				Q.push(W[i].w);
		if(cnt==n-1){
			while(k&&!Q.empty()){
				--k;
				ans+=Q.top();
				Q.pop();
			}
			printf("%lld\n",ans);
		}
		else
			puts("-1");
	}
	return 0;
}