#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char* s){
	*s=getchar();
	while(*s!='('&&*s!=')') *s=getchar();
	while(*s=='('||*s==')') *(++s)=getchar();
	*s='\0';
	return s;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

mt19937 rng;

namespace FHQTreap{
	const int MAXSIZE=MAXN;
	struct Node{
		int lson,rson,siz;
		int val,sum;
		int lMax,lMin,rMax,rMin;
		bool tRev,tInv;
		char tCov;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
		#define lMax(x) unit[(x)].lMax
		#define lMin(x) unit[(x)].lMin
		#define rMax(x) unit[(x)].rMax
		#define rMin(x) unit[(x)].rMin
		#define tRev(x) unit[(x)].tRev
		#define tInv(x) unit[(x)].tInv
		#define tCov(x) unit[(x)].tCov
	};
	int tot;
	Node unit[MAXSIZE];
	inline int getId(reg char opt){
		//assert(opt=='('||opt==')');
		reg int p=++tot;
		lson(p)=rson(p)=0,siz(p)=1;
		val(p)=sum(p)=(opt=='(')?-1:1;
		lMax(p)=rMax(p)=max(val(p),0);
		lMin(p)=rMin(p)=min(val(p),0);
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
		lMax(p)=max(lMax(lson(p)),sum(lson(p))+val(p)+lMax(rson(p)));
		lMin(p)=min(lMin(lson(p)),sum(lson(p))+val(p)+lMin(rson(p)));
		rMax(p)=max(rMax(rson(p)),sum(rson(p))+val(p)+rMax(lson(p)));
		rMin(p)=min(rMin(rson(p)),sum(rson(p))+val(p)+rMin(lson(p)));
		return;
	}
	inline void rev(reg int p){
		tRev(p)=!tRev(p);
		swap(lson(p),rson(p));
		swap(lMax(p),rMax(p));
		swap(lMin(p),rMin(p));
		return;
	}
	inline void inv(reg int p){
		tInv(p)=!tInv(p);
		val(p)=-val(p),sum(p)=-sum(p);
		swap(lMax(p),lMin(p)),lMax(p)=-lMax(p),lMin(p)=-lMin(p);
		swap(rMax(p),rMin(p)),rMax(p)=-rMax(p),rMin(p)=-rMin(p);
		if(tCov(p))
			tCov(p)='('^')'^tCov(p);
		return;
	}
	inline void cov(reg int p,reg char opt){
		tCov(p)=opt;
		val(p)=(opt=='(')?-1:1;
		sum(p)=siz(p)*val(p);
		lMax(p)=max(sum(p),0);
		lMin(p)=min(sum(p),0);
		rMax(p)=max(sum(p),0);
		rMin(p)=min(sum(p),0);
		tRev(p)=tInv(p)=false;
		return;
	}
	inline void pushdown(reg int p){
		if(tRev(p)){
			if(lson(p)) rev(lson(p));
			if(rson(p)) rev(rson(p));
			tRev(p)=false;
		}
		if(tInv(p)){
			if(lson(p)) inv(lson(p));
			if(rson(p)) inv(rson(p));
			tInv(p)=false;
		}
		if(tCov(p)){
			if(lson(p)) cov(lson(p),tCov(p));
			if(rson(p)) cov(rson(p),tCov(p));
			tCov(p)=0;
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if((int)rng()%(siz(x)+siz(y))<siz(x)){
			pushdown(x);
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			pushdown(y);
			lson(y)=merge(x,lson(y));
			pushup(y);
			return y;
		}
	}
	inline void split(reg int p,reg int k,reg int& x,reg int& y){
		if(!p){
			x=y=0;
			return;
		}
		pushdown(p);
		if(siz(lson(p))<k){
			x=p;
			split(rson(x),k-siz(lson(p))-1,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			split(lson(y),k,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline int build(reg int l,reg int r,reg char a[]){
		if(l>r)
			return 0;
		reg int mid=(l+r)>>1;
		reg int p=getId(a[mid]);
		lson(p)=build(l,mid-1,a),rson(p)=build(mid+1,r,a);
		pushup(p);
		return p;
	}
}

int n,q;
char s[MAXN];
int rt;

inline void Swap(reg int l,reg int r){
	int rt1,mid,rt2;
	FHQTreap::split(rt,l-1,rt1,mid);
	FHQTreap::split(mid,r-l+1,mid,rt2);

	FHQTreap::rev(mid);

	rt=FHQTreap::merge(FHQTreap::merge(rt1,mid),rt2);
	return;
}

inline void Invert(reg int l,reg int r){
	int rt1,mid,rt2;
	FHQTreap::split(rt,l-1,rt1,mid);
	FHQTreap::split(mid,r-l+1,mid,rt2);

	FHQTreap::inv(mid);

	rt=FHQTreap::merge(FHQTreap::merge(rt1,mid),rt2);
	return;
}

inline void Replace(reg int l,reg int r,reg char c){
	int rt1,mid,rt2;
	FHQTreap::split(rt,l-1,rt1,mid);
	FHQTreap::split(mid,r-l+1,mid,rt2);

	FHQTreap::cov(mid,c);

	rt=FHQTreap::merge(FHQTreap::merge(rt1,mid),rt2);
	return;
}

inline void Query(reg int l,reg int r){
	int rt1,mid,rt2;
	FHQTreap::split(rt,l-1,rt1,mid);
	FHQTreap::split(mid,r-l+1,mid,rt2);

	reg int ans=((FHQTreap::unit[mid].lMax+1)>>1)+((-FHQTreap::unit[mid].rMin+1)>>1);
	writeln(ans);

	rt=FHQTreap::merge(FHQTreap::merge(rt1,mid),rt2);
	return;
}

bool ed;

int main(void){
	n=read(),q=read();
	read(s+1);
	rt=FHQTreap::build(1,n,s);
	while(q--){
		static char opt,c;
		static int a,b;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'R':{
				a=read(),b=read();
				do
					c=getchar();
				while(c!='('&&c!=')');
				Replace(a,b,c);
				break;
			}
			case 'S':{
				a=read(),b=read();
				Swap(a,b);
				break;
			}
			case 'I':{
				a=read(),b=read();
				Invert(a,b);
				break;
			}
			case 'Q':{
				a=read(),b=read();
				Query(a,b);
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}