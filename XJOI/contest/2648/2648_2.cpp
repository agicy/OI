#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXT=1e5+5;

struct operation{
	char opt;
	int x,y;
};

int n,t;
int a[MAXN];
operation op[MAXT];
int fa[MAXN];
vector<int> G[MAXN];

inline void dfs(reg int u,reg int rt){
	a[u]=a[rt];
	for(int v:G[u])
		dfs(v,rt);
	return;
}

bool important[MAXN];
int col[MAXN];
vector<int> son[MAXN];

inline void getSon(int u,reg int rt){
	col[u]=rt;
	son[rt].push_back(u);
	for(int v:G[u])
		if(!important[v])
			getSon(v,rt);
	return;
}

int ptr[MAXN];

inline int find(reg int x){
	while(x!=ptr[x]) x=ptr[x];
	return x;
}

inline void solve(reg int l,reg int r){
	vector<int> V;
	for(reg int i=l;i<=r;++i)
		if(op[i].opt=='L')
			V.push_back(op[i].x),V.push_back(op[i].y);
		else if(op[i].opt=='C')
			V.push_back(op[i].x);
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(int u:V)
		important[u]=true;
	fill(col+1,col+n+1,0);
	for(int u:V){
		son[u].clear();
		getSon(u,u);
		sort(son[u].begin(),son[u].end());
	}
	for(int u:V)
		if(fa[u]!=u&&col[fa[u]])
			ptr[u]=col[fa[u]];
		else
			ptr[u]=u;
	static ll sum[MAXN];
	for(reg int i=1;i<=n;++i)
		if(!col[i])
			sum[i]=sum[i-1]+a[i];
		else
			sum[i]=sum[i-1];
	static int val[MAXN];
	for(int u:V)
		val[u]=a[u];
	for(reg int i=l;i<=r;++i){
		for(int u:V)
			val[u]=val[find(u)];
		switch(op[i].opt){
			case 'L':{
				ptr[op[i].x]=op[i].y;
				break;
			}
			case 'C':{
				ptr[op[i].x]=op[i].x;
				val[op[i].x]=op[i].y;
				break;
			}
			case 'Q':{
				reg ll res=sum[op[i].y]-sum[op[i].x-1];
				for(int u:V){
					if(son[u].empty()||son[u].back()<op[i].x||son[u].front()>op[i].y)
						continue;
					reg int lef,rig;
					reg int __l,__r,__mid;
					__l=0,__r=son[u].size()-1;
					while(__l<__r){
						__mid=(__l+__r)>>1;
						if(op[i].x<=son[u][__mid])
							__r=__mid;
						else
							__l=__mid+1;
					}
					lef=__l;
					__l=0,__r=son[u].size()-1;
					while(__l<__r){
						__mid=(__l+__r)>>1;
						if(son[u][__mid+1]<=op[i].y)
							__l=__mid+1;
						else
							__r=__mid;
					}
					rig=__l;
					res+=1ll*val[u]*(rig-lef+1);
				}
				writeln(res);
				break;
			}
		}
	}
	for(int u:V)
		important[u]=false;
	for(reg int i=l;i<=r;++i)
		switch(op[i].opt){
			case 'L':{
				fa[op[i].x]=op[i].y;
				break;
			}
			case 'C':{
				fa[op[i].x]=op[i].x;
				a[op[i].x]=op[i].y;
				break;
			}
			case 'Q':break;
		}
	for(reg int i=1;i<=n;++i)
		G[i].clear();
	for(int i=1;i<=n;++i)
		if(fa[i]!=i)
			G[fa[i]].push_back(i);
	for(reg int i=1;i<=n;++i)
		if(fa[i]==i)
			dfs(i,i);
	return;
}

bool ed;

int main(void){
	n=read(),t=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),fa[i]=i;
	reg int B=300,tot=(t+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		reg int len=min(i*B,t)-((i-1)*B+1)+1;
		for(reg int j=1;j<=len;++j){
			do
				op[j].opt=getchar();
			while(!isalpha(op[j].opt));
			op[j].x=read(),op[j].y=read();
		}
		solve(1,len);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}