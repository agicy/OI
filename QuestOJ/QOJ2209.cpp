#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=300000+5;
const int MAXN=100000+5;

int n,m;
char str[MAXSIZE];
int L[MAXN],R[MAXN];

namespace SAM{
	struct Node{
		int dep,link;
		int next[26];
	};
	int tot;
	int last;
	Node unit[MAXSIZE<<1];
	inline void Init(void){
		tot=1,last=1;
		return;
	}
	inline int insert(reg int ch){
		if(unit[last].next[ch]&&unit[unit[last].next[ch]].dep==unit[last].dep+1){
			return unit[last].next[ch];
		}
		reg int ID=++tot,pre=last,flag=0;
		unit[ID].dep=unit[last].dep+1;
		while(pre!=0&&unit[pre].next[ch]==0){
			unit[pre].next[ch]=ID;
			pre=unit[pre].link;
		}
		if(pre==0)
			unit[ID].link=1;
		else{
			reg int q=unit[pre].next[ch];
			if(unit[pre].dep+1==unit[q].dep)
				unit[ID].link=q;
			else{
				if(unit[ID].dep==unit[pre].dep+1)
					flag=true;
				reg int clone=++tot;
				unit[clone]=unit[q];
				unit[clone].dep=unit[pre].dep+1;
				unit[clone].link=unit[q].link;
				unit[ID].link=unit[q].link=clone;
				while(pre!=0&&unit[pre].next[ch]==q){
					unit[pre].next[ch]=clone;
					pre=unit[pre].link;
				}
				if(flag)
					ID=clone;
			}
		}
		return ID;
	}
}

using namespace SAM;

int cnt,head[MAXSIZE<<1],to[MAXSIZE<<1],Next[MAXSIZE<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int w[MAXSIZE<<1];

inline void build(void){
	for(reg int i=2;i<=tot;++i){
		Add_Edge(unit[i].link,i);
		w[i]=unit[i].dep-unit[unit[i].link].dep;
	}
	return;
}

int fa[MAXSIZE<<1],dep[MAXSIZE<<1];
int son[MAXSIZE<<1],size[MAXSIZE<<1];

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

int tim,dfn[MAXSIZE<<1];
int top[MAXSIZE<<1];
int rnk[MAXSIZE<<1];

inline void DFS2(reg int ID,reg int father,reg int topf){
	dfn[ID]=++tim;
	rnk[tim]=ID;
	top[ID]=topf;
	if(son[ID])
		DFS2(son[ID],ID,topf);
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID])
			DFS2(to[i],ID,to[i]);
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1)
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll val;
		ll sum2,sum;
		ll tag;
		#define val(x) unit[(x)].val
		#define sum2(x) unit[(x)].sum2
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<4];
	inline void Add(reg int k,reg ll Val){
		sum2(k)+=2ll*Val*sum(k)+Val*Val*val(k);
		sum(k)+=Val*val(k);
		tag(k)+=Val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			Add(lson,tag(k));
			Add(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			val(k)=w[rnk[l]];
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		val(k)=val(lson)+val(rson);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		sum(k)=sum(lson)+sum(rson);
		sum2(k)=sum2(lson)+sum2(rson);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

inline void Update(reg int u,reg ll val){
	while(top[u]){
		Update(1,1,tot,dfn[top[u]],dfn[u],val);
		u=fa[top[u]];
	}
	return;
}

int main(void){
	scanf("%d",&n);
	Init();
	for(reg int i=1;i<=n;++i){
		static char t[MAXSIZE];
		scanf("%s",t+1);
		reg int len=strlen(t+1);
		L[i]=R[i-1]+1,R[i]=L[i]+len-1;
		SAM::last=1;
		for(reg int j=1;j<=len;++j){
			str[L[i]+j-1]=t[j];
			SAM::last=insert(t[j]-'a');
		}
	}
	m=R[n];
	build();
	DFS1(1,0);
	DFS2(1,0,1);
	Build(1,1,tot);
	for(reg int i=1;i<=n;++i){
		reg int p=1;
		for(reg int j=L[i];j<=R[i];++j){
			p=SAM::unit[p].next[str[j]-'a'];
			Update(p,1ll);
		}
		printf("%lld\n",SegmentTree::unit[1].sum2);
	}
	return 0;
}