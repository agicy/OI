#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}


static char wbuf[1<<21];
int wp1;
const int wp2=1<<21;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
	return;
}

inline void putc(const char &c){
	if(wp1==wp2)
		flush();
	wbuf[wp1++]=c;
	return;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putc('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putc(buf[p--]);
	return;
}

const int MAXL=1e5+5;
const uint p=1331;

char str[MAXL];
uint val[MAXL];
uint basep[MAXL];
int tot,root;

namespace Splay{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int fa,ch[2];
		int val;
		int siz;
		uint hash;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define val(x) unit[(x)].val
		#define siz(x) unit[(x)].siz
		#define hash(x) unit[(x)].hash
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	Node unit[MAXL];
	inline bool get(reg int p){
		return p==rson(fa(p));
	}
	inline void pushup(reg int p){
		if(!p)
			return;
		siz(p)=1;
		if(lson(p))
			siz(p)+=siz(lson(p));
		if(rson(p))
			siz(p)+=siz(rson(p));
		hash(p)=hash(lson(p))+val(p)*basep[siz(lson(p))]+hash(rson(p))*basep[siz(lson(p))+1];
		return;
	}
	inline int build(reg int l,reg int r,reg int father,reg uint V[]){
		if(l>r)
			return 0;
		reg int p=++tot;
		fa(p)=father,lson(p)=build(l,mid-1,p,V),rson(p)=build(mid+1,r,p,V);
		siz(p)=1,val(p)=V[mid];
		pushup(p);
		return p;
	}
	inline void rotate(reg int p){
		reg int f=fa(p),ff=fa(f),w=get(p);
		ch(f)[w]=ch(p)[w^1];
		fa(ch(f)[w])=f;
		ch(p)[w^1]=f;
		fa(f)=p;
		fa(p)=ff;
		if(ff)
			ch(ff)[rson(ff)==f]=p;
		pushup(f),pushup(p);
		return;
	}
	inline void splay(reg int p,reg int goal){
		for(reg int f;f=fa(p),f!=goal;rotate(p))
			if(fa(f)!=goal)
				rotate(get(p)==get(f)?f:p);
		pushup(p);
		if(!goal)
			root=p;
		return;
	}
	inline int find(reg int val){
		reg int p=root;
		while(true)
			if(siz(lson(p))+1==val)
				return p;
			else if(siz(lson(p))+1<val)
				val-=siz(lson(p))+1,p=rson(p);
			else
				p=lson(p);
		return -1;
	}
	inline int getVal(reg int l,reg int r){
		reg int x=find(l),y=find(r+2);
		splay(x,0),splay(y,x);
		return hash(lson(y));
	}
	inline void update(reg int u,reg char ch){
		reg int x=find(u);
		splay(x,0);
		val(x)=ch-'a'+1;
		pushup(x);
		return;
	}
	inline void insert(reg int u,reg char ch){
		reg int x=find(u),y=find(u+1);
		splay(x,0),splay(y,x);
		lson(y)=++tot;
		fa(tot)=y;
		val(tot)=hash(tot)=ch-'a'+1;
		splay(tot,0);
		return;
	}
	#undef mid
}

int main(void){
	read(str+1);
	reg int n=strlen(str+1);
	basep[0]=1;
	for(reg int i=1;i<MAXL;++i)
		basep[i]=basep[i-1]*p;
	for(reg int i=2;i<=n+1;++i)
		val[i]=str[i-1]-'a'+1;
	root=Splay::build(1,n+2,0,val);
	reg int m=read();
	while(m--){
		static char opt;
		static int x,y;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'Q':{
				x=read(),y=read();
				if(x>y)
					swap(x,y);
				reg int l=0,r=tot-y-1,mid;
				while(l<r){
					mid=(l+r)>>1;
					if(Splay::getVal(x,x+mid)!=Splay::getVal(y,y+mid))
						r=mid;
					else
						l=mid+1;
				}
				write(l),putc('\n');
				break;
			}
			case 'R':{
				x=read();
				do
					y=getchar();
				while(!isalpha(y));
				Splay::update(x+1,y);
				break;
			}
			case 'I':{
				x=read();
				do
					y=getchar();
				while(!isalpha(y));
				Splay::insert(x+1,y);
				break;
			}
		}
	}
	flush();
	return 0;
}