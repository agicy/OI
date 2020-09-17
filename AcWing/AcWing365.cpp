#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e3+5;
const int MAXV=MAXN;
const int MAXE=MAXN*MAXN*2;

int n,m;
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
bool cut[MAXV];
int vDcc_cnt;
vector<int> vDcc[MAXV];

inline void tarjan(int u,reg int root){
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	if(u==root&&!head[u]){
		vDcc[++vDcc_cnt].push_back(u);
		return;
	}
	reg bool flag=false;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,root);
			cMin(low[u],low[v]);
			if(low[v]>=dfn[u]){
				if(flag||u!=root)
					cut[u]=true;
				flag=true;
				++vDcc_cnt;
				int tmp;
				do{
					tmp=S[top--];
					vDcc[vDcc_cnt].push_back(tmp);
				}while(tmp!=v);
				vDcc[vDcc_cnt].push_back(u);
			}
		}
		else
			cMin(low[u],dfn[v]);
	}
	return;
}

int vDcc_id[MAXN];
int col[MAXN];

inline bool dfs(reg int u,reg int c){
	col[u]=c;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(vDcc_id[u]==vDcc_id[v]){
			if(col[v]==col[u])
				return true;
			if(!col[v]&&dfs(v,c^1))
				return true;
		}
	}
	return false;
}

bool G[MAXN][MAXN];
bool ans[MAXN];

int main(void){
	while(n=read(),m=read(),n!=0&&m!=0){
		memset(G,false,sizeof(G));
		for(reg int i=1;i<=m;++i){
			static int a,b;
			a=read(),b=read();
			G[a][b]=G[b][a]=true;
		}
		cnt=0,memset(head,0,sizeof(head));
		for(reg int i=1;i<=n;++i)
			for(reg int j=i+1;j<=n;++j)
				if(!G[i][j]){
					Add_Edge(i,j);
					Add_Edge(j,i);
				}
		tim=0,memset(dfn,0,sizeof(dfn));
		for(reg int i=1;i<=n;++i)
			if(!dfn[i]){
				top=0;
				tarjan(i,i);
			}
		memset(ans,false,sizeof(ans));
		memset(vDcc_id,0,sizeof(vDcc_id));
		memset(col,0,sizeof(col));
		for(reg int i=1;i<=vDcc_cnt;++i){
			for(reg int j=0,siz=vDcc[i].size();j<siz;++j){
				reg int v=vDcc[i][j];
				vDcc_id[v]=i;
				col[v]=0;
			}
			if(dfs(vDcc[i][0],2))
				for(reg int j=0,siz=vDcc[i].size();j<siz;++j){
					reg int v=vDcc[i][j];
					ans[v]=true;
				}
			vDcc[i].clear();
		}
		reg int sum=0;
		for(reg int i=1;i<=n;++i)
			if(!ans[i])
				++sum;
		printf("%d\n",sum);
		vDcc_cnt=0;
	}
	return 0;
}