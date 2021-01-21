#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int mod=(1<<30)-1;

int n,q;
int tot,rt[MAXN];

namespace SegmentTree{
	const int MAXSIZE=MAXN*30;
	struct Node{
		int lson,rson;
		int cntl,cntr;
		ll suml,sumr;
		#define lson(p) unit[p].lson
		#define rson(p) unit[p].rson
		#define cntl(p) unit[p].cntl
		#define cntr(p) unit[p].cntr
		#define suml(p) unit[p].suml
		#define sumr(p) unit[p].sumr
	};
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int id){
		reg int p=++tot;
		unit[p]=unit[pre];
		cntl(p)+=cntl(id),cntr(p)+=cntr(id);
		suml(p)+=suml(id),sumr(p)+=sumr(id);
		if(cntl(id)>0)
			lson(p)=update(lson(p),lson(id));
		if(cntr(id)>0)
			rson(p)=update(rson(p),rson(id));
		return p;
	}
	inline ll query(reg int id,reg int p1,reg int p2){
		if(cntl(id)>0)
			return query(lson(id),lson(p1),lson(p2))+sumr(p2)-sumr(p1)+(cntr(p2)-cntr(p1))*suml(id);
		if(cntr(id)>0)
			return query(rson(id),rson(p1),rson(p2))+suml(p2)-suml(p1)+(cntl(p2)-cntl(p1))*sumr(id);
		return 0;
	}
}

namespace CTree{
	using namespace SegmentTree;
	int cnt=1,head[MAXN<<1],to[MAXN<<2],w[MAXN<<2],Next[MAXN<<2];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,len);
		return;
	}
	bool vis[MAXN];
	int siz[MAXN],las[MAXN];
	int S,Min,cut;
	inline void find(reg int u,reg int father){
		siz[u]=1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[i]&&v!=father){
				find(v,u);
				siz[u]+=siz[v];
				reg int Max=max(siz[v],S-siz[v]);
				if(Max<Min)
					Min=Max,cut=i;
			}
		}
		return;
	}
	inline void dfs(reg int u,reg int father,reg ll dis,reg bool tag){
		if(u<=n){
			++tot;
			if(!rt[u])
				rt[u]=tot;
			if(lson(las[u])==-1)
				lson(las[u])=tot;
			else
				rson(las[u])=tot;
			if(!tag)
				lson(tot)=-1,++cntl(tot),suml(tot)=dis;
			else
				rson(tot)=-1,++cntr(tot),sumr(tot)=dis;
			las[u]=tot;
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[i]&&v!=father)
				dfs(v,u,dis+w[i],tag);
		}
		return;
	}
	inline void conquer(reg int u,reg int tot){
		if(tot<=1)
			return;
		S=Min=tot;
		find(u,0);
		vis[cut]=vis[cut^1]=true;
		reg int l=to[cut],r=to[cut^1];
		dfs(l,0,0,false),dfs(r,0,w[cut],true);
		conquer(r,tot-siz[l]),conquer(l,siz[l]);
		return;
	}
}

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int las[MAXN];
	int tot;
	inline void dfs(reg int u,reg int father){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dfs(v,u);
				if(!las[u]){
					las[u]=u;
					CTree::Add_Tube(las[u],v,w[i]);
				}
				else{
					CTree::Add_Tube(las[u],++tot,0);
					las[u]=tot;
					CTree::Add_Tube(las[u],v,w[i]);
				}
			}
		}
		return;
	}
}

int p[MAXN];
ll T[MAXN];

int main(void){
	n=read(),q=read();
	Tree::tot=n;
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	for(reg int i=1;i<n;++i){
		static int x,y,z;
		x=read(),y=read(),z=read();
		Tree::Add_Edge(x,y,z);
		Tree::Add_Edge(y,x,z);
	}
	Tree::dfs(1,0);
	CTree::conquer(1,Tree::tot);
	SegmentTree::unit[0]=SegmentTree::unit[tot+10];
	for(reg int i=1;i<=tot;++i)
		SegmentTree::lson(i)=max(SegmentTree::lson(i),0),SegmentTree::rson(i)=max(SegmentTree::rson(i),0);
	for(reg int i=1;i<=n;++i)
		T[i]=SegmentTree::update(T[i-1],rt[p[i]]);
	reg ll lastans=0;
	while(q--){
		static int t,l,r,x;
		t=read();
		switch(t){
			case 1:{
				l=read()^lastans,r=read()^lastans,x=read()^lastans;
				lastans=SegmentTree::query(rt[x],T[l-1],T[r]);
				printf("%lld\n",lastans);
				lastans&=mod;
				break;
			}
			case 2:{
				x=read()^lastans;
				swap(p[x],p[x+1]);
				T[x]=SegmentTree::update(T[x-1],rt[p[x]]);
				break;
			}
		}
	}
	return 0;
}