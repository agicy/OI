#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;

namespace FHQTreap{
	const int MAXSIZE=MAXN;
	struct Node{
		int lson,rson,siz;
		int val;
		bool tRev;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define tRev(x) unit[(x)].tRev
	};
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int v){
		reg int p=++tot;
		lson(p)=rson(p)=0,siz(p)=1;
		val(p)=v,tRev(p)=false;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void rev(reg int p){
		swap(lson(p),rson(p));
		tRev(p)=!tRev(p);
		return;
	}
	inline void pushdown(reg int p){
		if(tRev(p)){
			if(lson(p))
				rev(lson(p));
			if(rson(p))
				rev(rson(p));
			tRev(p)=false;
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(rand()%(siz(x)+siz(y))<siz(x)){
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
	inline void split(reg int p,reg int k,reg int &x,reg int &y){
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
	inline int build(reg int l,reg int r,reg int a[]){
		if(l>r)
			return 0;
		reg int mid=(l+r)>>1;
		reg int p=New(a[mid]);
		lson(p)=build(l,mid-1,a),rson(p)=build(mid+1,r,a);
		pushup(p);
		return p;
	}
	int top,S[MAXSIZE];
	inline void print(reg int p){
		if(!p)
			return;
		pushdown(p);
		print(lson(p)),S[++top]=val(p),print(rson(p));
		return;
	}
}

int n,m;
int rt;

int main(void){
	n=read(),m=read();
	static int val[MAXN];
	for(reg int i=1;i<=n;++i)
		val[i]=i;
	rt=FHQTreap::build(1,n,val);
	while(m--){
		static int l,r;
		static int rt1,mid,rt2;
		l=read(),r=read();
		FHQTreap::split(rt,l-1,rt1,mid);
		FHQTreap::split(mid,r-l+1,mid,rt2);
		FHQTreap::rev(mid);
		rt=FHQTreap::merge(FHQTreap::merge(rt1,mid),rt2);
	}
	FHQTreap::top=0,FHQTreap::print(rt);
	for(reg int i=1;i<=FHQTreap::top;++i)
		write(FHQTreap::S[i]),putchar(i==FHQTreap::top?'\n':' ');
	flush();
	return 0;
}