#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e4+5;
const int MAXLOG2N=14+1;

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN],dis[MAXN];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dis[v]=dis[u]+w[i];
			dfs(v,u);
		}
	}
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int getFa(reg int x,reg int k){
	for(reg int i=0;i<MAXLOG2N;++i)
		if((k>>i)&1)
			x=fa[x][i];
	return x;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		cnt=0,fill(head+1,head+n+1,0);
		for(reg int i=1;i<n;++i){
			static int a,b,c;
			a=read(),b=read(),c=read();
			Add_Edge(a,b,c),Add_Edge(b,a,c);
		}
		dfs(1,0);
		reg bool flag=true;
		while(flag){
			static char opt;
			static int a,b,k;
			do
				opt=getchar();
			while(!isalpha(opt));
			switch(opt){
				case 'D':{
					opt=getchar();
					switch(opt){
						case 'I':{
							a=read(),b=read();
							writeln(dis[a]+dis[b]-(dis[LCA(a,b)]<<1));
							break;
						}
						case 'O':{
							flag=false;
							break;
						}
					}
					break;
				}
				case 'K':{
					a=read(),b=read(),k=read();
					reg int lca=LCA(a,b);
					if(k<=dep[a]-dep[lca]+1)
						writeln(getFa(a,k-1));
					else
						writeln(getFa(b,dep[a]+dep[b]-(dep[LCA(a,b)]<<1)+1-k));
					break;
				}
			}
		}
	}
	flush();
	return 0;
}