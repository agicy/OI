#include<bits/stdc++.h>
using namespace std;
#define reg register
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
int x[MAXM],y[MAXM];
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
		x[i]=read(),y[i]=read();
		Add_Edge(x[i],y[i]);
	}
	return;
}

bool vis[MAXN];
int t,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int Tarjan_cnt,color[MAXN],size[MAXN];
int inDeg[MAXN];

inline void Tarjan(reg int ID){
	vis[ID]=true;
	dfn[ID]=low[ID]=++t;
	S[++top]=ID;
	for(reg int i=head[ID];i;i=Next[i]){
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			low[ID]=min(low[ID],low[to[i]]);
		}
		else if(vis[to[i]])
			low[ID]=min(low[ID],dfn[to[i]]);
	}
	if(dfn[ID]==low[ID]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=S[top--];
			vis[To]=false;
			++size[Tarjan_cnt];
			color[To]=Tarjan_cnt;
		}while(To!=ID);
	}
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			Tarjan(i);
	cnt=0;
	memset(head,0,sizeof(head));
	for(reg int i=1;i<=m;++i)
		if(color[x[i]]!=color[y[i]]){
			++inDeg[color[y[i]]];
			Add_Edge(color[x[i]],color[y[i]]);
		}
	reg bool flag=false;
	reg int ans=0;
	for(reg int i=1;i<=Tarjan_cnt;++i){
		if(!flag&&!inDeg[i]&&size[i]==1){
			reg bool temp=false;
			for(reg int j=head[i];j;j=Next[j])
				if(inDeg[to[j]]==1){
					temp=true;
					break;
				}
			flag|=(!temp);
		}
		if(!inDeg[i])
			++ans;
	}
	printf("%.6lf\n",1.0-(double)(ans-flag)/n);
	return;
}
