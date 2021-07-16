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

inline void swap(reg int& a,reg int& b){
	reg int tmp=a;
	a=b,b=tmp;
	return;
}

inline bool check(reg int l,reg int r,reg int x){
	return l<=x&&x<=r;
}

const int MAXC=1e5+5;
const int MAXV=12*MAXC+16;
const int MAXE=MAXV*2;
const int MAXSIZE=16+14*MAXC;

struct Node{
	int id,x,y;
	inline Node(void){return;}
	inline Node(const int& id,const int& x,const int& y):id(id),x(x),y(y){return;}
	inline bool operator==(const Node& a)const{return x==a.x&&y==a.y;}
};

inline bool cmp(const Node& a,const Node& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y)||(a.x==b.x&&a.y==b.y&&a.id<b.id);
}

inline bool cmpx(const Node& a,const Node& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

int n,m,c;
int tot;
Node V[MAXSIZE];

inline void getPot(reg int x,reg int y,reg int r){
	for(reg int i=-r;i<=r;++i)
		for(reg int j=-r;j<=r;++j)
			if(check(1,n,x+i)&&check(1,m,y+j))
				V[++tot]=Node(0,x+i,y+j);
	return;
}

int cnt,head[MAXV],to[MAXE],nxt[MAXE];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool flag;
int tim,dfn[MAXV],low[MAXV];
int rt;

inline void tarjan(reg int u){
	dfn[u]=low[u]=++tim;
	reg int cnt=0;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				++cnt;
				if(u!=rt||cnt>1)
					flag=true;
			}
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	return;
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read(),c=read();
		tot=0;
		for(reg int i=1;i<=c;++i){
			static int x,y;
			x=read(),y=read();
			V[++tot]=Node(-1,x,y);
			getPot(x,y,1),getPot(1,y,0),getPot(n,y,0),getPot(x,1,0),getPot(x,m,0);
		}
		getPot(1,1,1),getPot(1,m,1),getPot(n,1,1),getPot(n,m,1);
		sort(V+1,V+tot+1,cmp),tot=unique(V+1,V+tot+1)-(V+1);
		reg int id=0;
		for(reg int i=1;i<=tot;++i)
			if(V[i].id!=-1)
				V[i].id=++id;
		cnt=1,memset(head+1,0,sizeof(int)*id);
		sort(V+1,V+tot+1,cmpx);
		for(reg int i=1;i<tot;++i)
			if(V[i+1].id==-1)
				++i;
			else if(V[i].id==-1)
				continue;
			else if(V[i].x==V[i+1].x){
				Add_Edge(V[i].id,V[i+1].id);
				Add_Edge(V[i+1].id,V[i].id);
			}
		for(reg int i=1;i<=tot;++i)
			swap(V[i].x,V[i].y);
		sort(V+1,V+tot+1,cmpx);
		for(reg int i=1;i<tot;++i)
			if(V[i+1].id==-1)
				++i;
			else if(V[i].id==-1)
				continue;
			else if(V[i].x==V[i+1].x){
				Add_Edge(V[i].id,V[i+1].id);
				Add_Edge(V[i+1].id,V[i].id);
			}
		if(id<=1||(id==2&&head[1]))
			puts("-1");
		else{
			tim=0,memset(dfn+1,0,sizeof(int)*id);
			flag=false;
			tarjan(rt=1);
			if(tim!=id)
				puts("0");
			else if(flag)
				puts("1");
			else
				puts("2");
		}
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}