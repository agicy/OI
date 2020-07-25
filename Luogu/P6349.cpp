#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e4+5;
const int MAXM=2e5+5;

int n,m;
int ans[MAXM];

struct Point{
	int l,r;
};

Point p[MAXN];

namespace kD_Tree{
	struct Node{
		int lson,rson;
		int id,x[2];
		int Max[2],Min[2];
		int add;
		bool cov;
		int tag,his;
		int cnt;
		int Ans;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define id(x) unit[(x)].id
		#define add(x) unit[(x)].add
		#define cov(x) unit[(x)].cov
		#define tag(x) unit[(x)].tag
		#define his(x) unit[(x)].his
		#define cnt(x) unit[(x)].cnt
		#define Ans(x) unit[(x)].Ans
	};
	int root,tot;
	Node unit[MAXM];
	Node dat[MAXM];
	int WD;
	inline bool cmp(const Node& a,const Node& b){
		return a.x[WD]<b.x[WD];
	}
	inline void pushup(reg int k){
		reg int ls=lson(k),rs=rson(k);
		Max(k)[0]=Min(k)[0]=unit[k].x[0];
		Max(k)[1]=Min(k)[1]=unit[k].x[1];
		if(ls){
			Max(k)[0]=max(Max(k)[0],Max(ls)[0]);
			Max(k)[1]=max(Max(k)[1],Max(ls)[1]);
			Min(k)[0]=min(Min(k)[0],Min(ls)[0]);
			Min(k)[1]=min(Min(k)[1],Min(ls)[1]);
		}
		if(rs){
			Max(k)[0]=max(Max(k)[0],Max(rs)[0]);
			Max(k)[1]=max(Max(k)[1],Max(rs)[1]);
			Min(k)[0]=min(Min(k)[0],Min(rs)[0]);
			Min(k)[1]=min(Min(k)[1],Min(rs)[1]);
		}
		return;
	}
	inline void update(reg int k,reg int val){
		cnt(k)+=val;
		Ans(k)=max(Ans(k),cnt(k));
		return;
	}
	inline void Add(reg int k,reg int val){
		update(k,val);
		if(cov(k)){
			tag(k)+=val;
			his(k)=max(his(k),tag(k));
		}
		else
			add(k)+=val;
		return;
	}
	inline void Cov(reg int k){
		if(!cov(k))
			cov(k)=true,his(k)=0;
		cnt(k)=tag(k)=0;
		return;
	}
	inline void pushtag(reg int k,reg int v1,int v2){
		cov(k)=true,his(k)=max(his(k),v2);
		cnt(k)=tag(k)=v1,Ans(k)=max(Ans(k),his(k));
		return;
	}
	inline void pushdown(reg int k){
		reg int ls=lson(k),rs=rson(k);
		if(add(k)){
			if(ls)
				Add(ls,add(k));
			if(rs)
				Add(rs,add(k));
			add(k)=0;
		}
		if(cov(k)){
			if(ls)
				pushtag(ls,tag(k),his(k));
			if(rs)
				pushtag(rs,tag(k),his(k));
			cov(k)=false;
			tag(k)=0;
		}
		return;
	}
	inline int build(reg int l,reg int r,reg int wd){
		reg int k=++tot;
		reg int mid=(l+r)>>1;
		WD=wd;
		nth_element(dat+l,dat+mid+1,dat+r+1,cmp);
		unit[k]=dat[mid];
		if(l<mid)
			lson(k)=build(l,mid-1,wd^1);
		if(r>mid)
			rson(k)=build(mid+1,r,wd^1);
		pushup(k);
		return k;
	}
	inline bool in(const Node& a,reg int l,reg int r){
		return a.Max[0]<=r&&l<=a.Min[1];
	}
	inline bool out(const Node& a,reg int l,reg int r){
		return a.Min[0]>r||l>a.Max[1];
	}
	inline void modify(reg int k,reg int l,reg int r){
		reg int ls=lson(k),rs=rson(k);
		if(in(unit[k],l,r)){
			Add(k,1);
			return;
		}
		if(out(unit[k],l,r)){
			Cov(k);
			return;
		}
		pushdown(k);
		if(unit[k].x[0]<=r&&l<=unit[k].x[1])
			update(k,1);
		else
			cnt(k)=0;
		if(ls)
			modify(ls,l,r);
		if(rs)
			modify(rs,l,r);
		return;
	}
	inline void dfs(reg int u){
		reg int ls=lson(u),rs=rson(u);
		pushdown(u);
		ans[id(u)]=Ans(u);
		if(ls)
			dfs(ls);
		if(rs)
			dfs(rs);
		return;
	}
}

int main(void){
	using namespace kD_Tree;
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		p[i].l=read(),p[i].r=read();
	for(reg int i=1;i<=m;++i)
		dat[i].x[0]=read(),dat[i].x[1]=read(),dat[i].id=i;
	root=build(1,m,0);
	for(reg int i=1;i<=n;++i)
		modify(root,p[i].l,p[i].r);
	dfs(root);
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}