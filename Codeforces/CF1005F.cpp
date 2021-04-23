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
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;

int n,m,k;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int dis[MAXN];
int Q[MAXN];
ll ans=1;
vector<int> res[MAXN];

inline void bfs(reg int s){
	fill(dis+1,dis+n+1,-1);
	reg int _head=0,_tail=0;
	dis[s]=0,res[s].push_back(0),Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		if(ans<=k)
			ans*=res[u].size();
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]==-1){
				dis[v]=dis[u]+1;
				res[v].push_back(w[i]);
				Q[_tail++]=v;
			}
			else if(dis[v]==dis[u]+1)
				res[v].push_back(w[i]);
		}
	}
	return;
}

bool tag[MAXM];

inline void dfs(reg int u){
	if(u==n+1){
		if(k){
			--k;
			for(reg int i=1;i<=m;++i)
				putchar(tag[i]|'0');
			putchar('\n');
		}
		return;
	}
	for(reg int i=0,siz=res[u].size();i<siz;++i){
		tag[res[u][i]]=true;
		dfs(u+1);
		tag[res[u][i]]=false;
		if(!k)
			return;
	}
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b,i),Add_Edge(b,a,i);
	}
	bfs(1);
	if(ans<k)
		k=ans;
	writeln(k);
	dfs(1);
	flush();
	return 0;
}