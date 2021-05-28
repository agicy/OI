#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
//#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;

int n,m;
vector<int> G[MAXN];
int fa[MAXN];
int tim,dfn[MAXN],rnk[MAXN],low[MAXN],ed[MAXN],clow[MAXN],ced[MAXN];
int s,t;

inline void tarjan(reg int u,reg int father){
	fa[u]=father;
	dfn[u]=low[u]=clow[u]=++tim;
	rnk[tim]=u;
	ed[u]=ced[u]=u;
	for(int v:G[u])
		if(v!=father){
			if(!dfn[v]){
				tarjan(v,u);
				if(low[v]<low[u]){
					clow[u]=low[u],ced[u]=ed[u];
					low[u]=low[v],ed[u]=ed[v];
				}
				else if(low[v]<clow[u])
					clow[u]=low[v],ced[u]=ed[v];
			}
			else{
				if(dfn[v]<low[u]){
					clow[u]=low[u],ced[u]=ed[u];
					low[u]=dfn[v],ed[u]=u;
				}
				else if(dfn[v]<clow[u])
					clow[u]=dfn[v],ced[u]=u;
			}
		}
	if(!s&&!t&&clow[u]<dfn[u])
		s=u,t=rnk[clow[u]];
	return;
}

inline vector<int> getPath(reg int son,int father){
	vector<int> res;
	for(int p=son;p!=father;p=fa[p])
		res.push_back(p);
	res.push_back(father);
	return res;
}

inline vector<int> reverse(vector<int> a){
	reverse(a.begin(),a.end());
	return a;
}

inline vector<int> merge(vector<int> a,vector<int> b){
	a.insert(a.end(),b.begin(),b.end());
	return a;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),m=read();
		for(reg int i=1;i<=n;++i)
			G[i].clear();
		for(reg int i=1;i<=m;++i){
			static int u,v;
			u=read(),v=read();
			G[u].push_back(v),G[v].push_back(u);
		}
		tim=0,fill(dfn+1,dfn+n+1,0);
		s=0,t=0;
		for(reg int i=1;i<=n;++i)
			if(!dfn[i])
				tarjan(i,0);
		if(!s&&!t)
			write(-1),putchar('\n');
		else{
			write(s),putchar(' '),write(t),putchar('\n');
			vector<int> ans1=getPath(s,t);
			write(ans1.size()),putchar(' ');
			for(reg int i=0,siz=ans1.size();i<siz;++i)
				write(ans1[i]),putchar(i==siz-1?'\n':' ');
			vector<int> ans2=merge(reverse(getPath(ed[s],s)),reverse(getPath(t,rnk[low[s]])));
			write(ans2.size()),putchar(' ');
			for(reg int i=0,siz=ans2.size();i<siz;++i)
				write(ans2[i]),putchar(i==siz-1?'\n':' ');
			vector<int> ans3=merge(reverse(getPath(ced[s],s)),getPath(rnk[clow[s]],rnk[clow[s]]));
			write(ans3.size()),putchar(' ');
			for(reg int i=0,siz=ans3.size();i<siz;++i)
				write(ans3[i]),putchar(i==siz-1?'\n':' ');
		}
	}
	flush();
	return 0;
}