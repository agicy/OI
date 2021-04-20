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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

const int MAXN=2e3+5;
const int MAXV=2*MAXN;

inline int getA(reg int i){
	return (i<<1)-1;
}

inline int getB(reg int i){
	return i<<1;
}

int n;
int a[MAXN];
vector<int> G[MAXV];

inline void Add_Edge(reg int u,reg int v){
	G[u].push_back(v);
	return;
}

bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int scc_cnt,col[MAXV];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(int v:G[u])
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u]){
		++scc_cnt;
		reg int v;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(u!=v);
	}
	return;
}

vector<int> V;
int cnt[MAXN];
int pos[MAXN][4];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		pos[a[i]][cnt[a[i]]++]=i;
	}
	reg int m=V.size();
	for(reg int i=1;i<=m;++i)
		switch(cnt[i]){
			case 2:{
				Add_Edge(getA(pos[i][0]),getB(pos[i][1])),Add_Edge(getB(pos[i][0]),getA(pos[i][1]));
				Add_Edge(getA(pos[i][1]),getB(pos[i][0])),Add_Edge(getB(pos[i][1]),getA(pos[i][0]));
				break;
			}
			case 4:{
				break;
			}
			default:{
				puts("Hello, cnt_World!"),exit(0);
			}
		}
	for(reg int i=1;i<=n;++i){
		if(!dfn[getA(i)])
			tarjan(getA(i));
		if(!dfn[getB(i)])
			tarjan(getB(i));
		if(col[getA(i)]==col[getB(i)])
			puts("Hello, cir_World!"),exit(0);
	}
	
	return 0;
}