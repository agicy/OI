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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=3e5+5;
const int mod=1e9+7;
const int MAXSIZE=4e6;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int add(reg int a,reg int b,reg int c){
	return add(add(a,b),c);
}

int n,m;
int rt;

namespace FHQTreap{
	struct Node{
		int key;
		int ch[2];
		int siz;
		int sum,val;
		int tAdd,tCov;
		#define key(x) unit[(x)].key
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define sum(x) unit[(x)].sum
		#define val(x) unit[(x)].val
		#define tAdd(x) unit[(x)].tAdd
		#define tCov(x) unit[(x)].tCov
		#define tRev(x) tRev[(x)]
	};
	bool tRev[MAXSIZE];
	#define lson(x) ch(x)[0]
	#define rson(x) ch(x)[1]
	int tot;
	Node unit[MAXSIZE];
	inline int New(reg int v){
		reg int p=++tot;
		key(p)=rand();
		lson(p)=rson(p)=0;
		siz(p)=1,sum(p)=val(p)=v;
		tAdd(p)=0,tCov(p)=-1,tRev(p)=0;
		return p;
	}
	inline int copy(reg int p){
		reg int q=++tot;
		unit[q]=unit[p];
		tRev(q)=tRev(p);
		return q;
	}
	inline void pushup(reg int p){
		sum(p)=add(sum(lson(p)),sum(rson(p)),val(p));
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		return;
	}
	inline void Rev(reg int p){
		swap(lson(p),rson(p));
		tRev(p)^=1;
		return;
	}
	inline void Add(reg int p,reg int v){
		sum(p)=add(sum(p),1ll*siz(p)*v%mod);
		val(p)=add(val(p),v);
		tAdd(p)=add(tAdd(p),v);
		return;
	}
	inline void Cov(reg int p,reg int v){
		sum(p)=1ll*siz(p)*v%mod;
		val(p)=v;
		tAdd(p)=0,tCov(p)=v;
		return;
	}
	inline void pushdown(reg int p){
		if((~tCov(p))||tAdd(p)||tRev(p)){
			if(lson(p))
				lson(p)=copy(lson(p));
			if(rson(p))
				rson(p)=copy(rson(p));
		}
		if(~tCov(p)){
			if(lson(p))
				Cov(lson(p),tCov(p));
			if(rson(p))
				Cov(rson(p),tCov(p));
			tCov(p)=-1;
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
		//pushdown(x),pushdown(y);
		if(key(x)<key(y)){
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
}

inline int opt1(reg int l,reg int r){
	using namespace FHQTreap;
	int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
	reg int res=sum(mid);
	rt=merge(merge(rt1,mid),rt2);
	return res;
}

inline void opt2(reg int l,reg int r,reg int val){
	using namespace FHQTreap;
	int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
    //mid=copy(mid);
	Cov(mid,val);
	rt=merge(merge(rt1,mid),rt2);
	return;
}

inline void opt3(reg int l,reg int r,reg int val){
	using namespace FHQTreap;
	int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
    //mid=copy(mid);
	Add(mid,val);
	rt=merge(merge(rt1,mid),rt2);
	return;
}

inline void opt4(int l1,int r1,int l2,int r2){
	using namespace FHQTreap;
	reg bool flag=false;
	if(l1>l2)
		flag=true,swap(l1,l2),swap(r1,r2);
	int rt1,rt2,rt3,rt4,rt5;
	split(rt,l1-1,rt1,rt2);
	split(rt2,r1-l1+1,rt2,rt3);
	split(rt3,l2-r1-1,rt3,rt4);
	split(rt4,r2-l2+1,rt4,rt5);
	if(flag)
		rt2=copy(rt4);
	else
		rt4=copy(rt2);
	rt=merge(merge(merge(merge(rt1,rt2),rt3),rt4),rt5);
	return;
}

inline void opt5(int l1,int r1,int l2,int r2){
	using namespace FHQTreap;
	if(l1>l2)
		swap(l1,l2),swap(r1,r2);
	int rt1,rt2,rt3,rt4,rt5;
	split(rt,l1-1,rt1,rt2);
	split(rt2,r1-l1+1,rt2,rt3);
	split(rt3,l2-r1-1,rt3,rt4);
	split(rt4,r2-l2+1,rt4,rt5);
	rt=merge(merge(merge(merge(rt1,rt4),rt3),rt2),rt5);
	return;
}

inline void opt6(reg int l,reg int r){
	using namespace FHQTreap;
	int rt1,mid,rt2;
	split(rt,l-1,rt1,mid);
	split(mid,r-l+1,mid,rt2);
    //mid=copy(mid);
	Rev(mid);
	rt=merge(merge(rt1,mid),rt2);
	return;
}

int top,S[MAXN];

inline void dfs(reg int u){
	using namespace FHQTreap;
	pushdown(u);
	if(lson(u))
		dfs(lson(u));
	S[++top]=val(u);
	if(rson(u))
		dfs(rson(u));
	return;
}

inline int build(reg int l,reg int r){
	using namespace FHQTreap;
	if(l>r)
		return 0;
	reg int mid=(l+r)>>1;
	reg int p=New(S[mid]);
	lson(p)=build(l,mid-1),rson(p)=build(mid+1,r);
	pushup(p);
	return p;
}

int main(void){
	//printf("%.0lf\n",(sizeof(FHQTreap::unit)+sizeof(FHQTreap::tRev))/1048576.0);
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		S[i]=read();
	rt=build(1,n);
	while(m--){
		static int opt,l,r,val,l1,r1,l2,r2;
		opt=read();
		switch(opt){
			case 1:{
				l=read(),r=read();
				write(opt1(l,r)),putchar('\n');
				break;
			}
			case 2:{
				l=read(),r=read(),val=read();
				opt2(l,r,val);
				break;
			}
			case 3:{
				l=read(),r=read(),val=read();
				opt3(l,r,val);
				break;
			}
			case 4:{
				l1=read(),r1=read(),l2=read(),r2=read();
				opt4(l1,r1,l2,r2);
				break;
			}
			case 5:{
				l1=read(),r1=read(),l2=read(),r2=read();
				opt5(l1,r1,l2,r2);
				break;
			}
			case 6:{
				l=read(),r=read();
				opt6(l,r);
				break;
			}
		}
		if(FHQTreap::tot>3600000){
			top=0;
			dfs(rt);
			FHQTreap::tot=0;
			rt=build(1,n);
		}
	}
	top=0;
	dfs(rt);
	for(reg int i=1;i<=n;++i)
		write(S[i]),putchar(i==n?'\n':' ');
	flush();
	return 0;
}