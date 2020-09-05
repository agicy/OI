#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+500;

namespace Splay{
	const int MAXSIZE=MAXN;
	struct Node{
		int fa,ch[2];
		int size,cnt;
		int val;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define size(x) unit[(x)].size
		#define cnt(x) unit[(x)].cnt
		#define val(x) unit[(x)].val
	};
	int tot,root;
	Node unit[MAXSIZE];
	inline bool get(reg int x){
		return ch(fa(x))[1]==x;
	}
	inline void pushup(reg int p){
		size(p)=size(ch(p)[0])+size(ch(p)[1])+cnt(p);
		return;
	}
	inline void rotate(reg int x){
		reg int y=fa(x),z=fa(y),dir=get(x),w=ch(x)[dir^1];
		fa(x)=z;
		if(z)
			ch(z)[get(y)]=x;
		fa(y)=x;
		ch(x)[dir^1]=y;
		fa(w)=y,ch(y)[dir]=w;
		pushup(y),pushup(x);
		return;
	}
	inline void splay(reg int x,reg int goal){
		if(!x)
			return;
		for(reg int f=fa(x);f=fa(x),f!=goal;rotate(x))
			if(fa(f)!=goal)
				rotate(get(x)==get(f)?f:x);
		if(!goal)
			root=x;
		return;
	}
	inline int find(reg int Val){
		reg int p=root;
		while(p&&Val!=val(p)&&ch(p)[Val>val(p)])
			p=ch(p)[Val>val(p)];
		splay(p,0);
		return p;
	}
	inline void insert(reg int Val){
		reg int p=root,pre=0;
		while(p&&Val!=val(p))
			pre=p,p=ch(p)[Val>val(p)];
		if(p)
			++cnt(p);
		else{
			p=++tot;
			fa(p)=pre;
			ch(p)[0]=ch(p)[1]=0;
			val(p)=Val;
			size(p)=cnt(p)=1;
			if(pre)
				ch(pre)[Val>val(pre)]=p;
		}
		splay(p,0);
		return;
	}
	inline int pre(reg int Val){
		reg int p=find(Val);
		if(val(p)<Val)
			return p;
		p=ch(p)[0];
		while(ch(p)[1])
			p=ch(p)[1];
		return p;
	}
	inline int suf(reg int Val){
		reg int p=find(Val);
		if(val(p)>Val)
			return p;
		p=ch(p)[1];
		while(ch(p)[0])
			p=ch(p)[0];
		return p;
	}
	inline void del(reg int Val){
		reg int Pre=pre(Val),Suf=suf(Val);
		splay(Pre,0),splay(Suf,Pre);
		reg int p=ch(Suf)[0];
		--cnt(p);
		if(cnt(p)==0)
			fa(p)=ch(Suf)[0]=0;
		else
			splay(p,0);
		return;
	}
	inline int rnk(reg int Val){
		reg int p=find(Val);
		return size(ch(p)[0])+1;
	}
	inline int kth(reg int k){
		reg int p=root;
		if(k>size(p))
			return 0;
		while(true){
			if(k<=size(ch(p)[0]))
				p=ch(p)[0];
			else if(k<=size(ch(p)[0])+cnt(p))
				return val(p);
			else{
				k-=size(ch(p)[0])+cnt(p);
				p=ch(p)[1];
			}
		}
	}
}

using namespace Splay;

int main(void){
	insert(-0X7FFFFFFF),insert(0X7FFFFFFF);
	reg int n=read();
	while(n--){
		static int opt,x;
		opt=read(),x=read();
		switch(opt){
			case 1:{
				insert(x);
				break;
			}
			case 2:{
				del(x);
				break;
			}
			case 3:{
				printf("%d\n",rnk(x)-1);
				break;
			}
			case 4:{
				printf("%d\n",kth(x+1));
				break;
			}
			case 5:{
				printf("%d\n",val(pre(x)));
				break;
			}
			case 6:{
				printf("%d\n",val(suf(x)));
				break;
			}
			default:break;
		}
	}
	return 0;
}
