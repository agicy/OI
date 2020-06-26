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
const int MAXM=100000+5;

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	//freopen("sequence.in","r",stdin);
	//freopen("sequence.out","w",stdout);
	reg int T=read();
	while(T--){
		Init();
		Read();
		Work();
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

struct Edge{
	int u,v;
	inline Edge(reg int u=0,reg int v=0):u(u),v(v){
		return;
	}
};

struct Graph{
	int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
	inline void Init(void){
		cnt=0;
		memset(head,0,sizeof(head));
		return;
	}
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v){
		Add_Edge(u,v);
		Add_Edge(v,u);
		return;
	}
};

int n,m;
int cnt,tot;
int a[MAXN];
Graph G,Gp;
Edge E[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		a[i]=x-a[i];
	}
	for(reg int i=1;i<=m;++i){
		static int t,u,v;
		t=read(),u=read(),v=read();
		switch(t){
			case 1:E[++cnt]=Edge(u,v);break;
			case 2:G.Add_Tube(u,v);break;
			default:break;
		}
	}
	return;
}

int color[MAXN];
ll sum[MAXN];
int vis[MAXN];
bool tag[MAXN];

inline void DFS1(reg int ID,reg int col,const Graph& G){
	color[ID]=col;
	sum[col]+=a[ID];
	for(reg int i=G.head[ID];i;i=G.Next[i])
		if(!color[G.to[i]])
			DFS1(G.to[i],col,G);
	return;
}

bool target;
ll sumB,sumW;

inline bool DFS2(reg int ID,reg int col,const Graph& Gp){
	if(vis[ID]!=-1)
		return vis[ID]==col;
	vis[ID]=col;
	target|=tag[ID];
	if(col==0)
		sumB+=sum[ID];
	else
		sumW+=sum[ID];
	reg bool res=true;
	for(reg int i=Gp.head[ID];i;i=Gp.Next[i])
		res&=DFS2(Gp.to[i],col^1,Gp);
	return res;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		if(!color[i])
			DFS1(i,++tot,G);
	for(reg int i=1;i<=cnt;++i)
		if(color[E[i].u]==color[E[i].v])
			tag[color[E[i].u]]=true;
		else
			Gp.Add_Tube(color[E[i].u],color[E[i].v]);
	reg bool ans=true;
	for(reg int i=1;i<=tot;++i)
		if(vis[i]==-1){
			target=false;
			sumB=sumW=0;
			if(DFS2(i,0,Gp))
				if(target)
					ans&=(((sumB+sumW)&1)==0);
				else
					ans&=(sumB==sumW);
			else
				ans&=(((sumB+sumW)&1)==0);
		}
	puts(ans?"YES":"NO");
	return;
}

inline void Init(void){
	cnt=tot=0;
	G.Init();
	Gp.Init();
	memset(color,0,sizeof(color));
	memset(sum,0,sizeof(sum));
	memset(tag,false,sizeof(tag));
	memset(vis,-1,sizeof(vis));
	return;
}
