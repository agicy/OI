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

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

const int MAXN=1e6+5;
const int MAXM=1e6+5;
const int MAXV=4*MAXN;
const int MAXE=6*MAXN+2*MAXM;

int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
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

int n,m,k;
int arr[MAXN];

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a+n,b);
		Add_Edge(b+n,a);
	}
	for(reg int i=1;i<=k;++i){
		reg int w=read();
		for(reg int j=1;j<=w;++j)
			arr[j]=read();
		for(reg int j=1;j<=w;++j)
			Add_Edge(arr[j],arr[j]+n*2),Add_Edge(arr[j],arr[j]+n*3);
		for(reg int j=2;j<=w;++j)
			Add_Edge(arr[j]+n*2,arr[j-1]+n*2),Add_Edge(arr[j]+n*2,arr[j-1]+n);
		for(reg int j=w-1;j>=1;--j)
			Add_Edge(arr[j]+n*3,arr[j+1]+n*3),Add_Edge(arr[j]+n*3,arr[j+1]+n);
	}
	for(reg int i=1;i<=(n<<2);++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(col[i]==col[i+n])
			puts("NIE"),exit(0);
	puts("TAK");
	return 0;
}