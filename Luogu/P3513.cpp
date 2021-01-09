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

const int MAXN=5e3+5;
const int MAXV=MAXN<<1;
const int MAXE=MAXN*MAXN;
const int inf=0x3f3f3f3f;

inline void cMin(reg int& a,reg int b){
	if(a>b) a=b;
	return;
}

int n;
bool G[MAXN][MAXN];
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
int scc_cnt,col[MAXV],siz[MAXV];

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
			++siz[scc_cnt];
		}while(v!=u);
	}
	return;
}

bool p[MAXN];
int h[MAXN],t[MAXN];
int tag1[MAXN],tag2[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int k,a[MAXN];
		k=read();
		for(reg int j=1;j<=k;++j){
			a[j]=read();
			G[i][a[j]]=true;
		}
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				if(G[i][j])
					Add_Edge(i,j+n);
				else
					Add_Edge(i+n,j);
			}
	}
	for(reg int i=1;i<=(n<<1);++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(col[i]==col[i+n]){
			puts("0");
			return 0;
		}
	if(n==2){
		puts("2");
		return 0;
	}
	for(reg int i=1;i<=n;++i)
		p[i]=col[i+n]>col[i];
	reg int cnt1=0,cnt2=0;
	for(reg int i=1;i<=n;++i)
		if(!p[i])
			h[++cnt1]=i;
		else
			t[++cnt2]=i;
	for(reg int i=1;i<=cnt1;++i){
		reg int x=h[i],cnt=0;
		for(reg int j=1;j<=cnt2;++j){
			reg int y=t[j];
			if(G[x][y]){
				if(cnt==1){
					tag1[i]=inf;
					break;
				}
				++cnt;
				tag1[i]=y;
			}
		}
	}
	for(reg int i=1;i<=cnt2;++i){
		reg int x=t[i],cnt=0;
		for(reg int j=1;j<=cnt1;++j){
			reg int y=h[j];
			if(!G[x][y]){
				if(cnt==1){
					tag2[i]=inf;
					break;
				}
				++cnt;
				tag2[i]=y;
			}
		}
	}
	int ans=1;
	if(cnt1!=1)
		for(reg int i=1;i<=cnt1;++i)
			if(!tag1[i])
				++ans;
	if(cnt2!=1)
		for(reg int i=1;i<=cnt2;++i)
			if(!tag2[i])
				++ans;
	for(reg int i=1;i<=cnt1;++i)
		for(reg int j=1;j<=cnt2;++j)
			if((tag1[i]==t[j]||!tag1[i])&&((tag2[j]==h[i]||!tag2[j])))
				++ans;
	printf("%d\n",min(ans,n));
	return 0;
}