#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<20];int wp1;const int wp2=1<<20;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline void swap(reg int &a,reg int &b){
	a^=b,b=a^b,a^=b;
	return;
}

const int MAXN=3e5+5;
const int MAXSIZE=4e6;
const int inf=0x3f3f3f3f;

int n,m;
int rt;

namespace FHQTreap{
	struct Node{
		int ch[2];
		int siz;
		int Max,val;
		int tAdd,tRev;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define Max(x) unit[(x)].Max
		#define val(x) unit[(x)].val
		#define tAdd(x) unit[(x)].tAdd
		#define tRev(x) unit[(x)].tRev
		//#define tRev(x) tRev[(x)]
	};
	//bool tRev[MAXSIZE];
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	int tot;
	int top,S[MAXN];
	Node unit[MAXSIZE];
	inline int New(reg int v){
		reg int p=++tot;
		lson(p)=rson(p)=0;
		siz(p)=1,Max(p)=val(p)=v;
		tAdd(p)=0,tRev(p)=0;
		return p;
	}
	inline int copy(reg int p){
		reg int q=++tot;
		unit[q]=unit[p];
		tRev(q)=tRev(p);
		return q;
	}
	inline void pushup(reg int p){
		Max(p)=max(max(Max(lson(p)),Max(rson(p))),val(p));
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void Rev(reg int p){
		swap(lson(p),rson(p));
		tRev(p)=!tRev(p);
		return;
	}
	inline void Add(reg int p,reg int v){
		Max(p)+=v,val(p)+=v,tAdd(p)+=v;
		return;
	}
	inline void pushdown(reg int p){
		if(tAdd(p)||tRev(p)){
			if(lson(p))
				lson(p)=copy(lson(p));
			if(rson(p))
				rson(p)=copy(rson(p));
		}
		if(tAdd(p)){
			if(lson(p))
				Add(lson(p),tAdd(p));
			if(rson(p))
				Add(rson(p),tAdd(p));
			tAdd(p)=0;
		}
		if(tRev(p)){
			if(lson(p))
				Rev(lson(p));
			if(rson(p))
				Rev(rson(p));
			tRev(p)=false;
		}
		return;
	}
	inline void split(reg int p,reg int k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		pushdown(p);
		if(siz(lson(p))<k){
			x=copy(p);
			split(rson(x),k-siz(lson(p))-1,rson(x),y);
			pushup(x);
		}
		else{
			y=copy(p);
			split(lson(y),k,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(rand()%(siz(x)+siz(y))<siz(x)){
			pushdown(x);
			x=copy(x);
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			pushdown(y);
			y=copy(y);
			lson(y)=merge(x,lson(y));
			pushup(y);
			return y;
		}
	}
	#define mid ( ( (l) + (r) ) >> 1 )
	inline int build(reg int l,reg int r){
		if(l>r)
			return 0;
		reg int p=New(S[mid]);
		lson(p)=build(l,mid-1),rson(p)=build(mid+1,r);
		pushup(p);
		return p;
	}
	#undef mid
	inline void print(reg int u){
		if(!u)
			return;
		pushdown(u);
		print(lson(u)),S[++top]=val(u),print(rson(u));
		return;
	}
}

inline void opt1(reg int l,reg int r,reg int v){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
	mid=copy(mid);
	Add(mid,v);
	rt=merge(merge(rt1,mid),rt2);
	return;
}

inline void opt2(reg int l,reg int r){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
	mid=copy(mid);
	Rev(mid);
	rt=merge(merge(rt1,mid),rt2);
	return;
}

inline void opt3(reg int l,reg int r){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
	writeln(Max(mid));
	rt=merge(merge(rt1,mid),rt2);
	return;
}

int main(void){
	//printf("%.0lf\n",sizeof(FHQTreap::unit)/1048576.0);
	using namespace FHQTreap;
	unit[0].Max=-inf;
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		S[i]=0;
	rt=build(1,n);
	while(m--){
		static int k,l,r,v;
		k=read();
		switch(k){
			case 1:{
				l=read(),r=read(),v=read();
				opt1(l,r,v);
				break;
			}
			case 2:{
				l=read(),r=read();
				opt2(l,r);
				break;
			}
			case 3:{
				l=read(),r=read();
				opt3(l,r);
				break;
			}
		}
		if(tot>3.6e6){
			top=0;
			print(rt);
			tot=0;
			rt=build(1,n);
		}
	}
	flush();
	return 0;
}