#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=2e5+5;
const int MAXA=20;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN];
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
	if(Max<MaxPart){
		rt=u,MaxPart=Max;
	}
	return;
}

ll T[1<<MAXA];

inline void dfs(reg int u,reg int father,reg int tag,reg int S){
	S^=(1<<a[u]);
	T[S]+=tag;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v])
			dfs(v,u,tag,S);
	}
	return;
}

ll ans[MAXN];

inline ll dfs(reg int u,reg int father,reg int S){
	S^=(1<<a[u]);
	reg ll sum=T[S];
	for(reg int i=0;i<MAXA;++i)
		sum+=T[S^(1<<i)];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v])
			sum+=dfs(v,u,S);
	}
	ans[u]+=sum;
	return sum;
}

inline void calc(reg int u){
	dfs(u,0,1,0);
	reg ll sum=T[0];
	for(reg int i=0;i<MAXA;++i)
		sum+=T[1<<i];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v]){
			dfs(v,u,-1,1<<a[u]);
			sum+=dfs(v,u,0);
			dfs(v,u,1,1<<a[u]);
		}
	}
	dfs(u,0,-1,0);
	ans[u]+=(sum>>1);
	return;
}

inline void solve(reg int u){
	del[u]=true;
	calc(u);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v]){
			rt=0,MaxPart=inf,sum=siz[v];
			getRt(v,0),solve(rt);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	static char str[MAXN];
	read(str+1);
	for(reg int i=1;i<=n;++i)
		a[i]=str[i]-'a';
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	for(reg int i=1;i<=n;++i)
		write(ans[i]+1),putchar(i==n?'\n':' ');
	flush();
	return 0;
}