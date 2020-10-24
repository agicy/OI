#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	char ch=getchar();
	ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n;
ll hp[MAXN],ad[MAXN],de[MAXN],val[MAXN];
ll r[MAXN],R[MAXN],Val[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN];

inline void dfs(int u,int father){
	fa[u]=father;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(v!=father)
			dfs(v,u);
	}
	return;
}

int Fa[MAXN];

inline int find(int x){
	if(x==Fa[x])
		return x;
	else
		return Fa[x]=find(Fa[x]);
}

inline void fight(int u){
	hp[1]-=(ad[u]-de[1])*r[u];
	de[1]+=val[u];
	return;
}

bool killed[MAXN],vis[MAXN];
vector<int> Nxt[MAXN];
priority_queue<pair<double,int>/**/> Q;

inline void kill(int u){
	fight(u);
	killed[u]=true;
	for(auto x:Nxt[u])
		kill(x);
	return;
}

int main(void){
	n=read();
	for(int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs(1,0);
	hp[1]=read(),ad[1]=read(),de[1]=read();
	for(int i=2;i<=n;++i){
		hp[i]=read(),ad[i]=read(),de[i]=read(),val[i]=read();
		r[i]=hp[i]/(ad[1]-de[i]);
		if(hp[i]%(ad[1]-de[i])==0)
			--r[i];
		R[i]=r[i],Val[i]=val[i];
		Q.push(make_pair(1.0*val[i]/r[i],i));
	}
	killed[1]=true;
	for(int i=1;i<=n;++i)
		Fa[i]=i;
	while(!Q.empty()){
		static pair<double,int> p;
		p=Q.top();
		Q.pop();
		int u=p.second;
		if(vis[u])
			continue;
		vis[u]=true;
		if(killed[fa[u]]){
			kill(u);
			continue;
		}
		int f=find(fa[u]);
		R[f]+=R[u],Val[f]+=Val[u];
		Nxt[f].push_back(u);
		Fa[u]=f;
		Q.push(make_pair(1.0*Val[f]/R[f],f));
	}
	printf("%lld\n",hp[1]);
	return 0;
}