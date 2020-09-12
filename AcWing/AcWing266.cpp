#include <bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3fll;

int n,m;
ll a[MAXN];

namespace Splay{
	const int MAXSIZE=MAXN+MAXM;
	int root,tot;

	struct Node{
		int fa,ch[2];
		int siz;
		ll val,Min,tagA;
		bool tagR;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define Min(x) unit[(x)].Min
		#define tagA(x) unit[(x)].tagA
		#define tagR(x) unit[(x)].tagR
		#define lson(x) unit[(x)].ch[0]
		#define rson(x) unit[(x)].ch[1]
	};
	Node unit[MAXSIZE];
	inline bool chk(reg int p){
		return p==ch(fa(p))[1];
	}
	inline int make(reg int father,reg ll Val){
		reg int k=++tot;
		fa(k)=father,ch(k)[0]=ch(k)[1]=0,siz(k)=1,val(k)=Min(k)=Val,tagR(k)=false,tagA(k)=0;
		return k;
	}
	inline void connect(reg int p,reg int father,reg int k){
		fa(p)=father,ch(father)[k]=p;
		return;
	}
	inline void pushup(reg int p){
		Min(p)=val(p);
		if(lson(p))
			Min(p)=min(Min(p),Min(lson(p)));
		if(rson(p))
			Min(p)=min(Min(p),Min(rson(p)));
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void add(reg int k,reg ll Val){
		val(k)+=Val,Min(k)+=Val,tagA(k)+=Val;
		return;
	}
	inline void pushdown(reg int p){
		if(tagR(p)){
			swap(lson(p),rson(p));
			tagR(lson(p))^=1,tagR(rson(p))^=1;
			tagR(p)=false;
		}
		if(tagA(p)){
			if(lson(p))
				add(lson(p),tagA(p));
			if(rson(p))
				add(rson(p),tagA(p));
			tagA(p)=0;
		}
		return;
	}
	inline void rotate(reg int p){
		reg int f=fa(p),ff=fa(f);
		reg int dir1=chk(p),dir2=chk(f);
		connect(ch(p)[dir1^1],f,dir1),connect(f,p,dir1^1),connect(p,ff,dir2);
		pushup(f),pushup(p);
		return;
	}
	inline void splay(reg int p,reg int goal){
		reg int tar=fa(goal);
		for(reg int f=fa(p);f=fa(p),f!=tar;rotate(p))
			if(fa(f)!=tar)
				rotate(chk(p)!=chk(f)?p:f);
		if(goal==root)
			root=p;
		return;
	}
	inline void build(reg int& p,reg int l,reg int r,reg int f,reg ll a[]){
		if(l>r)
			return;
		p=++tot;
		reg int mid=(l+r)>>1;
		fa(p)=f,val(p)=Min(p)=a[mid],tagR(p)=false,tagA(p)=0;
		build(lson(p),l,mid-1,p,a),build(rson(p),mid+1,r,p,a);
		pushup(p);
		return;
	}
	inline int kth(reg int k){
		reg int p=root;
		while(true){
			pushdown(p);
			if(siz(lson(p))>=k)
				p=lson(p);
			else{
				k-=siz(lson(p))+1;
				if(!k)
					return p;
				p=rson(p);
			}
		}
		return -1;
	}
	inline int split(reg int l,reg int r,reg int dir){
		int nxt[2]={kth(l),kth(r+2)};
		splay(nxt[dir^1],root);
		splay(nxt[dir],ch(root)[dir]);
		return ch(ch(root)[dir])[dir^1];
	}
	inline void revolve(reg int l,reg int r,reg int d){
		if(!d)
			return;
		reg int f1=split(l,r-d,0);
		reg int f2=lson(root);
		pushdown(root),pushdown(f2);
		rson(f2)=0;
		pushup(f2),pushup(root);
		reg int f3=split(r-d+1-siz(f1),r-siz(f1),1);
		if(!f3){
			reg int f4=rson(rson(root));
			connect(f1,rson(root),1);
			pushup(rson(root)),pushup(root);
			reg int f5=root;
			pushdown(root);
			while(rson(f5))
				f5=rson(f5),pushdown(f5);
			splay(f5,rson(root));
			pushdown(root),pushdown(f5);
			connect(f4,f5,1);
			pushup(rson(root)),pushup(root);
		}
		else{
			pushdown(f3);
			while(rson(f3))
				f3=rson(f3),pushdown(f3);
			splay(f3,lson(rson(root)));
			connect(f1,lson(rson(root)),1);
			pushup(lson(rson(root))),pushup(rson(root)),pushup(root);
		}
		return;
	}
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%lld",&a[i+1]);
	Splay::unit[0].Min=a[0]=a[n+2]=inf;
	Splay::build(Splay::root,1,n+2,0,a);
	scanf("%d",&m);
	for(reg int i=1;i<=m;++i){
		static string opt;
		cin>>opt;
		if(opt=="ADD"){
			static int l,r;
			static ll v;
			scanf("%d%d%lld",&l,&r,&v);
			reg int p=Splay::split(l,r,1),f=Splay::unit[p].fa,ff=Splay::unit[f].fa;
			Splay::unit[p].tagA+=v;
			Splay::unit[p].val+=v;
			Splay::unit[p].Min+=v;
			Splay::pushup(f),Splay::pushup(ff);
		}
		else if(opt=="REVERSE"){
			static int l,r;
			scanf("%d%d",&l,&r);
			reg int p=Splay::split(l,r,1);
			Splay::unit[p].tagR^=1;
		}
		else if(opt=="REVOLVE"){
			static int l,r,t;
			scanf("%d%d%d",&l,&r,&t);
			t%=r-l+1;
			Splay::revolve(l,r,t);
		}
		else if(opt=="INSERT"){
			static int x;
			static ll v;
			scanf("%d%lld",&x,&v);
			reg int p=Splay::split(x,x,1),f=Splay::unit[p].fa,ff=Splay::unit[f].fa;
			Splay::pushdown(p);
			Splay::unit[p].ch[1]=Splay::make(p,v);
			Splay::pushup(p),Splay::pushup(f),Splay::pushup(ff);
		}
		else if(opt=="DELETE"){
			static int x;
			scanf("%d",&x);
			reg int p=Splay::split(x,x,1),f=Splay::unit[p].fa,ff=Splay::unit[f].fa;
			Splay::unit[f].ch[0]=0;
			Splay::pushup(f),Splay::pushup(ff);
		}
		else if(opt=="MIN"){
			static int l,r;
			scanf("%d%d",&l,&r);
			reg int p=Splay::split(l,r,1);
			printf("%lld\n",Splay::unit[p].Min);
		}
	}
	return 0;
}