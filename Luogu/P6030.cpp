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

const double eps=1e-7,INF=1e18;
const int MAXS=100+5,MAXN=1e4+5,MAXM=1e6+5;

int n,m,S,T;
int Deg[MAXN],id[MAXN];

int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,dfn[MAXN],low[MAXN];
int top,Stack[MAXN];
bool vis[MAXN];
int Tarjan_cnt,color[MAXN];
vector<int>SCC[MAXN];

inline void Tarjan(reg int ID){
	vis[ID]=true;
	dfn[ID]=low[ID]=++tim;
	Stack[++top]=ID;
	for(reg int i=head[ID];i;i=Next[i]){
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			low[ID]=min(low[ID],low[to[i]]);
		}
		else if(vis[to[i]])
			low[ID]=min(low[ID],dfn[to[i]]);
	}
	if(dfn[ID]==low[ID]){
		int To;
		++Tarjan_cnt;
		do{
			To=Stack[top--];
			vis[To]=false;
			color[To]=Tarjan_cnt;
			id[To]=int(SCC[Tarjan_cnt].size())+1;
			SCC[Tarjan_cnt].push_back(To);
		}while(ID!=To);
	}
	return;
}

double F[MAXN],A[MAXS][MAXS],B[MAXS],x[MAXS];

inline bool Gauss(reg int n){
	for(reg int i=1;i<=n;++i){
		int p=i;
		for(reg int j=i+1;j<=n;++j)
			if(abs(A[j][i])>abs(A[p][i]))
				p=j;
		if(i!=p)
			swap(A[i],A[p]),swap(B[i],B[p]);
		if(abs(A[i][i])<eps)
			return false;
		for(reg int j=i+1;j<=n;++j){
			reg double d=A[j][i]/A[i][i];
			B[j]-=d*B[i];
			for(reg int k=i;k<=n;++k)
				A[j][k]-=d*A[i][k];
		}
	}
	for(reg int i=n;i;--i){
		for(reg int j=i+1;j<=n;++j)
			B[i]-=x[j]*A[i][j];
		x[i]=B[i]/A[i][i];
	}
	return true;
}

int main(void){
	n=read(),m=read(),S=read(),T=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		++Deg[u];
		Add_Edge(u,v);
	}
	Tarjan(S);
	if(!dfn[T]){
		puts("INF");
		return 0;
	}
	for(reg int i=1;i<=Tarjan_cnt;++i){
		memset(A,0,sizeof(A));
		memset(B,0,sizeof(B));
		memset(x,0,sizeof(x));
		for(reg int k=0,size=SCC[i].size();k<size;++k){
			reg int u=SCC[i][k];
			if(u==T){
				A[id[u]][id[u]]=1.0;
				continue;
			}
			reg double p=1.0/Deg[u];
			A[id[u]][id[u]]=1.0,B[id[u]]=1.0;
			for(reg int j=head[u];j;j=Next[j])
				if(color[u]==color[to[j]])
					A[id[u]][id[to[j]]]-=p;
				else
					B[id[u]]+=p*F[to[j]];
			if(!head[u])
				B[id[u]]=INF;
		}
		Gauss(SCC[i].size());
		for(reg int k=0,size=SCC[i].size();k<size;++k){
			F[SCC[i][k]]=x[id[SCC[i][k]]];
			if(F[SCC[i][k]]>1e10)
				F[SCC[i][k]]=INF;
		}
	}
	if(F[S]>1e10)
		puts("INF");
	else
		printf("%.3f\n",F[S]);
	return 0;
}
