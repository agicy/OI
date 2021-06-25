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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e4+5;
const int MAXK=150+5;
const int mod=1e4+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,k;
int fac[MAXK];
int strling[MAXK][MAXK];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int f[MAXN][MAXK];

inline void dfs1(reg int u,reg int father){
	f[u][0]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			for(reg int j=1;j<=k;++j)
				f[u][j]=add(f[u][j],add(f[v][j],f[v][j-1]));
			f[u][0]=add(f[u][0],f[v][0]);
		}
	}
	return;
}

int g[MAXN][MAXK];

inline void dfs2(reg int u,reg int father){
	for(reg int i=0;i<=k;++i)
		g[u][i]=f[u][i];
	if(father){
		static int tmp[MAXK];
		for(reg int i=1;i<=k;++i)
			tmp[i]=sub(g[father][i],add(f[u][i],f[u][i-1]));
		tmp[0]=sub(g[father][0],f[u][0]);
		for(reg int i=1;i<=k;++i)
			g[u][i]=add(g[u][i],add(tmp[i],tmp[i-1]));
		g[u][0]=add(g[u][0],tmp[0]);
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs2(v,u);
	}
	return;
}

int main(void){
	n=read(),k=read();
	fac[0]=1;
	for(reg int i=1;i<=k;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	strling[0][0]=1;
	for(reg int i=1;i<=k;++i)
		for(reg int j=1;j<=i;++j)
			strling[i][j]=add(strling[i-1][j-1],1ll*j*strling[i-1][j]%mod);
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs1(1,0),dfs2(1,0);
	for(reg int i=1;i<=n;++i){
		reg int ans=0;
		for(reg int j=0;j<=k;++j)
			ans=add(ans,1ll*fac[j]*strling[k][j]%mod*g[i][j]%mod);
		writeln(ans);
	}
	flush();
	return 0;
}