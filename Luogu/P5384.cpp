#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=1000000+5;
const int MAXLOG2N=18+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,Q;
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),Q=read();
	for(reg int i=2;i<=n;++i)
		Add_Edge(read(),i);
	return;
}

int dep[MAXN];
int fa[MAXN][MAXLOG2N];
int tim,dfn[MAXN],end[MAXN];
vector<int> V[MAXN];

inline void DFS(reg int ID,reg int father){
	dfn[ID]=++tim;
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	V[dep[ID]].push_back(dfn[ID]);
	for(reg int i=1;i<MAXLOG2N;++i){
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
		if(!fa[ID][i])
			break;
	}
	for(reg int i=head[ID];i;i=Next[i])
		DFS(to[i],ID);
	end[ID]=tim;
	return;
}

inline int GetFa(reg int ID,reg int k){
	for(reg int i=0;i<MAXLOG2N&&k;++i)
		if(k&(1<<i))
			ID=fa[ID][i],k^=(1<<i);
	return ID;
}

inline void Work(void){
	DFS(1,0);
	for(reg int i=1;i<=Q;++i){
		static int u,k;
		u=read(),k=read();
		if(k>=dep[u])
			printf("%d%c",0,i==Q?'\n':' ');
		else{
			reg int fa=GetFa(u,k);
			int l=dfn[fa],r=end[fa];
			reg int pos=dep[u];
			reg int cnt=upper_bound(V[pos].begin(),V[pos].end(),r)-upper_bound(V[pos].begin(),V[pos].end(),l);
			printf("%d%c",cnt-1,i==Q?'\n':' ');
		}
	}
	return;
}
