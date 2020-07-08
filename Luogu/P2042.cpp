#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define TAGNONE INF
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000000+5;

int n,m;

namespace Splay{
	struct Node{
		int fa,ch[2];
		int size;
		int val,sum;
		int tag,rev;
		int lMax,rMax,Max;
		inline void clear(void){
			fa=ch[0]=ch[1]=rev=0;
			tag=TAGNONE;
			return;
		}
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define lson(x) unit[(x)].ch[0]
		#define rson(x) unit[(x)].ch[1]
		#define size(x) unit[(x)].size
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
		#define tag(x) unit[(x)].tag
		#define rev(x) unit[(x)].rev
		#define lMax(x) unit[(x)].lMax
		#define rMax(x) unit[(x)].rMax
		#define Max(x) unit[(x)].Max
	};
	int a[MAXN],id[MAXN];
	int tot;
	int root;
	int top,S[MAXN];
	Node unit[MAXN];
	inline int New(void){
		if(top)
			return S[top--];
		else
			return ++tot;
	}
	inline void Set(reg int u,int Val){
		if(!u)
			return;
		tag(u)=val(u)=Val;
		sum(u)=Val*size(u);
		lMax(u)=rMax(u)=max(sum(u),0);
		Max(u)=max(sum(u),Val);
		return;
	}
	inline void reverse(reg int u){
		swap(lson(u),rson(u));
		swap(lMax(u),rMax(u));
		rev(u)^=1;
		return;
	}
	inline void pushup(reg int u){
		sum(u)=sum(lson(u))+sum(rson(u))+val(u);
		size(u)=size(lson(u))+size(rson(u))+1;
		Max(u)=max(max(Max(lson(u)),Max(rson(u))),rMax(lson(u))+lMax(rson(u))+val(u));
		lMax(u)=max(lMax(lson(u)),sum(lson(u))+lMax(rson(u))+val(u));
		rMax(u)=max(rMax(rson(u)),sum(rson(u))+rMax(lson(u))+val(u));
		return;
	}
	inline void pushdown(reg int u){
		if(tag(u)!=TAGNONE){
			Set(lson(u),tag(u));
			Set(rson(u),tag(u));
			tag(u)=TAGNONE;
		}
		if(rev(u)){
			reverse(lson(u));
			reverse(rson(u));
			rev(u)=false;
		}
		return;
	}
	inline bool get(reg int u){
		return rson(fa(u))==u;
	}
	inline void rotate(reg int x){
		int y=fa(x),z=fa(y),dir=get(x);
		ch(z)[get(y)]=x;
		fa(x)=z;
		ch(y)[dir]=ch(x)[dir^1];
		fa(ch(x)[dir^1])=y;
		ch(x)[dir^1]=y,fa(y)=x;
		pushup(y),pushup(x);
		return;
	}
	inline void splay(reg int x,reg int goal){
		for(reg int f;f=fa(x),f!=goal;rotate(x))
			if(fa(f)!=goal)
				rotate(get(x)!=get(f)?x:f);
		if(!goal)
			root=x;
		return;
	}
	inline void New(reg int u,int Val){
		Max(u)=sum(u)=Val;
		tag(u)=TAGNONE;
		rev(u)=0;
		lMax(u)=rMax(u)=max(Val,0);
		size(u)=1;
		return;
	}
	inline void Build(reg int l,reg int r,reg int father){
		if(r<l)
			return;
		reg int mid=(l+r)>>1;
		int u=id[mid],pre=id[father];
		if(l==r)
			New(u,a[l]);
		Build(l,mid-1,mid);
		Build(mid+1,r,mid);
		val(u)=a[mid],fa(u)=pre,
		tag(u)=TAGNONE;
		pushup(u);
		ch(pre)[mid>=father]=u;
		return;
	}
	inline int kth(reg int k){
		reg int u=root;
		while(true){
			pushdown(u);
			if(k<=size(lson(u)))
				u=lson(u);
			else if(k==size(lson(u))+1)
				return u;
			else{
				k-=size(lson(u))+1;
				u=rson(u);
			}
		}
	}
	inline void remove(reg int u){
		if(lson(u))
			remove(lson(u));
		if(rson(u))
			remove(rson(u));
		S[++top]=u;
		unit[u].clear();
		return;
	}
	inline int split(reg int pos,reg int len){
		reg int l=kth(pos),r=kth(pos+len+1);
		splay(l,0),splay(r,l);
		return lson(r);
	}
	inline void query(reg int pos,reg int len){
		reg int u=split(pos,len);
		printf("%d\n",sum(u));
		return;
	}
	inline void update(reg int pos,reg int len,reg int Val){
		reg int u=split(pos,len),f=fa(u);
		Set(u,Val);
		pushup(f),pushup(fa(f));
		return;
	}
	inline void reverse(reg int pos,reg int len){
		reg int u=split(pos,len),f=fa(u);
		if(tag(u)!=TAGNONE)
			return;
		reverse(u);
		pushup(f),pushup(fa(f));
		return;
	}
	inline void erase(reg int pos,reg int len){
		reg int u=split(pos,len),f=fa(u);
		remove(u);
		lson(f)=0;
		pushup(f),pushup(fa(f));
		return;
	}
	inline void insert(reg int pos,reg int len){
		for(reg int i=1;i<=len;++i)
			a[i]=read();
		for(reg int i=1;i<=len;++i)
			id[i]=New();
		Build(1,len,0);
		reg int z=id[(1+len)>>1];
		int x=kth(pos+1),y=kth(pos+2);
		splay(x,0),splay(y,x);
		fa(z)=y;
		lson(y)=z;
		pushup(y),pushup(x);
		return;
	}
}

using namespace Splay;

int main(void){
	n=read(),m=read();
	unit[0].Max=a[1]=a[n+2]=-INF;
	for(reg int i=1;i<=n;++i)
		a[i+1]=read();
	for(reg int i=1;i<=n+2;++i)
		id[i]=i;
	Build(1,n+2,0);
	root=(n+3)>>1;
	tot=n+2;
	for(reg int i=1;i<=m;++i){
		static string str;
		static int pos,tot,c;
		cin>>str;
		if(str=="MAX-SUM")
			printf("%d\n",unit[root].Max);
		else{
			pos=read(),tot=read();
			if(str=="INSERT")
				insert(pos,tot);
			else if(str=="DELETE")
				erase(pos,tot);
			else if(str=="REVERSE")
				reverse(pos,tot);
			else if(str=="GET-SUM")
				query(pos,tot);
			else if(str=="MAKE-SAME"){
				c=read();
				update(pos,tot,c);
			}
		}
	}
	return 0;
}