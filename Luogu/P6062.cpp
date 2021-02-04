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
	while(*s!='*'&&*s!='.')*s=getchar();
	while(*s=='*'||*s=='.')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=50+5;
const int MAXM=50+5;
const int MAXV=MAXN*MAXM*2;
const int MAXE=MAXN*MAXM;

int n,m;
char M[MAXN][MAXM];
int id1[MAXN][MAXM],id2[MAXN][MAXM];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,vis[MAXV];
int mat[MAXV];

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(vis[v]!=tim){
			vis[v]=tim;
			if(!mat[v]||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	reg int cnt1=0,cnt2=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='*'){
				if(M[i][j-1]=='*')
					id1[i][j]=id1[i][j-1];
				else
					id1[i][j]=++cnt1;
				if(M[i-1][j]=='*')
					id2[i][j]=id2[i-1][j];
				else
					id2[i][j]=++cnt2;
			}
	reg int tmp=n*m;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			Add_Edge(id1[i][j],id2[i][j]+tmp);
	reg int ans=0;
	for(reg int i=1;i<=cnt1;++i)
		if(!mat[i]){
			++tim;
			if(dfs(i))
				++ans;
		}
	printf("%d\n",ans);
	return 0;
}