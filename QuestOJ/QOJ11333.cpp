#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;
const int MAXQ=3e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l)+(r) ) >> 1 )
	struct Node{
		int Max,tAdd;
		#define Max(x) unit[(x)].Max
		#define tAdd(x) unit[(x)].tAdd
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			Max(k)=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Add(reg int k,reg int val){
		Max(k)+=val,tAdd(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tAdd(k)){
			Add(lson,tAdd(k));
			Add(rson,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int lef,reg int rig,reg int val){
		if(lef<=l&&r<=rig){
			Add(k,val);
			return;
		}
		pushdown(k);
		if(lef<=mid)
			update(lson,l,mid,lef,rig,val);
		if(rig>mid)
			update(rson,mid+1,r,lef,rig,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int lef,reg int rig){
		if(lef<=l&&r<=rig)
			return Max(k);
		pushdown(k);
		if(lef<=mid&&mid<rig)
			return max(query(lson,l,mid,lef,rig),query(rson,mid+1,r,lef,rig));
		else if(lef<=mid)
			return query(lson,l,mid,lef,rig);
		else
			return query(rson,mid+1,r,lef,rig);
	}
}

struct querys{
	int opt,x,y;
};

int n,q;
int a[MAXN];
querys Q[MAXQ];
int fa[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

int pre[MAXN],suf[MAXN];
int head[MAXN],tail[MAXN];

inline void link(reg int a,reg int b){
	reg int ra=find(a),rb=find(b);
	if(ra!=rb){
		fa[rb]=ra;
		reg int u=tail[ra],v=head[rb];
		tail[ra]=tail[rb];
		pre[u]=v,suf[v]=u;
	}
	return;
}

int lef[MAXN],rig[MAXN];

inline void merge(reg int a,reg int b){
	reg int ra=find(a),rb=find(b);
	if(ra!=rb){
		fa[rb]=ra;
		if(lef[ra]<lef[rb])
			rig[ra]=rig[rb];
		else
			lef[ra]=lef[rb];
	}
	return;
}

int tim,dfn[MAXN],rnk[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read(),
		fa[i]=head[i]=tail[i]=i;
	}
	q=read();
	for(reg int i=1;i<=q;++i){
		static char opt;
		static int id;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'U':{
				Q[i].opt=1,Q[i].x=read(),Q[i].y=read();
				link(Q[i].x,Q[i].y);
				break;
			}
			case 'A':{
				id=getchar()-'0';
				Q[i].opt=id+1,Q[i].x=read();
				if(id<3)
					Q[i].y=read();
				break;
			}
			case 'F':{
				id=getchar()-'0';
				Q[i].opt=id+4;
				if(id<3)
					Q[i].x=read();
				break;
			}
		}
	}
	for(reg int i=1;i<=n;++i)
		if(!pre[i])
			for(reg int j=i;j;j=suf[j]){
				dfn[j]=++tim;
				rnk[tim]=j;
			}
	for(reg int i=1;i<=n;++i)
		fa[i]=i,lef[i]=rig[i]=dfn[i];
	static int val[MAXN];
	for(reg int i=1;i<=n;++i)
		val[dfn[i]]=a[i];
	SegmentTree::build(1,1,n,val);
	for(reg int i=1;i<=q;++i)
		switch(Q[i].opt){
			case 1:{
				merge(Q[i].x,Q[i].y);
				break;
			}
			case 2:{
				SegmentTree::update(1,1,n,dfn[Q[i].x],dfn[Q[i].x],Q[i].y);
				break;
			}
			case 3:{
				reg int id=find(Q[i].x);
				SegmentTree::update(1,1,n,lef[id],rig[id],Q[i].y);
				break;
			}
			case 4:{
				SegmentTree::update(1,1,n,1,n,Q[i].x);
				break;
			}
			case 5:{
				writeln(SegmentTree::query(1,1,n,dfn[Q[i].x],dfn[Q[i].x]));
				break;
			}
			case 6:{
				reg int id=find(Q[i].x);
				writeln(SegmentTree::query(1,1,n,lef[id],rig[id]));
				break;
			}
			case 7:{
				writeln(SegmentTree::query(1,1,n,1,n));
				break;
			}
		}
	flush();
	return 0;
}