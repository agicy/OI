#include <bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 51061

const int MAXN=100000+5;

namespace LCT{
	#define lson (ch[p][0])
	#define rson (ch[p][1])
	int fa[MAXN],ch[MAXN][2];
	int size[MAXN];
	int sum[MAXN],val[MAXN];
	bool tag[MAXN];
	int tagAdd[MAXN],tagMul[MAXN];
	inline bool get(reg int p){
		return ch[fa[p]][1]==p;
	}
	inline bool isRoot(reg int p){
		return ch[fa[p]][0]!=p&&ch[fa[p]][1]!=p;
	}
	inline void pushup(reg int p){
		sum[p]=(sum[lson]+sum[rson]+val[p])%MOD;
		size[p]=size[lson]+size[rson]+1;
		return;
	}
	inline void Add(reg int p,reg ll Val){
		sum[p]=((ll)sum[p]+(ll)size[p]*Val)%MOD;
		val[p]=((ll)val[p]+(ll)Val)%MOD;
		tagAdd[p]=((ll)tagAdd[p]+(ll)Val)%MOD;
		return;
	}
	inline void Mul(reg int p,reg ll Val){
		sum[p]=(ll)sum[p]*Val%MOD;
		val[p]=(ll)val[p]*Val%MOD;
		tagAdd[p]=(ll)tagAdd[p]*Val%MOD;
		tagMul[p]=(ll)tagMul[p]*Val%MOD;
		return;
	}
	inline void Swap(reg int p){
		swap(lson,rson);
		tag[p]^=1;
		return;
	}
	inline void pushMul(reg int p){
		if(tagMul[p]!=1){
			Mul(lson,tagMul[p]);
			Mul(rson,tagMul[p]);
			tagMul[p]=1;
		}
		return;
	}
	inline void pushAdd(reg int p){
		if(tagAdd[p]){
			Add(lson,tagAdd[p]);
			Add(rson,tagAdd[p]);
			tagAdd[p]=0;
		}
		return;
	}
	inline void pushSwap(reg int p){
		if(tag[p]){
			if(lson)
				Swap(lson);
			if(rson)
				Swap(rson);
			tag[p]=0;
		}
		return;
	}
	inline void pushdown(reg int p){
		pushMul(p);
		pushAdd(p);
		pushSwap(p);
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
		if(!isRoot(y))
			ch[z][get(y)]=x;
		ch[x][!k]=y;
		ch[y][k]=w;
		if(w)
			fa[w]=y;
		fa[y]=x,fa[x]=z;
		pushup(y);
		return;
	}
	inline void update(reg int p){
		if(!isRoot(p))
			update(fa[p]);
		pushdown(p);
		return;
	}
	inline void splay(reg int p){
		update(p);
		for(reg int f=fa[p];f=fa[p],!isRoot(p);rotate(p))
			if(!isRoot(f))
				rotate(get(p)==get(f)?f:p);
		pushup(p);
		return;
	}
	inline void access(reg int p){
		for(reg int pre=0;p;pre=p,p=fa[p])
			splay(p),rson=pre,pushup(p);
		return;
	}
	inline void makeRoot(reg int p){
		access(p),splay(p),Swap(p);
		return;
	}
	inline void split(reg int x,reg int y){
		makeRoot(x),access(y),splay(y);
		return;
	}
	inline void link(reg int x,reg int y){
		makeRoot(x);
		fa[x]=y;
		return;
	}
	inline void cut(reg int x,reg int y){
		split(x,y);
		fa[x]=ch[y][0]=0;
		return;
	}
	inline void UpdateAdd(reg int x,reg int y,reg ll ch){
		split(x,y),Add(y,ch);
		return;
	}
	inline void UpdateMul(reg int x,reg int y,reg ll ch){
		split(x,y),Mul(y,ch);
		return;
	}
	inline int Query(reg int x,reg int y){
		split(x,y);
		return sum[y]%MOD;
	}
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			size[i]=val[i]=tagMul[i]=1;
		return;
	}
	#undef lson
	#undef rson
}

int n,q;

signed main(void){
	scanf("%d%d",&n,&q);
	LCT::Init(n);
	for(reg int i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		LCT::link(u,v);
	}
	while(q--){
		static char opt;
		static int u1,v1,u2,v2;
		static ll c;
		cin>>opt;
		if(opt=='+'){
			scanf("%d%d%lld",&u1,&v1,&c);
			LCT::UpdateAdd(u1,v1,c);
		}
		else if(opt=='-'){
			scanf("%d%d%d%d",&u1,&v1,&u2,&v2);
			LCT::cut(u1,v1);
			LCT::link(u2,v2);
		}
		else if(opt=='*'){
			scanf("%d%d%lld",&u1,&v1,&c);
			LCT::UpdateMul(u1,v1,c);
		}
		else if(opt=='/'){
			scanf("%d%d",&u1,&v1);
			printf("%d\n",LCT::Query(u1,v1));
		}
	}
	return 0;
}