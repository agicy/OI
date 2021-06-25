#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e3+5;
const int MAXM=5e3+5;

inline void Slavko(void){
	putchar('S'),putchar('l'),putchar('a'),putchar('v'),putchar('k'),putchar('o'),putchar('\n');
	return;
}

inline void Mirko(void){
	putchar('M'),putchar('i'),putchar('r'),putchar('k'),putchar('o'),putchar('\n');
	return;
}

int n,m;
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,vis[MAXN];
int mat[MAXN];

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

bool ans[MAXN];

inline void getAns(reg int u){
	ans[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(mat[v]&&!ans[mat[v]])
			getAns(mat[v]);
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int v,d;
		v=read(),d=read();
		Add_Edge(v,d);
	}
	for(reg int i=1;i<=n;++i){
		++tim;
		dfs(i);
	}
	++tim;
	for(reg int i=1;i<=n;++i)
		vis[mat[i]]=tim;
	for(reg int i=1;i<=n;++i)
		if(vis[i]!=tim)
			getAns(i);
	for(reg int i=1;i<=n;++i)
		if(ans[i])
			Mirko();
		else
			Slavko();
	flush();
	return 0;
}