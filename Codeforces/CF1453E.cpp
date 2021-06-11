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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int inf=0x3f3f3f3f;

int n;
vector<int> G[MAXN];
int f[MAXN];
int ans;

inline void dfs(reg int u,reg int father){
	reg int cnt=0,Max=0,cMax=0;
	f[u]=inf;
	for(int v:G[u])
		if(v!=father){
			++cnt;
			dfs(v,u);
			f[u]=min(f[u],f[v]+1);
			if(f[v]+1>Max)
				cMax=Max,Max=f[v]+1;
			else if(f[v]+1>cMax)
				cMax=f[v]+1;
		}
	if(!cnt)
		f[u]=0;
	else if(u==1)
		if(cnt==1)
			ans=max(ans,Max);
		else
			ans=max(ans,max(cMax+1,Max));
	else
		ans=max(ans,Max+1);
	return;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			G[i].clear();
		for(reg int i=1;i<n;++i){
			static int u,v;
			u=read(),v=read();
			G[u].push_back(v),G[v].push_back(u);
		}
		ans=0;
		dfs(1,0);
		writeln(ans);
	}
	flush();
	return 0;
}