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

inline int mex(reg int S){
	return __builtin_popcount(S^(S+1))-1;
}

const int mod=1004535809;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

const int MAXN=5e5+5;
const int MAXQ=1e5+5;

int Q;
int fa[MAXQ];
int cnt[MAXN];
int f[MAXN][32];
int g[32],a[MAXN][32];
int k[1<<20];
int leaf[MAXQ];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

namespace Graph{
	int cnt,head[MAXN],to[MAXN],nxt[MAXN];
	inline void init(reg int n){
		cnt=0,memset(head+1,0,sizeof(int)*n);
		return;
	}
	inline void Add_Edge(reg int u,reg int v){
		nxt[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
}

inline bool cmp(reg int a,reg int b){
	return cnt[a]<cnt[b];
}

inline void dfs(reg int u,reg int t){
	cnt[u]=0;
	vector<int> w;
	if(!Graph::head[u]){
		memset(f[u],0,sizeof(int)*32);
		++leaf[t];
		cnt[u]=1;
		f[u][0]=f[u][1]=1;
		return;
	}
	for(reg int i=Graph::head[u];i;i=Graph::nxt[i]){
		int v=Graph::to[i];
		dfs(v,t);
		w.push_back(v);
	}
	sort(w.begin(),w.end(),cmp);
	k[0]=1;
	reg int las=0;
	for(reg int i=0,siz=w.size();i<siz-1;++i){
		reg int v=w[i];
		for(reg int S=(1<<(cnt[las]+1))-1;S>=0;--S){
			reg int tmp=k[S];
			k[S]=0;
			for(reg int j=0;j<=cnt[v];++j)
				k[S|(1<<j)]=add(k[S|(1<<j)],1ll*tmp*f[v][j]%mod);
		}
		las=w[i];
	}
	reg int v=w.back();
	memset(f[u],0,sizeof(int)*32);
	reg int tot=0;
	for(reg int i=0;i<=cnt[v];++i)
		tot=add(tot,f[v][i]);
	for(reg int S=0;S<(1<<(cnt[las]+1));++S){
		reg int a=mex(S),b=mex(S|(1<<a));
		f[u][a]=add(f[u][a],1ll*sub(tot,f[v][a])*k[S]%mod);
		f[u][b]=add(f[u][b],1ll*f[v][a]*k[S]%mod);
		k[S]=0;
	}
	while(f[u][cnt[u]+1]) ++cnt[u];
	return;
}

bool ed;

int main(void){
	Q=read();
	g[0]=1;
	reg int cnt=0;
	for(reg int t=1;t<=Q;++t){
		static int c,op;
		c=read(),op=read();
		switch(op){
			case 1:{
				fa[t]=find(read());
				break;
			}
			case 2:{
				fa[t]=t;
				reg int n=read();
				Graph::init(n);
				for(reg int i=2;i<=n;++i)
					Graph::Add_Edge(read(),i);
				dfs(1,t);
				for(reg int i=0;i<32;++i)
					a[t][i]=f[1][i];
				break;
			}
		}
		if(c&1){
			static int tmp[32];
			memset(tmp,0,sizeof(int)*32);
			for(reg int i=0;i<32;++i)
				for(reg int j=0;j<32;++j)
					tmp[i^j]=add(tmp[i^j],1ll*a[fa[t]][i]*g[j]%mod);
			for(reg int i=0;i<32;++i)
				g[i]=tmp[i];
		}
		else
			cnt+=leaf[fa[t]];
		reg int ans=0;
		for(reg int i=1;i<32;++i)
			ans=add(ans,g[i]);
		writeln(1ll*ans*fpow(2,cnt)%mod);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}