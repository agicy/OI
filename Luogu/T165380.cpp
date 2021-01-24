#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[100000];int wp1;const int wp2=100000;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
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

const int MAXN=1e5+5;

int rt;

namespace FHQTreap{
	const int MAXSIZE=6.7e7-50;
	struct Node{
		int lson:30;
		int rson:30;
		int siz:30;
		bool val:2;
		int sum:30;
		bool tRev:2;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
		#define tRev(x) unit[(x)].tRev
	};
	int tot;
	Node unit[MAXSIZE];
	inline int getId(void){
		if(tot==MAXSIZE-1)
			exit(-1);
		return ++tot;
	}
	inline int New(const int& v){
		reg int p=getId();
		lson(p)=rson(p)=0;
		siz(p)=1,sum(p)=val(p)=v;
		tRev(p)=false;
		return p;
	}
	inline int copy(const int& p){
		reg int q=getId();
		unit[q]=unit[p];
		val(q)=val(p);
		tRev(q)=tRev(p);
		return q;
	}
	inline void pushup(const int& p){
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void Rev(const int& p){
		static int t;
		t=lson(p),lson(p)=rson(p),rson(p)=t;
		tRev(p)=!tRev(p);
		return;
	}
	inline void pushdown(const int& p){
		if(tRev(p)){
			if(lson(p))
				lson(p)=copy(lson(p)),Rev(lson(p));
			if(rson(p))
				rson(p)=copy(rson(p)),Rev(rson(p));
			tRev(p)=false;
		}
		return;
	}
	inline void split(const int& p,const int& k,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		pushdown(p);
		if(siz(lson(p))<k){
			x=copy(p);
			int a;
			split(rson(x),k-siz(lson(p))-1,a,y);
			rson(x)=a;
			pushup(x);
		}
		else{
			y=copy(p);
			int a;
			split(lson(y),k,x,a);
			lson(y)=a;
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
	inline int find(const int& p,const int& k){
		if(!p||sum(p)<k)
			return -1;
		pushdown(p);
		if(k<=sum(lson(p)))
			return find(lson(p),k);
		else if(sum(lson(p))+val(p)==k)
			return siz(lson(p))+1;
		else
			return siz(lson(p))+1+find(rson(p),k-sum(lson(p))-val(p));
	}
	/*
	inline void print(reg int p){
		if(!p)
			return;
		pushdown(p);
		print(lson(p)),putchar('0'+val(p)),print(rson(p));
		return;
	}
	*/
}

bitset<MAXN> tmp;

#define mid ( ( (l) + (r) ) >> 1 )

inline int build(const int& l,const int& r){
	using namespace FHQTreap;
	if(l>r)
		return 0;
	reg int p=New(tmp[mid]);
	lson(p)=build(l,mid-1),rson(p)=build(mid+1,r);
	pushup(p);
	return p;
}

#undef mid

int n;
char s[MAXN];
int m;

inline void opt1(const int& l,const int& r,reg int k){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	FHQTreap::split(rt,l-1,rt1,mid);
	FHQTreap::split(mid,r-l+1,mid,rt2);
	static int x,res;
	x=copy(mid),res=copy(mid);
	--k;
	while(k){
		if(k&1)
			res=merge(res,copy(x));
		x=merge(x,copy(x));
		k>>=1;
	}
	rt=FHQTreap::merge(FHQTreap::merge(rt1,res),rt2);
	return;
}

inline void opt2(const int& l,const int& r,reg int k){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
	//reg int res=copy(mid);
/*
	puts("opt2");

	puts("rt1"),print(rt1),puts("");
	puts("mid"),print(mid),puts("");
	puts("rt2"),print(rt2),puts("");*/

	static int x,y;
	x=copy(mid),y=copy(mid);
	Rev(y);
	
	for(reg int i=0,tmpx,tmpy;(1<<i)<k;++i){
		tmpx=copy(x),tmpy=copy(y);
		//puts("FFFF");
		x=merge(x,tmpy),y=merge(y,tmpx);
		//puts("x"),print(x),puts("");
	}
	//puts("x"),print(x),puts("");

	static int lef,rig;
	split(x,siz(mid)*k,lef,rig);

	//puts("lef"),print(lef),puts("");

	rt=merge(merge(rt1,lef),rt2);
	//del(rig);
	return;
}

inline void opt3(const int& l,const int& r){
	using namespace FHQTreap;
	static int rt1,mid,rt2;
	FHQTreap::split(rt,l-1,rt1,mid);
	FHQTreap::split(mid,r-l+1,mid,rt2);
	/*puts("rt1"),print(rt1),puts("");
	puts("mid"),print(mid),puts("");
	puts("rt2"),print(rt2),puts("");*/
	rt=FHQTreap::merge(rt1,rt2);
	//FHQTreap::del(mid);
	return;
}

inline int opt4(const int& k){
	using namespace FHQTreap;
	return FHQTreap::find(rt,k);
}

int main(void){
	printf("%.0lf\n",(sizeof(FHQTreap::unit))/1048576.0);
	srand(time(0));
	n=read();
	read(s+1);
	for(reg int i=1;i<=n;++i)
		tmp[i]=(s[i]^'0');
	rt=build(1,n);
	m=read();
	while(m--){
		static int op,l,r,k;
		op=read();
		//printf("opt=%d\n",op);
		switch(op){
			case 1:{
				l=read(),r=read(),k=read();
				opt1(l,r,k);
				break;
			}
			case 2:{
				l=read(),r=read(),k=read();
				opt2(l,r,k);
				break;
			}
			case 3:{
				l=read(),r=read();
				opt3(l,r);
				break;
			}
			case 4:{
				k=read();
				writeln(opt4(k));
				break;
			}
		}
		//puts("rt:"),FHQTreap::print(rt),puts("");
	}
	flush();
	return 0;
}