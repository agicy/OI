#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=5e4+5;
const int base=1331;

int n;
char s[MAXN];
ull basep[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int tot,rt,del[MAXN],siz[MAXN],Rt[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void getRt(reg int u,reg int father,reg int sum){
	siz[u]=1;
	reg int Max=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v]){
			getRt(v,u,sum);
			siz[u]+=siz[v];
			Max=max(Max,siz[v]);
		}
	}
	Max=max(Max,sum-siz[u]);
	rt=(Max<<1)<=sum?u:rt;
	return;
}

inline void build(reg int u,reg int sum){
	rt=0;
	getRt(u,0,sum);
	u=rt;
	del[u]=true;
	Rt[++tot]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v])
			build(v,siz[v]<siz[u]?siz[v]:sum-siz[u]);
	}
	return;
}

int top;
int dep[MAXN];
ull Hash[MAXN];

inline void dfs(reg int u,reg int father,reg int len,reg ull Hash1,reg ull Hash2,reg int depth){
	Hash[++top]=Hash1*basep[len-depth+1]-Hash2;
	dep[top]=depth;
	if(depth>=len)
		return;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v])
			dfs(v,u,len,Hash1+s[v]*basep[depth-1],Hash2*base+s[v],depth+1);
	}
	return;
}

set<ull> S[MAXN];

inline bool solve(reg int u,reg int len){
	del[u]=true;
	for(reg int i=1;S[i].size();++i)
		S[i].clear();
	S[1].insert(-s[u]);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v]){
			top=0;
			dfs(v,u,len,s[v],s[u]*base+s[v],2);
			for(reg int j=1;j<=top;++j)
				if(S[len-dep[j]+1].find(Hash[j])!=S[len-dep[j]+1].end())
					return true;
			for(reg int j=1;j<=top;++j)
				S[dep[j]].insert(Hash[j]);
		}
	}
	return false;
}

inline bool check(reg int len){

	fill(del+1,del+n+1,false);
	for(reg int i=1;i<=tot;++i)
		if(solve(Rt[i],len))
			return true;
	return false;
}

inline int solve(reg int sgn){
	reg int l=0,r=(n+1)>>1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check((mid+1)<<1|sgn))
			l=mid+1;
		else
			r=mid;
	}
	return l<<1|sgn;
}

int main(void){
	n=read();
	read(s+1);
	for(reg int i=1;i<=n;++i)
		s[i]=s[i]-'a'+1;
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*base;
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	build(1,n);
	printf("%d\n",max(solve(0),solve(1)));
	return 0;
}