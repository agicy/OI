#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=150000+5;

int n,m,W,H;

struct Point{
	int id,x,y;
	inline void Read(reg int i){
		id=i;
		x=read(),y=read();
	}
	inline bool operator<(const Point& a)const{
		return y==a.y?id<a.id:y<a.y;
	}
	inline Point(reg int id=0,reg int x=0,reg int y=0):id(id),x(x),y(y){
		return;
	}
};

Point s[MAXN];
set<Point> S[MAXN<<1];

#define lson ( (k) << 1 )
#define rson ( (k) << 1 | 1 )
#define mid ( ( (l) + (r) ) >> 1 )

inline void Update(reg int k,reg int l,reg int r,reg int v){
	S[k].insert(s[v]);
	if(l==r)
		return;
	if(s[v].x<=mid)
		Update(lson,l,mid,v);
	else
		Update(rson,mid+1,r,v);
	return;
}

inline void deleet(reg int k,reg int l,reg int r,reg int v){
	S[k].erase(s[v]);
	if(l==r)
		return;
	if(s[v].x<=mid)
		deleet(lson,l,mid,v);
	else
		deleet(rson,mid+1,r,v);
	return;
}

struct Jump{
	int p,t,l,r,d,u;
	inline void Read(void){
		p=read(),t=read(),l=read(),r=read(),d=read(),u=read();
		return;
	}
};

Jump E[MAXN];
vector<int> G[MAXN];

struct Node{
	int ID,dis;
	inline Node(reg int ID=0,reg int dis=0):ID(ID),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

priority_queue<Node,vector<Node>,greater<Node>/**/> Q;


int dis[MAXN];

inline void Relax(reg int k,reg int l,reg int r,reg int id,reg int v){
	reg int L=E[id].l,R=E[id].r;
	if(r<L||l>R)
		return;
	if(L<=l&&r<=R){
		queue<int> tag;
		for(set<Point>::iterator it=lower_bound(S[k].begin(),S[k].end(),Point(0,n+1,E[id].d));it!=S[k].end()&&(it->y)<=E[id].u;++it){
			int to=(it->id);
			dis[to]=v;
			tag.push(to);
			for(reg int i=0,size=G[to].size();i<size;++i)
				Q.push(Node(G[to][i],v+E[G[to][i]].t));
		}
		while(!tag.empty()){
			deleet(1,1,n,tag.front());
			tag.pop();
		}
		return;
	}
	Relax(lson,l,mid,id,v);
	Relax(rson,mid+1,r,id,v);
	return;
}

bool vis[MAXN];

int main(void){
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	n=read(),m=read(),W=read(),H=read();
	for(reg int i=1;i<=n;++i){
		s[i].Read(i);
		Update(1,1,n,i);
	}
	for(int i=1;i<=m;++i){
		E[i].Read();
		G[E[i].p].push_back(i);
	}
	E[0].l=E[0].r=s[1].x;
	E[0].d=E[0].u=s[1].y;
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	dis[0]=0;
	Q.push(Node(0,0));
	while(!Q.empty()){
		static Node x;
		x=Q.top();
		Q.pop();
		reg int ID=x.ID,val=x.dis;
		if(vis[ID])
			continue;
		vis[ID]=true;
		Relax(1,1,n,ID,val);
	}
	for(reg int i=2;i<=n;++i)
		printf("%d\n",dis[i]);
	return 0;
}
