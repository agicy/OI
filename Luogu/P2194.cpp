#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXM=300000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int v[MAXN];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read();
	m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
	}
	return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int Tarjan_cnt,s[MAXN],w[MAXN];

inline void Tarjan(reg int ID){
	vis[ID]=true;
	dfn[ID]=low[ID]=++tim;
	S[++top]=ID;
	for(reg int i=head[ID];i;i=Next[i]){
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			low[ID]=min(low[ID],low[to[i]]);
		}
		else if(vis[to[i]]){
			low[ID]=min(low[ID],dfn[to[i]]);
		}
	}
	if(dfn[ID]==low[ID]){
		++Tarjan_cnt;
		w[Tarjan_cnt]=INF;
		reg int to;
		do{
			to=S[top--];
			vis[to]=false;
			if(v[to]<w[Tarjan_cnt])
				w[Tarjan_cnt]=v[to],s[Tarjan_cnt]=0;
			if(v[to]==w[Tarjan_cnt])
				++s[Tarjan_cnt];
		}while(to!=ID);
	}
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			Tarjan(i);
	reg ll ans1=0,ans2=1;
	for(reg int i=1;i<=Tarjan_cnt;++i){
		ans1+=w[i];
		ans2=ans2*s[i]%MOD;
	}
	printf("%lld %lld\n",ans1,ans2);
	return;
}
