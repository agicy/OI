#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMax(reg ll& a,reg ll b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=3e5+5;
const int MAXM=2*MAXN;
const int INF=1e9+7;

int n,w[MAXN];
char s[MAXN];

namespace SAM{
	struct Node{
		int link,dep,size;
		int next[26];
		int Max[2],Min[2];
		inline Node(void){
			Max[0]=Max[1]=-INF;
			Min[0]=Min[1]=INF;
			link=dep=size=0;
			memset(next,0,sizeof(next));
			return;
		}
		#define link(x) unit[(x)].link
		#define dep(x) unit[(x)].dep
		#define size(x) unit[(x)].size
		#define next(x) unit[(x)].next
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
	};
	int tot,last;
	Node unit[MAXM];
	inline void Init(void){
		last=tot=1;
		return;
	}
	inline void insert(reg int ch,reg int w){
		reg int p=last;
		reg int np=++tot;
		dep(np)=dep(p)+1;
		Max(np)[0]=Min(np)[0]=w;
		size(np)=1;
		while(p&&next(p)[ch]==0){
			next(p)[ch]=np;
			p=link(p);
		}
		if(!p)
			link(np)=1;
		else{
			reg int q=next(p)[ch];
			if(dep(p)+1==dep(q))
				link(np)=q;
			else{
				reg int nq=++tot;
				memcpy(next(nq),next(q),sizeof(next(q)));
				link(nq)=link(q);
				dep(nq)=dep(p)+1;
				link(np)=link(q)=nq;
				while(p&&next(p)[ch]==q){
					next(p)[ch]=nq;
					p=link(p);
				}
			}
		}
		last=np;
		return;
	}
	int cnt,head[MAXM],to[MAXM],Next[MAXM];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void checkMax(reg int u,reg int w){
		if(w>Max(u)[0]){
			Max(u)[1]=Max(u)[0];
			Max(u)[0]=w;
		}
		else if(w>Max(u)[1])
			Max(u)[1]=w;
		return;
	}
	inline void checkMin(reg int u,reg int w){
		if(w<Min(u)[0]){
			Min(u)[1]=Min(u)[0];
			Min(u)[0]=w;
		}
		else if(w<Min(u)[1])
			Min(u)[1]=w;
		return;
	}
	ll sum[MAXM],ans[MAXM];
	inline void dfs(reg int u){
		reg int size=0;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			dfs(v);
			size+=size(v);
			checkMax(u,Max(v)[0]),checkMax(u,Max(v)[1]);
			checkMin(u,Min(v)[0]),checkMin(u,Min(v)[1]);
		}
		if(size+size(u)<2)
			return;
		cMax(ans[dep(u)],max(1ll*Max(u)[0]*Max(u)[1],1ll*Min(u)[0]*Min(u)[1]));
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			sum[dep(u)]+=1ll*size(u)*size(v);
			size(u)+=size(v);
		}
		return;
	}
	inline void Solve(void){
		memset(ans,-63,sizeof(ans));
		for(reg int i=2;i<=tot;++i)
			Add_Edge(link(i),i);
		dfs(1);
		for(reg int i=n-1;i>=0;--i)
			sum[i]+=sum[i+1],cMax(ans[i],ans[i+1]);
		for(reg int i=0;i<n;++i)
			printf("%lld %lld\n",sum[i],sum[i]?ans[i]:0);
		return;
	}
}

int main(void){
	SAM::Init();
	n=read();
	scanf("%s",s+1);
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=n;i>=1;--i)
		SAM::insert(s[i]-'a',w[i]);
	SAM::Solve();
	return 0;
}