#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;

int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int n,m,d;
int v[MAXN];

int fa[MAXN],dep[MAXN];
int son[MAXN],size[MAXN];

inline void DFS1(reg int ID,reg int father){
	size[ID]=1;
	fa[ID]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			size[ID]+=size[to[i]];
			if(size[son[ID]]<size[to[i]])
				son[ID]=to[i];
		}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];
int top[MAXN];

inline void DFS2(reg int ID,reg int father,reg int topf){
	top[ID]=topf;
	dfn[ID]=++tim;
	rnk[tim]=ID;
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,cMax;
		inline Node(reg int Max=0,reg int cMax=0):Max(Max),cMax(cMax){
			return;
		}
		inline Node operator+(const Node& a){
			reg int _Max=max(Max,a.Max);
			reg int _cMax=max(Max==_Max?cMax:Max,a.Max==_Max?a.cMax:a.Max);
			return Node(_Max,_cMax);
		}
		#define Max(x) unit[(x)].Max
		#define cMax(x) unit[(x)].cMax
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		cMax(k)=max(cMax(lson),cMax(rson));
		if(Max(lson)<Max(rson))
			cMax(k)=max(cMax(k),Max(lson));
		if(Max(lson)>Max(rson))
			cMax(k)=max(cMax(k),Max(rson));
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			Max(k)=v[rnk[l]];
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Max(k)+=val;
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,val);
		if(pos>mid)
			Update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return Query(lson,l,mid,L,R)+Query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return Query(lson,l,mid,L,R);
		else
			return Query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;
multiset<int> S;

inline void Query(int x,int y){
	Node res;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res=res+Query(1,1,n,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res=res+Query(1,1,n,dfn[x],dfn[y]);
	if(!res.cMax)
		puts("-1");
	else{
		S.erase(S.find(res.cMax)),S.erase(S.find(res.Max));
		int ans2=*(--S.lower_bound(*--S.end()));
		S.insert(res.cMax),S.insert(res.Max);
		printf("%d %d\n",res.cMax,ans2);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	for(reg int i=1;i<=n;++i){
		v[i]=read();
		S.insert(v[i]);
	}
	DFS1(1,0);
	DFS2(1,0,1);
	Build(1,1,n);
	reg int q=read();
	while(q--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 0:{
				Update(1,1,n,dfn[x],y);
				S.erase(S.find(v[x]));
				S.insert(v[x]+=y);
				break;
			}
			case 1:{
				Query(x,y);
				break;
			}
			default:break;
		}
	}
	return 0;
}