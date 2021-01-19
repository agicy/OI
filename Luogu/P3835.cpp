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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=5e5+5;

namespace FHQTreap{
	const int MAXSIZE=MAXN*70;
	struct Node{
		int key;
		int ch[2];
		int siz;
		int val;
		#define key(x) unit[(x)].key
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int v){
		reg int p=++tot;
		val(p)=v;
		key(p)=rand();
		siz(p)=1;
		return p;
	}
	inline int copy(reg int p){
		reg int q=New(0);
		unit[q]=unit[p];
		return q;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void split(reg int p,reg int v,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(val(p)<=v){
			x=copy(p);
			split(rson(x),v,rson(x),y);
			pushup(x);
		}
		else{
			y=copy(p);
			split(lson(y),v,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(key(x)<key(y)){
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			lson(y)=merge(x,lson(y));
			pushup(y);
			return y;
		}
	}
	inline int kth(reg int p,reg int k){
		while(true){
			if(k<=siz(lson(p)))
				p=lson(p);
			else{
				k-=siz(lson(p))+1;
				if(!k)
					return val(p);
				else
					p=rson(p);
			}
		}
		return -1;
	}
	inline int insert(reg int p,reg int v){
		int x,y;
		split(p,v,x,y);
		return merge(merge(x,New(v)),y);
	}
	inline int del(reg int p,reg int w){
		int x,y,z;
		split(p,w,x,z);
		split(x,w-1,x,y);
		return merge(merge(x,merge(lson(y),rson(y))),z);
	}
	int ans;
	inline int rnk(reg int p,reg int v){
		int x,y;
		split(p,v-1,x,y);
		ans=siz(x);
		return merge(x,y);
	}
	inline int pre(reg int p,reg int v){
		int x,y;
		split(p,v-1,x,y);
		reg int id=x;
		while(rson(id))
			id=rson(id);
		ans=val(id);
		return merge(x,y);
	}
	inline int suf(reg int p,reg int v){
		int x,y;
		split(p,v,x,y);
		reg int id=y;
		while(lson(id))
			id=lson(id);
		ans=val(id);
		return merge(x,y);
	}
}

int cnt,rt[MAXN];

const int inf=(1ll<<31)-1;

int main(void){
	srand(time(0));
	reg int n=read();
	using namespace FHQTreap;
	rt[0]=merge(New(-inf),New(inf));
	while(n--){
		static int opt,v,x;
		v=read(),opt=read(),x=read();
		switch(opt){
			case 1:{
				rt[++cnt]=insert(rt[v],x);
				break;
			}
			case 2:{
				rt[++cnt]=del(rt[v],x);
				break;
			}
			case 3:{
				rt[++cnt]=rnk(rt[v],x);
				printf("%d\n",ans);
				break;
			}
			case 4:{
				rt[++cnt]=rt[v];
				printf("%d\n",kth(rt[cnt],x+1));
				break;
			}
			case 5:{
				rt[++cnt]=pre(rt[v],x);
				printf("%d\n",ans);
				break;
			}
			case 6:{
				rt[++cnt]=suf(rt[v],x);
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}