#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

#define tr(x) ( (x) << 1 )
#define fl(x) ( (x) << 1 | 1 )

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e6+5;
const int MAXS=6e6+5;

struct Node{
	int id,len;
	inline Node(reg int id=0,reg int len=0):id(id),len(len){
		return;
	}
	inline bool operator<(const Node& a)const{
		return len<a.len;
	}
};

int n;
string s[MAXN];
Node p[MAXN];

int cnt,head[MAXS],to[MAXS],Next[MAXS];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Add(reg int u,reg int v){
	Add_Edge(u,v);
	Add_Edge(v^1,u^1);
	return;
}

bool vis[MAXS];
int tim,dfn[MAXS],low[MAXS];
int top,S[MAXS];
int scc_cnt,col[MAXS];

inline void tarjan(reg int u){
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	vis[u]=true;
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
		++scc_cnt;
		reg int v;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(v!=u);
	}
	return;
}

int tot;
int son[MAXS][2];

inline void insert(reg int u,reg int len,reg int p){
	reg int x=n+1,last=0;
	for(reg int i=0,c;i<len;++i){
		c=s[u][i]-'0';
		if(!son[x][c])
			son[x][c]=++tot;
		last=x;
		x=son[x][c];
		Add(p,tr(x));
	}
	reg int y=++tot;
	Add(p,fl(y)),Add(tr(y),tr(x));
	son[last][s[u][len-1]-'0']=y;
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		cin>>s[i];
		p[i]=Node(i,s[i].length());
	}
	sort(p+1,p+n+1);
	tot=n+1;
	for(reg int i=1;i<=n;++i){
		reg int u=p[i].id;
		for(reg int j=0;j<p[i].len;++j)
			if(s[u][j]=='?'){
				s[u][j]='0';
				insert(u,p[i].len,tr(u));
				s[u][j]='1';
				insert(u,p[i].len,fl(u));
				break;
			}
			else if(j==p[i].len-1)
				insert(u,p[i].len,tr(u)),Add(fl(u),tr(u));
	}
	for(reg int i=1;i<=(tot<<1|1);++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=tot;++i)
		if(col[tr(i)]==col[fl(i)]){
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}