#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void cMin(reg int& a,reg int b){
	if(a>b) a=b;
	return;
}

const int MAXN=5e4+5;
const int MAXM=1e5+5;

struct Rule{
	int i,hi,j,hj;
	inline void Read(void){
		static char a,b;
		i=read(),a=getchar(),j=read(),b=getchar();
		hi=a-'A',hj=b-'A';
		return;
	}
};

int n,d,m;
char str[MAXN];
Rule R[MAXM];
int cnt,head[MAXN<<1],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN<<1];
int tim,dfn[MAXN<<1],low[MAXN<<1];
int top,S[MAXN<<1];
int scc_cnt,col[MAXN<<1];

inline void tarjan(reg int u){
	dfn[u]=low[u]=++tim;
	vis[u]=true;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++scc_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(v!=u);
	}
	return;
}

int p[MAXN];
int pos[MAXN][3];
int Ans[MAXN<<1];
int pa[MAXN<<1];

inline void Solve(void){
	cnt=0;
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	for(reg int i=1;i<=n;++i)
		pa[pa[i]=n+i]=i;
	for(reg int i=1;i<=m;++i)
		if(p[R[i].i]!=R[i].hi){
			reg int u=pos[R[i].i][R[i].hi],v=pos[R[i].j][R[i].hj];
			if(p[R[i].j]==R[i].hj)
				Add_Edge(u,pa[u]);
			else
				Add_Edge(u,v),Add_Edge(pa[v],pa[u]);
		}
	for(reg int i=1;i<=2*n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(col[i]!=col[i+n])
			pa[col[i+n]]=col[i],pa[col[i]]=col[i+n];
		else
			return;
	for(reg int i=1;i<=n;++i)
		putchar('A'+Ans[i+(col[i]<col[i+n]?0:n)]);
	putchar('\n');
	exit(0);
	return;
}

vector<int> V;

int main(void){
	n=read(),d=read();
	read(str+1);
	m=read();
	for(reg int i=1;i<=m;++i)
		R[i].Read();
	for(reg int i=1;i<=n;++i)
		switch(p[i]=str[i]-'a'){
			case 0:{
				pos[i][1]=i,pos[i][2]=i+n;
				Ans[i]=1,Ans[i+n]=2;
				break;
			}
			case 1:{
				pos[i][0]=i,pos[i][2]=i+n;
				Ans[i]=0,Ans[i+n]=2;
				break;
			}
			case 2:{
				pos[i][0]=i,pos[i][1]=i+n;
				Ans[i]=0,Ans[i+n]=1;
				break;
			}
		}
	for(int i=1;i<=n;++i)
		if(p[i]>2)
			V.push_back(i);
	for(reg int i=0;i<(1<<d);++i){
		for(reg int j=0;j<d;++j)
			switch(p[V[j]]=((i>>j)&1)){
				case 0:{
					pos[V[j]][1]=V[j],pos[V[j]][2]=V[j]+n;
					Ans[V[j]]=1,Ans[V[j]+n]=2;
					break;
				}
				case 1:{
					pos[V[j]][0]=V[j],pos[V[j]][2]=V[j]+n;
					Ans[V[j]]=0,Ans[V[j]+n]=2;
					break;
				}
				case 2:{
					pos[V[j]][0]=V[j],pos[V[j]][1]=V[j]+n;
					Ans[V[j]]=0,Ans[V[j]+n]=1;
					break;
				}
				default:break;
			}
		Solve();
	}
	puts("-1");
	return 0;
}