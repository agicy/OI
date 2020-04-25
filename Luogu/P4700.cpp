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

const int MAXN=300000+5;
const int MAXM=900000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int ID,x,y;
	inline void Read(reg int i){
		ID=i;
		x=read(),y=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return y>a.y;
	}
};

int n,m,A,B;
Node p[MAXN];
int c[MAXM],d[MAXM],k[MAXM];
int flag[MAXN];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
vector<Node> L,R;

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read(),A=read(),B=read();
	for(reg int i=1;i<=n;++i){
		p[i].Read(i);
		if(p[i].x==0){
			flag[i]=-1;
			L.push_back(p[i]);
		}
		if(p[i].x==A)
			flag[i]=1;
	}
	for(reg int i=1;i<=m;++i){
		c[i]=read(),d[i]=read(),k[i]=read();
			Add_Edge(c[i],d[i]);
		if(k[i]!=1)
			Add_Edge(d[i],c[i]);
	}
	return;
}

int tim,dfn[MAXN],low[MAXN];
bool vis[MAXN];
int top,S[MAXN];
int Tarjan_cnt,color[MAXN];

inline void Tarjan(reg int ID){
	if(flag[ID]==1)
		R.push_back(p[ID]);
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

bool mark[MAXN];
int Max[MAXN],Min[MAXN];

inline void DFS(reg int ID){
	if(mark[ID])
		return;
	mark[ID]=true;
	for(reg int i=head[ID];i;i=Next[i]){
		DFS(to[i]);
		Max[ID]=max(Max[ID],Max[to[i]]);
		Min[ID]=min(Min[ID],Min[to[i]]);
	}
	return;
}

inline void Work(void){
	for(reg int i=0;i<(int)L.size();++i)
		if(!dfn[L[i].ID])
			Tarjan(L[i].ID);
	cnt=0,memset(head,0,sizeof(head));
	for(reg int i=1;i<=m;++i)
		if(color[c[i]]!=color[d[i]]){
			Add_Edge(color[c[i]],color[d[i]]);
			if(k[i]!=1)
				Add_Edge(color[d[i]],color[c[i]]);
		}
	memset(Max,0,sizeof(Max));
	memset(Min,0X3F,sizeof(Min));
	sort(L.begin(),L.end());
	sort(R.begin(),R.end());
	for(reg int i=0;i<(int)R.size();++i){
		reg int ID=color[R[i].ID];
		int res=lower_bound(R.begin(),R.end(),R[i])-R.begin()+1;
		Max[ID]=max(Max[ID],res);
		Min[ID]=min(Min[ID],res);
	}
	for(reg int i=0;i<(int)L.size();++i){
		DFS(color[L[i].ID]);
		printf("%d\n",max(Max[color[L[i].ID]]-Min[color[L[i].ID]]+1,0));
	}
	return;
}
