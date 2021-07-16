#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=2e5+5;

namespace SAM{
	const int MAXS=MAXN;
	const int lim=26;
	struct Node{
		int fa,len,ch[lim];
		int pos;
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
		#define pos(x) unit[(x)].pos
	};
	int tot,las;
	Node unit[MAXS<<1];
	inline int getId(void){
		reg int p=++tot;
		//memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void init(void){
		tot=0,las=getId();
		return;
	}
	inline void insert(reg int c,reg int id){
		reg int np=getId(),p=las;
		len(np)=len(p)+1;
		pos(np)=id;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(len(q)==len(p)+1)
				fa(np)=q;
			else{
				reg int nq=getId();
				unit[nq]=unit[q];
				len(nq)=len(p)+1;
				fa(np)=fa(q)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return;
	}
	int cnt[MAXS];
	int rnk[MAXS<<1];
	inline void build(reg int n){
		for(reg int i=1;i<=tot;++i)
			++cnt[len(i)];
		for(reg int i=1;i<=n;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=1;i<=tot;++i)
			rnk[cnt[len(i)]--]=i;
		return;
	}
	namespace SegmentTree{
		const int MAXSIZE=MAXS*60;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
		};
		int tot;
		Node unit[MAXSIZE];
		inline int update(reg int l,reg int r,reg int pos){
			reg int p=++tot;
			if(l!=r){
				if(pos<=mid)
					lson(p)=update(l,mid,pos);
				else
					rson(p)=update(mid+1,r,pos);
			}
			return p;
		}
		inline int merge(reg int x,reg int y){
			if(!x||!y)
				return x|y;
			reg int p=++tot;
			lson(p)=merge(lson(x),lson(y)),rson(p)=merge(rson(x),rson(y));
			return p;
		}
		inline bool query(reg int p,reg int l,reg int r,reg int L,reg int R){
			if(!p)
				return false;
			if(L<=l&&r<=R)
				return true;
			if(L<=mid&&mid<R)
				return query(lson(p),l,mid,L,R)||query(rson(p),mid+1,r,L,R);
			else if(L<=mid)
				return query(lson(p),l,mid,L,R);
			else
				return query(rson(p),mid+1,r,L,R);
		}
		#undef mid
		#undef lson
		#undef rson
	}
	int rt[MAXS<<1];
	int f[MAXS<<1],g[MAXS<<1];
	inline void solve(reg int n,reg char s[]){
		SAM::init();
		for(reg int i=1;i<=n;++i){
			SAM::insert(s[i]-'a',i);
			rt[las]=SegmentTree::update(1,n,i);
		}
		SAM::build(n);
		for(reg int i=tot;i>1;--i){
			reg int u=rnk[i];
			rt[fa(u)]=SegmentTree::merge(rt[fa(u)],rt[u]);
		}
		reg int ans=1;
		for(reg int i=2;i<=tot;++i){
			reg int u=rnk[i];
			if(fa(u)==1){
				f[u]=1,g[u]=u;
				continue;
			}
			if(SegmentTree::query(rt[g[fa(u)]],1,n,pos(u)-len(u)+len(g[fa(u)]),pos(u)-1))
				f[u]=f[fa(u)]+1,g[u]=u;
			else
				f[u]=f[fa(u)],g[u]=g[fa(u)];
			ans=max(ans,f[u]);
		}
		printf("%d\n",ans);
		return;
	}
	#undef fa
	#undef len
	#undef ch
}

int n;
char s[MAXN];

bool ed;

int main(void){
	scanf("%d%s",&n,s+1);
	SAM::solve(n,s);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}