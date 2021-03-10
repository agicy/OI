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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e4+5;
const int MAXM=5e4+5;
const int MAXV=10*MAXM;

struct Edge{
	int u,v,c,t;
	inline void Read(void){
		u=read(),v=read(),c=read(),t=read();
		return;
	}
};

int n,m,tot;
Edge e[MAXM];
vector<int> V[MAXN];
vector<int> G[MAXV];

inline void buildpre(vector<int> V){
	int lasS,lasT;
	for(reg int i=0,siz=V.size();i<siz;++i){
		int x=V[i],y=V[i]+m,s=++tot,t=++tot;
		G[x].push_back(s),G[t].push_back(y);
		if(i){
			G[lasS].push_back(s),G[lasS].push_back(y);
			G[t].push_back(lasT),G[x].push_back(lasT);
		}
		lasS=s,lasT=t;
	}
	return;
}

inline void buildsuf(vector<int> V){
	int lasS,lasT;
	for(reg int i=0,siz=V.size();i<siz;++i){
		int x=V[i],y=V[i]+m,s=++tot,t=++tot;
		G[s].push_back(x),G[y].push_back(t);
		if(i){
			G[lasT].push_back(t),G[lasT].push_back(x);
			G[s].push_back(lasS),G[y].push_back(lasS);
		}
		lasS=s,lasT=t;
	}
	return;
}

bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int scc_cnt,col[MAXV];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(int v:G[u])
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u]){
		reg int v;
		++scc_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(v!=u);
	}
	return;
}

inline bool check(reg int mid){
	for(reg int i=1;i<=m;++i)
		if(e[i].t>mid)
			G[i].push_back(i+m);
	for(reg int i=1;i<=tot;++i)
		dfn[i]=0;
	scc_cnt=tim=0;
	for(reg int i=1;i<=tot;++i)
		if(!dfn[i])
			tarjan(i);
	reg bool flag=true;
	for(reg int i=1;i<=m;++i)
		if(col[i]==col[i+m]){
			flag=false;
			break;
		}
	for(reg int i=1;i<=m;++i)
		if(e[i].t>mid)
			G[i].pop_back();
	return flag;
}

inline bool cmp(reg int a,reg int b){
	return e[a].c<e[b].c;
}

int main(void){
	n=read(),m=read(),tot=m<<1;
	reg int l=0,r=0;
	for(int i=1;i<=m;++i){
		e[i].Read();
		V[e[i].u].push_back(i),V[e[i].v].push_back(i);
		r=max(r,e[i].t);
	}
	for(reg int i=1;i<=n;++i){
		sort(V[i].begin(),V[i].end(),cmp);
		buildpre(V[i]);
		for(reg int l=0,r=0,siz=V[i].size();l<siz;l=r+1){
			vector<int> tmp;
			tmp.push_back(V[i][l]);
			r=l;
			while(r+1<siz&&e[V[i][r+1]].c==e[V[i][r]].c)
				tmp.push_back(V[i][++r]);
			buildsuf(tmp);
		}
	}
	if(!check(r))
		puts("No");
	else{
		puts("Yes");
		while(l<r){
			reg int mid=(l+r)>>1;
			if(check(mid))
				r=mid;
			else
				l=mid+1;
		}
		check(l);
		vector<int> ans;
		for(int i=1;i<=m;++i)
			if(col[i]<col[i+m])
				ans.push_back(i);
		printf("%d %lu\n",l,ans.size());
		for(reg int i=0,siz=ans.size();i<siz;++i)
			printf("%d%c",ans[i],i==siz-1?'\n':' ');
	}
	return 0;
}