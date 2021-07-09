#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

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

const int MAXN=1e5+5;

int n;
int __cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++__cnt]=head[u];
	to[__cnt]=v;
	head[u]=__cnt;
	return;
}

int id[MAXN];
ull val[MAXN<<1];
int tot;
map<ull,int> M;

inline int getId(ull val){
	map<ull,int>::iterator it=M.find(val);
	if(it!=M.end())
		return it->second;
	else
		return M[val]=++tot;
}

int cnt,T[MAXN<<1];

inline void add(reg int x){
	if(!T[x])
		++cnt;
	++T[x];
	return;
}

inline void del(reg int x){
	--T[x];
	if(!T[x])
		--cnt;
	return;
}

inline void dfs1(reg int u,reg int father){
	reg ull sum=0;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			sum+=val[id[v]];
		}
	}
	id[u]=getId(sum);
	add(id[u]);
	return;
}

int Max=-1,ans;

inline void dfs2(reg int u,reg int father,reg int c){
	del(id[u]);
	if(cnt>Max)
		Max=cnt,ans=u;
	reg ull sum=0;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father)
			sum+=val[id[v]];
	}
	sum+=val[c];
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			reg ull tmp=sum-val[id[v]];
			add(getId(tmp));
			dfs2(v,u,getId(tmp));
			del(getId(tmp));
		}
	}
	add(id[u]);
	return;
}

bool ed;

int main(void){
	n=read();
	mt19937_64 rng(time(0));
	for(reg int i=1;i<=(n<<1);++i)
		val[i]=rng();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	dfs1(1,0);
	dfs2(1,0,0);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}