#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e3+5;

int n;
int u[MAXN],v[MAXN],w[MAXN];
int Maxp[MAXN];
int cnt=1,head[MAXN],to[MAXN<<2],W[MAXN<<2],Next[MAXN<<2];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,W[cnt]=len;
	head[u]=cnt;
	return;
}

inline int getMaxw(reg int a,reg int b){
	return W[a]>W[b]?a:b;
}

inline int dfs(reg int u,reg int father,reg int t){
	if(u==t)
		return 0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			reg int tmp=dfs(v,u,t);
			if(tmp!=-1)
				return getMaxw(i,tmp);
		}
	}
	return -1;
}

bool del[MAXN<<2];
int Maxpp[MAXN];

inline void dfs2(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i])
		if(!del[i]){
			reg int v=to[i];
			if(v!=father){
				Maxpp[v]=getMaxw(Maxpp[u],i);
				dfs2(v,u);
			}
		}
	return;
}

int main(void){
	n=read();
	reg ll ans=0;
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
		ans+=w;
	}
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read(),w[i]=read();
		Maxp[i]=dfs(u[i],0,v[i]);
	}
	writeln(ans);
	bitset<MAXN> S;
	S.set();
	S[0]=false;
	for(reg int i=1;i<n;++i){
		reg int ptr=S._Find_first();
		for(reg int j=S._Find_next(ptr);j<n;j=S._Find_next(j))
			if(w[j]-W[Maxp[j]]<w[ptr]-W[Maxp[ptr]])
				ptr=j;
		S[ptr]=false;
		del[Maxp[ptr]]=del[Maxp[ptr]^1]=true;
		Add_Edge(u[ptr],v[ptr],0),Add_Edge(v[ptr],u[ptr],0);
		ans+=w[ptr]-W[Maxp[ptr]];
		Maxpp[u[ptr]]=Maxpp[v[ptr]]=0;
		dfs2(u[ptr],v[ptr]),dfs2(v[ptr],u[ptr]);
		for(reg int j=1;j<n;++j)
			if(j!=ptr&&del[Maxp[j]])
				Maxp[j]=getMaxw(Maxpp[u[j]],Maxpp[v[j]]);
		writeln(ans);
	}
	flush();
	return 0;
}