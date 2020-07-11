#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,Min;

inline void Read(void){
	n=read(),Min=read();
	return;
}

struct Splay{
	int tot;
	int root;
	int fa[MAXN];
	int ch[MAXN][2];
	int val[MAXN],cnt[MAXN],size[MAXN];
	inline void maintain(reg int x){
		size[x]=size[ch[x][0]]+size[ch[x][1]]+cnt[x];
		return;
	}
	inline bool get(reg int x){
		return x==ch[fa[x]][1];
	}
	inline void clear(reg int x){
		fa[x]=ch[x][0]=ch[x][1]=0;
		val[x]=cnt[x]=size[x]=0;
		return;
	}
	inline void rotate(reg int x){
		reg int f=fa[x],ff=fa[f];
		reg bool w=get(x);
		ch[f][w]=ch[x][w^1];
		fa[ch[f][w]]=f;
		fa[f]=x;
		fa[x]=ff;
		ch[x][w^1]=f;
		if(ff)
			ch[ff][ch[ff][1]==f]=x;
		maintain(x);
		maintain(f);
		return;
	}
	inline void splay(reg int x,reg int goal){
		for(reg int qwq;(qwq=fa[x])!=goal;rotate(x))
			if(fa[qwq]!=goal)
				rotate(get(x)==get(qwq)?qwq:x);
		if(goal==0)
			root=x;
		return;
	}
	inline void insert(reg int x){
		if(!root){
			val[++tot]=x;
			++cnt[tot];
			root=tot;
			maintain(root);
			return;
		}
		reg int ID=root,f=0;
		while(true){
			if(val[ID]==x){
				++cnt[ID];
				maintain(ID);
				maintain(f);
				splay(ID,0);
				break;
			}
			f=ID;
			ID=ch[ID][val[ID]<x];
			if(!ID){
				val[++tot]=x;
				++cnt[tot];
				fa[tot]=f;
				ch[f][val[f]<x]=tot;
				root=tot;
				maintain(tot);
				maintain(f);
				splay(tot,0);
				return;
			}
		}
		return;
	}
	inline int id(reg int x){
		reg int ID=root;
		while(true){
			if(x==val[ID])
				return ID;
			else{
				if(x<val[ID])
					ID=ch[ID][0];
				else
					ID=ch[ID][1];
			}
		}
	}
	inline int rank(reg int x){
		reg int res=0,ID=root;
		while(true){
			if(x<val[ID])
				ID=ch[ID][0];
			else{
				res+=size[ch[ID][0]];
				if(x==val[ID]){
					splay(ID,0);
					return res+1;
				}
				res+=cnt[ID];
				ID=ch[ID][1];
			}
		}
		return -1;
	}
	inline int kth(reg int x){
		reg int ID=root;
		while(true){
			if(ch[ID][0]&&x<=size[ch[ID][0]]){
				ID=ch[ID][0];
			}
			else{
				x-=cnt[ID]+size[ch[ID][0]];
				if(x<=0)
					return val[ID];
				ID=ch[ID][1];
			}
		}
		return -INF;
	}
	inline int pre(void){
		reg int ID=ch[root][0];
		while(ch[ID][1])
			ID=ch[ID][1];
		return ID;
	}
	inline int nxt(void){
		reg int ID=ch[root][1];
		while(ch[ID][0])
			ID=ch[ID][0];
		return ID;
	}
	inline void del(reg int k){
		rank(k);
		if(cnt[root]>1){
			--cnt[root];
			maintain(root);
			return;
		}
		if(!ch[root][0]&&!ch[root][1]){
			clear(root);
			root=0;
			return;
		}
		if(!ch[root][0]){
			reg int ID=root;
			root=ch[root][1];
			fa[root]=0;
			clear(ID);
			return;
		}
		if(!ch[root][1]){
			reg int ID=root;
			root=ch[root][0];
			fa[root]=0;
			clear(ID);
			return;
		}
		reg int x=pre(),ID=root;
		splay(x,0);
		fa[ch[ID][1]]=x;
		ch[x][1]=ch[ID][1];
		clear(ID);
		maintain(root);
		return;
	}
};

int delta;
Splay S;

inline void Work(void){
	S.insert(-INF);
	S.insert(INF);
	reg int cnt=0;
	while(n--){
		static char ch;
		static int k;
		do
			ch=getchar();
		while(ch<'A'||'Z'<ch);
		k=read();
		switch(ch){
			case 'I':
				if(k>=Min){
					S.insert(k-delta);
					++cnt;
				}
				break;
			case 'A':{
				delta+=k;
				break;
			}
			case 'S':{
				delta-=k;
				S.insert(Min-delta);
				reg int a=S.id(-INF),b=S.id(Min-delta);
				S.splay(a,0);
				S.splay(b,a);
				S.ch[S.ch[S.root][1]][0]=0;
				S.del(Min-delta);
				break;
			}
			case 'F':{
				reg int temp=S.rank(INF)-2;
				if(temp<k)
					puts("-1");
				else
					printf("%d\n",S.kth(temp+2-k)+delta);
				break;
			}
			default:break;
		}
	}
	reg int temp=S.rank(INF)-2;
	printf("%d\n",cnt-temp);
	return;
}
