#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e4+5;
const int MAXV=2e6+5;

int n,m;
int a[MAXN];
int cnt,T[MAXN];
int V;

inline int getA(reg int i){
	return (i<<1)-1;
}

inline int getB(reg int i){
	return i<<1;
}

vector<int> G[MAXN<<1],tmp[MAXV];

inline void Add_Edge_G(reg int u,int v){
	G[u].push_back(v);
	return;
}

inline void Add_Edge(reg int u,int v){
	tmp[u].push_back(v);
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

int unit1[MAXN][2],unit2[MAXN][2];

inline void updateA(reg int x,reg int val){
	for(reg int i=x;i<=cnt;i+=lowbit(i)){
		++V;
		if(unit1[i][0])
			Add_Edge(V,unit1[i][0]),Add_Edge(V+1,unit1[i][0]+1);
		unit1[i][0]=V;
		Add_Edge(V,val),Add_Edge(V+1,val+1);
		V+=2;
		if(unit2[i][0])
			Add_Edge(unit2[i][0],V),Add_Edge(unit2[i][0]+1,V+1);
		unit2[i][0]=V;
		Add_Edge(val,V),Add_Edge(val+1,V+1);
		++V;
	}
	return;
}

inline void updateB(reg int x,reg int val){
	for(reg int i=x;i<=cnt;i+=lowbit(i)){
		++V;
		if(unit1[i][1])
			Add_Edge(V,unit1[i][1]),Add_Edge(V+1,unit1[i][1]+1);
		unit1[i][1]=V;
		Add_Edge(V,val),Add_Edge(V+1,val+1);
		V+=2;
		if(unit2[i][1])
			Add_Edge(unit2[i][1],V),Add_Edge(unit2[i][1]+1,V+1);
		unit2[i][1]=V;
		Add_Edge(val,V),Add_Edge(val+1,V+1);
		++V;
	}
	return;
}

inline void queryA(reg int x,reg int val){
	for(reg int i=x;i;i^=lowbit(i)){
		if(unit1[i][0])
			Add_Edge(val,unit1[i][0]+1);
		if(unit2[i][0])
			Add_Edge(unit2[i][0],val+1);
	}
	return;
}

inline void queryB(reg int x,reg int val){
	for(reg int i=x;i;i^=lowbit(i)){
		if(unit1[i][1])
			Add_Edge(val+1,unit1[i][1]);
		if(unit2[i][1])
			Add_Edge(unit2[i][1]+1,val);
	}
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
	for(int v:tmp[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(u<=(n<<1))
		for(int v:G[u]){
			if(!dfn[v]){
				tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(vis[v])
				low[u]=min(low[u],dfn[v]);
		}
	if(dfn[u]==low[u]){
		++scc_cnt;
		reg int v;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=scc_cnt;
		}while(u!=v);
	}
	return;
}

inline bool check(reg int mid){
	memset(unit1,0,sizeof(unit1)),memset(unit2,0,sizeof(unit2));
	V=2*n;
	for(reg int i=1;i<=n;++i){
		reg int p;
		p=upper_bound(T+1,T+cnt+1,a[i]-mid)-T-1;
		if(p>=1)
			queryA(p,getA(i));
		p=lower_bound(T+1,T+cnt+2,a[i]+mid)-T;
		if(p<=cnt)
			queryB(cnt-p+1,getA(i));
		p=lower_bound(T+1,T+cnt+1,a[i])-T;
		updateA(p,getA(i)),updateB(cnt-p+1,getA(i));
	}
	tim=0,memset(dfn,0,sizeof(dfn));
	scc_cnt=0;
	reg bool res=true;
	for(reg int i=1;i<=n;++i){
		if(!dfn[getA(i)])
			tarjan(getA(i));
		if(!dfn[getB(i)])
			tarjan(getB(i));
		if(col[getA(i)]==col[getB(i)])
			res=false;
	}
	for(reg int i=1;i<=V;++i)
		tmp[i].clear();
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		T[++cnt]=a[i];
	}
	sort(T+1,T+cnt+1);
	cnt=unique(T+1,T+cnt+1)-T-1;
	T[cnt+1]=T[cnt]+1;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge_G(getA(u),getB(v)),Add_Edge_G(getB(u),getA(v)),Add_Edge_G(getB(v),getA(u)),Add_Edge_G(getA(v),getB(u));
	}
	for(reg int i=1;i<=n;++i){
		if(!dfn[getA(i)])
			tarjan(getA(i));
		if(!dfn[getB(i)])
			tarjan(getB(i));
		if(col[getA(i)]==col[getB(i)])
			puts("-1"),exit(0);
	}
	reg int l=0,r=1e9,mid;
	while(l<r){
		mid=(0ll+l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}