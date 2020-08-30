#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

struct Splay{
	int rt,tot,fa[MAXN],ch[MAXN][2],val[MAXN],cnt[MAXN],sz[MAXN];
	inline void maintain(int x){
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
		return;
	}
	inline bool get(int x){
		return x==ch[fa[x]][1];
	}
	inline void clear(int x){
		ch[x][0]=ch[x][1]=fa[x]=val[x]=sz[x]=cnt[x]=0;
		return;
	}
	inline void rotate(int x){
		int y=fa[x],z=fa[y],chk=get(x);
		ch[y][chk]=ch[x][chk^1];
		fa[ch[x][chk^1]]=y;
		ch[x][chk^1]=y;
		fa[y]=x;
		fa[x]=z;
		if(z)
			ch[z][y==ch[z][1]]=x;
		maintain(x);
		maintain(y);
		return;
	}
	inline void splay(int x,int goal){
		int f;
		for(f=fa[x];f=fa[x],f!=goal;rotate(x))
			if(fa[f]!=goal)
				rotate(get(x)==get(f)?f:x);
		if(goal==0)
			rt=x;
		return;
	}
	inline void ins(int k){
		if(!rt){
			val[++tot]=k;
			++cnt[tot];
			rt=tot;
			maintain(rt);
			return;
		}
		int cnr=rt,f=0;
		while(true){
			if(val[cnr]==k){
				++cnt[cnr];
				maintain(cnr);
				maintain(f);
				splay(cnr,0);
				break;
			}
			f=cnr;
			cnr=ch[cnr][val[cnr]<k];
			if(!cnr){
				val[++tot]=k;
				++cnt[tot];
				fa[tot]=f;
				ch[f][val[f]<k]=tot;
				maintain(tot);
				maintain(f);
				splay(tot,0);
				break;
			}
		}
	}
	inline int rk(int k){
		int res=0,cnr=rt;
		while(true)
			if(k<val[cnr])
				cnr=ch[cnr][0];
			else{
				res+=sz[ch[cnr][0]];
				if(k==val[cnr]){
					splay(cnr,0);
					return res+1;
				}
				res+=cnt[cnr];
				cnr=ch[cnr][1];
			}
	}
	inline int kth(int k){
		int cnr=rt;
		while(true)
			if(ch[cnr][0]&&k<=sz[ch[cnr][0]])
				cnr=ch[cnr][0];
			else{
				k-=cnt[cnr]+sz[ch[cnr][0]];
				if(k<=0)
					return val[cnr];
				cnr=ch[cnr][1];
			}
	}
	inline int pre(void){
		int cnr=ch[rt][0];
		while(ch[cnr][1])
			cnr=ch[cnr][1];
		return cnr;
	}
	inline int nxt(void){
		int cnr=ch[rt][1];
		while(ch[cnr][0])
			cnr=ch[cnr][0];
		return cnr;
	}
	inline void del(int k){
		rk(k);
		if(cnt[rt]>1){
			--cnt[rt];
			maintain(rt);
			return;
		}
		if(!ch[rt][0]&&!ch[rt][1]){
			clear(rt);
			rt=0;
			return;
		}
		if(!ch[rt][0]){
			int cnr=rt;
			rt=ch[rt][1];
			fa[rt]=0;
			clear(cnr);
			return;
		}
		if(!ch[rt][1]){
			int cnr=rt;
			rt=ch[rt][0];
			fa[rt]=0;
			clear(cnr);
			return;
		}
		int x=pre(),cnr=rt;
		splay(x,0);
		fa[ch[cnr][1]]=x;
		ch[x][1]=ch[cnr][1];
		clear(cnr);
		maintain(rt);
		return;
	}
};

int n;
Splay T;

int main(void){
	n=read();
	while(n--){
		static int opt,x;
		opt=read(),x=read();
		if(opt==1)
			T.ins(x);
		if(opt==2)
			T.del(x);
		if(opt==3)
			printf("%d\n",T.rk(x));
		if(opt==4)
			printf("%d\n",T.kth(x));
		if(opt==5){
			T.ins(x);
			printf("%d\n",T.val[T.pre()]);
			T.del(x);
		}
		if(opt==6){
			T.ins(x);
			printf("%d\n",T.val[T.nxt()]);
			T.del(x);
		}
	}
	return 0;
}