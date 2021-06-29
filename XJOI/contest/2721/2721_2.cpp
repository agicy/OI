#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=200+5;

int n,A[3];
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int val[MAXN];
int siz[MAXN][3];
int f[MAXN][MAXN/2+1][MAXN/4+1][MAXN/6+1];
int ans;

inline void dfs(reg int u,reg int father){
	f[u][0][0][0]=1;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			static int tmp[MAXN/2+1][MAXN/4+1][MAXN/6+1];
			for(reg int a=0;a<=siz[u][0];++a)
				for(reg int b=0;b<=siz[u][1];++b)
					for(reg int c=0;c<=siz[u][2];++c)
						tmp[a][b][c]=f[u][a][b][c],f[u][a][b][c]=0;
			for(reg int a0=0;a0<=siz[u][0];++a0)
				for(reg int a1=0;a1<=siz[v][0]&&a0+a1<=A[0];++a1)
			for(reg int b0=0;b0<=siz[u][1];++b0)
				for(reg int b1=0;b1<=siz[v][1]&&b0+b1<=A[1];++b1)
			for(reg int c0=0;c0<=siz[u][2];++c0)
				for(reg int c1=0;c1<=siz[v][2]&&c0+c1<=A[2];++c1)
					f[u][a0+a1][b0+b1][c0+c1]=add(f[u][a0+a1][b0+b1][c0+c1],1ll*tmp[a0][b0][c0]*f[v][a1][b1][c1]%mod);
			siz[u][0]+=siz[v][0];
			if(siz[u][0]>A[0]) siz[u][0]=A[0];
			siz[u][1]+=siz[v][1];
			if(siz[u][1]>A[1]) siz[u][1]=A[1];
			siz[u][2]+=siz[v][2];
			if(siz[u][2]>A[2]) siz[u][2]=A[2];
		}
	}
	static int tmp[MAXN/2+1][MAXN/4+1][MAXN/6+1];
	for(reg int a=0;a<=siz[u][0];++a)
		for(reg int b=0;b<=siz[u][1];++b)
			for(reg int c=0;c<=siz[u][2];++c)
				tmp[a][b][c]=f[u][a][b][c],f[u][a][b][c]=0;
	for(reg int a=0;a<=siz[u][0];++a)
		for(reg int b=0;b<=siz[u][1];++b)
			for(reg int c=0;c<=siz[u][2];++c)
				f[u][a+(val[u]==0)][b+(val[u]==1)][c+(val[u]==2)]=add(f[u][a+(val[u]==0)][b+(val[u]==1)][c+(val[u]==2)],tmp[a][b][c]);
	siz[u][val[u]]+=1;
	if(siz[u][val[u]]>A[val[u]]) siz[u][val[u]]=A[val[u]];
	for(reg int a=0;a<=siz[u][0];++a)
		for(reg int b=0;b<=siz[u][1];++b)
			for(reg int c=0;c<=siz[u][2];++c)
				if(a|b|c)
					ans=add(ans,f[u][a][b][c]);
	f[u][0][0][0]=1;
	return;
}

inline bool cmp(reg int a,reg int b){
	return A[a]>A[b];
}

bool ed;

int main(void){
	n=read(),A[0]=read(),A[1]=read(),A[2]=read();
	int id[3]={0,1,2};
	sort(id,id+3,cmp);
	int inv[3];
	for(reg int i=0;i<3;++i)
		inv[id[i]]=i;
	sort(A,A+3),reverse(A,A+3);
	for(reg int i=1;i<=n;++i)
		val[i]=inv[read()];
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(1,0);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}