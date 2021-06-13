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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
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

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

struct Node{
	ll b;
	int k;
	int id;
	int l,r;
	inline bool operator<(const Node& a)const{
		if(k!=a.k)
			return k<a.k;
		else if(b!=a.b)
			return b>a.b;
		else
			return id>a.id;
	}
	inline ll getVal(reg int t)const{
		return 1ll*k*t+b;
	}
};

int n,m;
Node a[MAXN];
vector<int> G[MAXN];

int fa[MAXN][MAXLOG2N];
int dep[MAXN];

inline void dfs(reg int u,reg int father){
	fa[u][0]=father;
	dep[u]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:G[u])
		if(v!=father)
			dfs(v,u);
	return;
}

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline bool getTag(const Node& a,const Node& b){
	reg int x=a.l;
	reg ll va=a.getVal(x),vb=b.getVal(x);
	if(va!=vb)
		return vb>va;
	else
		return b.id>a.id;
}

inline int getDis(reg int lca,reg int x,reg int y){
	return dep[x]+dep[y]-(dep[lca]<<1);
}

inline int getFa(reg int u,reg int k){
	reg int ptr=u;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if((k>>i)&1)
			ptr=fa[ptr][i];
	return ptr;
}

inline int getPoint(reg int st,reg int ed,reg int len){
	reg int lca=LCA(st,ed),dis=getDis(lca,st,ed);
	if(dis<=len)
		return ed;
	else if(len<=getDis(lca,st,lca))
		return getFa(st,len);
	else
		return getFa(ed,dis-len);
}

struct Segment{
	int v,l,r,las;
};

Node S[MAXN];
Segment Inv[MAXN];

const int T=1e9;

bool ed;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i].b=readll();
	for(reg int i=1;i<=n;++i)
		a[i].k=read(),a[i].id=i;
	for(reg int i=1;i<n;++i){
		static int s,t;
		s=read()+1,t=read()+1;
		G[s].push_back(t),G[t].push_back(s);
	}
	dfs(1,0);
	sort(a+1,a+n+1);
	reg int top=0;
	a[1].l=0,a[1].r=T;
	S[++top]=a[1];
	for(reg int i=2;i<=n;++i){
		if(a[i].k==a[i-1].k)
			continue;
		while(top&&getTag(S[top],a[i]))
			--top;
		if(top){
			reg ll va=S[top].getVal(S[top].r),vb=a[i].getVal(S[top].r);
			if(vb>va||(va==vb&&a[i].id>S[top].id)){
				reg int __l=S[top].l+1,__r=S[top].r,__mid;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					reg ll va=S[top].getVal(__mid),vb=a[i].getVal(__mid);
					if(vb>va||(va==vb&&a[i].id>S[top].id))
						__r=__mid;
					else
						__l=__mid+1;
				}
				S[top].r=__l-1;
				a[i].l=__l,a[i].r=T;
				if(a[i].l<=a[i].r)
					S[++top]=a[i];
			}
			else{
				a[i].l=S[top].r+1;
				a[i].r=T;
				if(a[i].l<=a[i].r)
					S[++top]=a[i];
			}
		}
		else{
			a[i].l=0,a[i].r=T;
			if(a[i].l<=a[i].r)
				S[++top]=a[i];
		}
	}
	Inv[0].l=Inv[0].r=-1,Inv[0].las=1;
	reg int tot=top;
	for(reg int i=1;i<=tot;++i){
		Inv[i].v=S[i].id;
		Inv[i].l=S[i].l;
		Inv[i].r=S[i].r;
		Inv[i].las=getPoint(Inv[i-1].las,Inv[i].v,Inv[i].r-Inv[i].l+1);
	}
	while(m--){
		static int t;
		t=read();
		reg int __l=0,__r=tot,__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(Inv[__mid+1].r<t)
				__l=__mid+1;
			else
				__r=__mid;
		}
		writeln(getPoint(Inv[__l].las,Inv[__l+1].v,t-Inv[__l+1].l)-1);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}