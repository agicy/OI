#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=600+5;
const int MAXM=100000+5;

int n,m1,m2;
int dis[MAXN][MAXN];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int Tarjan_cnt,color[MAXN];

inline void Tarjan(reg int ID){
	vis[ID]=true;
	dfn[ID]=low[ID]=++tim;
	S[++top]=ID;
	for(reg int i=head[ID];i;i=Next[i])
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			low[ID]=min(low[ID],low[to[i]]);
		}
		else if(vis[to[i]])
			low[ID]=min(low[ID],dfn[to[i]]);
	if(dfn[ID]==low[ID]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=S[top--];
			vis[To]=false;
			color[To]=Tarjan_cnt;
		}while(To!=ID);
	}
	return;
}

int Max[MAXN];

int main(void){
	n=read(),m1=read(),m2=read();
	memset(dis,0X3F,sizeof(dis));
	for(reg int i=1;i<=n;++i)
		dis[i][i]=0;
	for(reg int i=1;i<=m1;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
		dis[a][b]=min(dis[a][b],-1);
		dis[b][a]=min(dis[b][a],1);
	}
	for(reg int i=1;i<=m2;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		dis[a][b]=min(dis[a][b],0);
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			Tarjan(i);
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			if(color[i]==color[k])
				for(reg int j=1;j<=n;++j)
					if(color[i]==color[j])
						dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(reg int i=1;i<=n;++i)
		if(dis[i][i]!=0){
			puts("NIE");
			return 0;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(color[i]==color[j])
				Max[color[i]]=max(Max[color[i]],dis[i][j]);
	int ans=0;
	for(reg int i=1;i<=Tarjan_cnt;++i)
		ans+=Max[i];
	printf("%d\n",ans+Tarjan_cnt);
	return 0;
}