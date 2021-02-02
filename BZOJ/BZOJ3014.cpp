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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=4e4+5;
const int inf=0x3f3f3f3f;

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool del[MAXN];
int siz[MAXN];

int rt,MaxPart,sum;

inline void getRt(reg int u,reg int father){
	siz[u]=1;
	reg int Max=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v]){
			getRt(v,u);
			siz[u]+=siz[v];
			Max=max(Max,siz[v]);
		}
	}
	Max=max(Max,sum-siz[u]);
	if(Max<MaxPart)
		rt=u,MaxPart=Max;
	return;
}

bool tag[MAXN];
bool S[MAXN];
int top;
int Maxdep[MAXN],dep[MAXN];
int T[MAXN];

inline void dfs1(reg int u,reg int father){
	reg bool flag=false;
	if(top&&S[top]!=tag[u])
		--top;
	else
		flag=true,S[++top]=tag[u];
	dep[u]=dep[father]+(tag[u]?1:-1);
	Maxdep[u]=max(Maxdep[father],-dep[u]);
	if(!top||S[top])
		T[top]=max(T[top],Maxdep[u]+top);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v])
			dfs1(v,u);
	}
	if(flag)
		--top;
	else
		S[++top]=!tag[u];
	return;
}

int ans;

inline void dfs2(reg int u,reg int father){
	reg bool flag=false;
	if(top&&S[top]!=tag[u])
		--top;
	else
		flag=true,S[++top]=tag[u];
	dep[u]=dep[father]+(tag[u]?1:-1);
	Maxdep[u]=max(Maxdep[father],dep[u]);
	if((!top||!S[top])&&T[top]>=0)
		ans=max(ans,max(T[top],Maxdep[u]+top));
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v])
			dfs2(v,u);
	}
	if(flag)
		--top;
	else
		S[++top]=!tag[u];
	return;
}

int V[MAXN];

inline void calc(reg int u,reg int siz){
	reg int tot=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v])
			V[++tot]=v;
	}
	for(reg int i=1;i<=siz;++i)
		T[i]=-inf;
	T[0]=0;
	for(reg int i=1;i<=tot;++i){
		reg int v=V[i];
		S[top=1]=tag[u];
		if(tag[u])
			Maxdep[u]=dep[u]=1;
		else
			Maxdep[u]=dep[u]=-1;
		dfs2(v,u);
		top=0,Maxdep[u]=dep[u]=0;
		dfs1(v,u);
	}
	for(reg int i=1;i<=siz;++i)
		T[i]=-inf;
	T[0]=0;
	for(reg int i=tot;i>=1;--i){
		reg int v=V[i];
		S[top=1]=tag[u];
		if(tag[u])
			Maxdep[u]=dep[u]=1;
		else
			Maxdep[u]=dep[u]=-1;
		dfs2(v,u);
		top=0,Maxdep[u]=dep[u]=0;
		dfs1(v,u);
	}
	return;
}

inline void solve(reg int u){
	calc(u,siz[u]);
	del[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v]){
			rt=0,MaxPart=inf,sum=siz[v];
			getRt(v,0),solve(rt);
		}
	}
	return;
}

int n;

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i){
		static int fa;
		fa=read();
		Add_Edge(fa,i),Add_Edge(i,fa);
	}
	for(reg int i=1;i<=n;++i){
		static char ch;
		do
			ch=getchar();
		while(ch!='('&&ch!=')');
		tag[i]=(ch=='(');
	}
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	printf("%d\n",ans);
	return 0;
}