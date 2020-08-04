#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=200+5;
const int MAXM=1e5+5;
const int MAXSIZE=10+5;
const int INF=0X3F3F3F3F;

namespace Splay{
	struct Node{
		int fa,ch[2];
		int size,cnt;
		int val;
		#define val(x) unit[(x)].val
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define size(x) unit[(x)].size
		#define cnt(x) unit[(x)].cnt
	};
	int tot;
	int root;
	Node unit[MAXN+MAXM];
	inline bool check(reg int k){
		return ch(fa(k))[1]==k;
	}
	inline void pushup(reg int k){
		size(k)=size(ch(k)[0])+size(ch(k)[1])+cnt(k);
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa(x),z=fa(y),k=check(x),w=ch(x)[!k];
		ch(y)[k]=w,fa(w)=y;
		ch(z)[check(y)]=x,fa(x)=z;
		ch(x)[!k]=y,fa(y)=x;
		pushup(y),pushup(x);
		return;
	}
	inline void splay(reg int x,reg int goal=0){
		for(reg int f;f=fa(x),f!=goal;rotate(x))
			if(fa(f)!=goal)
				rotate(check(x)==check(f)?f:x);
		if(!goal)
			root=x;
		return;
	}
	inline void find(reg int v){
		if(!root)
			return;
		reg int p=root;
		while(ch(p)[v>val(p)]&&v!=val(p))
			p=ch(p)[v>val(p)];
		splay(p);
		return;
	}
	inline void insert(reg int v){
		reg int p=root,q=0;
		while(p&&val(p)!=v){
			q=p;
			p=ch(p)[v>val(p)];
		}
		if(p)
			++cnt(p);
		else{
			p=++tot;
			if(q)
				ch(q)[v>val(q)]=p;
			ch(p)[0]=ch(p)[1]=0;
			val(p)=v,fa(p)=q;
			cnt(p)=size(p)=1;
		}
		splay(p);
		return;
	}
	inline int query(reg int k){
		reg int p=root;
		while(true){
			if(ch(p)[0]&&size(ch(p)[0])>=k)
				p=ch(p)[0];
			else{
				if(size(ch(p)[0])+cnt(p)<k){
					k-=size(ch(p)[0])+cnt(p);
					p=ch(p)[1];
				}
				else
					return p;
			}
		}
	}
}

using namespace Splay;

int n,m,q;
char s[MAXN+MAXM][MAXSIZE];

int main(void){
	scanf("%d",&n);
	insert(-INF),insert(+INF);
	for(reg int i=1;i<=n;++i){
		scanf("%s",s[i]);
		insert(i);
	}
	scanf("%d",&m);
	for(reg int i=1;i<=m;++i){
		static int k;
		scanf("%s%d",s[i+n],&k);
		k+=2;
		reg int id=query(k);
		splay(id);
		reg int sid=query(k-1);
		splay(sid,id);
		ch(sid)[1]=++tot;
		ch(tot)[0]=ch(tot)[1]=0;
		fa(tot)=sid;
		val(tot)=k;
		cnt(tot)=size(tot)=1;
		pushup(sid),pushup(id);
	}
	scanf("%d",&q);
	for(reg int i=1;i<=q;++i){
		static int k;
		scanf("%d",&k);
		reg int id=Splay::query(k+2);
		puts(s[id-2]);
	}
	return 0;
}