#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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
const int MAXM=500000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	return;
}

bool vis[MAXN],cut[MAXN];
int size[MAXN];
int tim,dfn[MAXN],low[MAXN];
ll ans[MAXN];

inline void Tarjan(reg int ID){
	size[ID]=1;
	vis[ID]=true;
	dfn[ID]=low[ID]=++tim;
	int flag=0,sum=0;
	for(reg int i=head[ID];i;i=Next[i])
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			size[ID]+=size[to[i]];
			low[ID]=min(low[ID],low[to[i]]);
			if(low[to[i]]>=dfn[ID]){
				ans[ID]+=(ll)size[to[i]]*(n-size[to[i]]);
				sum+=size[to[i]];
				++flag;
				if(ID!=1||flag>1)
					cut[ID]=true;
			}
		}
		else if(vis[to[i]])
			low[ID]=min(low[ID],dfn[to[i]]);
	if(!cut[ID])
		ans[ID]=2*(n-1);
	else
		ans[ID]+=(ll)(n-sum-1)*(sum+1)+(n-1);
	return;
}

inline void Work(void){
	Tarjan(1);
	for(reg int i=1;i<=n;++i)
		printf("%lld\n",ans[i]);
	return;
}
