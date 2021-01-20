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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(isspace(*s))*s=getchar();
	while(!isspace(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXS=2*1024*1024+5;
const int MAXSIZE=5e6;

int ptr;
int rt;

namespace FHQTreap{
	struct Node{
		int ch[2];
		int siz;
		int val;
		bool tRev;
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define tRev(x) unit[(x)].tRev
	};
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	int tot;
	int top;
	char S[MAXSIZE];
	Node unit[MAXSIZE];
	inline int getId(void){
		return ++tot;
	}
	inline int New(reg int x){
		reg int p=getId();
		lson(p)=rson(p)=0,siz(p)=1,val(p)=x,tRev(p)=false;
		return p;
	}
	inline int copy(reg int p){
		reg int q=getId();
		unit[q]=unit[p];
		return q;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void Rev(reg int p){
		swap(lson(p),rson(p));
		tRev(p)=!tRev(p);
		return;
	}
	inline void pushdown(reg int p){
		if(tRev(p)){
			if(lson(p))
				lson(p)=copy(lson(p)),Rev(lson(p));
			if(rson(p))
				rson(p)=copy(rson(p)),Rev(rson(p));
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
	inline int build(reg int l,reg int r,reg char s[]){
		if(l>r)
			return 0;
		reg int p=New(s[mid]);
		lson(p)=build(l,mid-1,s),rson(p)=build(mid+1,r,s);
		pushup(p);
		return p;
	}
	#undef mid
	inline void print(reg int p){
		if(!p)
			return;
		pushdown(p);
		print(lson(p)),S[++top]=val(p),print(rson(p));
		return;
	}
}

inline void Move(reg int k){
	using namespace FHQTreap;
	ptr=k;
	return;
}

inline void Insert(reg int n,reg char s[]){
	using namespace FHQTreap;
	reg int p=build(1,n,s);
	static int rt1,rt2;
	split(rt,ptr,rt1,rt2);
	rt=merge(merge(rt1,p),rt2);
	return;
}

inline void Delete(reg int n){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	split(rt,ptr,rt1,mid);
	split(mid,n,mid,rt2);
	rt=merge(rt1,rt2);
	return;
}

inline void Rotate(reg int n){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	split(rt,ptr,rt1,mid);
	split(mid,n,mid,rt2);
	mid=copy(mid);
	Rev(mid);
	rt=merge(merge(rt1,mid),rt2);
	return;
}

inline void Get(reg int n){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	split(rt,ptr,rt1,mid);
	split(mid,n,mid,rt2);
	top=0;
	print(mid);
	if(S[1]!='\n')
		putchar(S[1]);
	putchar('\n');
	rt=merge(merge(rt1,mid),rt2);
	return;
}

inline void Prev(void){
	using namespace FHQTreap;
	--ptr;
	return;
}

inline void Next(void){
	using namespace FHQTreap;
	++ptr;
	return;
}

inline void rebuild(void){
	using namespace FHQTreap;
	top=0;
	print(rt);
	tot=0;
	rt=build(1,top,S);
	return;
}

int main(void){
	//printf("%.0lf\n",sizeof(FHQTreap::unit)/1048576.0);
	srand(time(0));
	reg int t=read();
	while(t--){
		static char opt[64];
		static int n,k;
		static char s[MAXS];
		read(opt);
		switch(opt[0]){
			case 'M':{
				k=read();
				Move(k);
				break;
			}
			case 'I':{
				n=read();
				reg int tot=0;
				while(tot<n)
					s[++tot]=getchar();
				Insert(n,s);
				break;
			}
			case 'D':{
				n=read();
				Delete(n);
				break;
			}
			case 'R':{
				n=read();
				Rotate(n);
				break;
			}
			case 'G':{
				Get(1);
				break;
			}
			case 'P':{
				Prev();
				break;
			}
			case 'N':{
				Next();
				break;
			}
		}
		if(FHQTreap::tot>MAXSIZE-2e6)
			rebuild();
	}
	flush();
	return 0;
}