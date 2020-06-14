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

const int MAXN=3000+5;
const int MAXM=4500+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt=1,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace UnionFind{
	int ID[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

inline void Read(void){
	n=read(),m=read();
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
		UnionFind::merge(u,v);
	}
	return;
}

const ll p=19260817;
ll Hash[MAXN];

bool vis[MAXM<<1];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int Tarjan_cnt,color[MAXN];

inline void Tarjan(reg int ID,reg int Del){
	dfn[ID]=low[ID]=++tim;
	S[++top]=ID;
	for(reg int i=head[ID];i;i=Next[i]){
		if(vis[i]||i==Del||(i^1)==Del)
			continue;
		if(!dfn[to[i]]){
			vis[i]=vis[i^1]=true;
			Tarjan(to[i],Del);
			vis[i]=vis[i^1]=false;
			low[ID]=min(low[ID],low[to[i]]);
		}
		else
			low[ID]=min(low[ID],dfn[to[i]]);
	}
	if(dfn[ID]==low[ID]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=S[top--];
			color[To]=Tarjan_cnt;
		}while(To!=ID);
	}
	return;
}

inline int Calc(reg int u,reg int v){
	if(!UnionFind::search(u,v))
		return 0;
	else if(color[u]!=color[v])
		return 1;
	else if(Hash[u]==Hash[v])
		return 3;
	else
		return 2;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		Hash[i]=1;
	for(reg int Del=1;Del<=m+1;++Del){
		tim=0,Tarjan_cnt=0,top=0;
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		for(reg int i=1;i<=n;++i)
			if(!dfn[i])
				Tarjan(i,Del<<1);
		for(reg int i=1;i<=n;++i)
			Hash[i]=Hash[i]*p+color[i];
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			ans+=Calc(i,j);
	printf("%d\n",ans);
	return;
}