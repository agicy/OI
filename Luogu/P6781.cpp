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
inline uint32_t read_uint32(void){
	reg char ch=getchar();
	reg uint32_t res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg uint32_t x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e6+5;
const int MAXM=2e5+5;

mt19937 rng;

inline uint32_t max(reg uint32_t a,reg uint32_t b){
	return a>b?a:b;
}

inline uint32_t nand(reg uint32_t a,reg uint32_t b){
	return ~(a&b);
}

struct Data{
	int cnt;
	uint32_t Max,Nand0,Nand1;
};

inline Data empDat(void){
	Data res;
	res.cnt=0;
	res.Max=0,res.Nand0=-1,res.Nand1=-1;
	return res;
}

inline Data getDat(reg uint32_t val){
	Data res;
	res.cnt=1;
	res.Max=val;
	res.Nand0=-1;
	res.Nand1=(-1)^val;
	return res;
}

inline Data merge(const Data& a,const Data& b){
	if(!a.cnt)
		return b;
	if(!b.cnt)
		return a;
	Data res;
	res.cnt=a.cnt+b.cnt;
	res.Max=max(a.Max,b.Max);
	res.Nand0=(a.Nand0&b.Nand1)|((~a.Nand0)&b.Nand0);
	res.Nand1=(a.Nand1&b.Nand1)|((~a.Nand1)&b.Nand0);
	return res;
}

namespace FHQTreap{
	struct Node{
		uint32_t lson,rson,siz;
		//basic
		uint32_t opt;
		Data val;
		//one point
		uint32_t lcnt,mopt,mcnt,rcnt;
		Data lef,mid,rig;
		//sub tree
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define opt(x) unit[(x)].opt
		#define val(x) unit[(x)].val
		#define lcnt(x) unit[(x)].lcnt
		#define mopt(x) unit[(x)].mopt
		#define mcnt(x) unit[(x)].mcnt
		#define rcnt(x) unit[(x)].rcnt
		#define lef(x) unit[(x)].lef
		#define mid(x) unit[(x)].mid
		#define rig(x) unit[(x)].rig
	};
	Node unit[MAXN];
	inline void init(void){
		lson(0)=rson(0)=siz(0)=0;
		lcnt(0)=rcnt(0)=0;
		opt(0)=0,val(0)=empDat();
		lcnt(0)=rcnt(0)=0;
		mopt(0)=-1;
		mcnt(0)=0;
		mid(0)=empDat();
		lef(0)=rig(0)=empDat();
		return;
	}
	inline void setVal(reg uint32_t p,reg uint32_t a,reg uint32_t b){
		siz(p)=1;
		opt(p)=a;
		val(p)=getDat(b);
		mopt(p)=a;
		mcnt(p)=1;
		mid(p)=val(p);
		return;
	}
	inline Data solveLef(reg uint32_t p,reg uint32_t k){
		if(!k)
			return empDat();
		//printf("solveLef p=%u k=%u\n",p,k);
		reg uint32_t clr,crl;
		Data tlr,trl;
		if(mopt(lson(p))==1){ //'('
			clr=mcnt(lson(p))+rcnt(lson(p)),tlr=merge(mid(lson(p)),rig(lson(p)));
		}
		else{ //')'
			clr=rcnt(lson(p)),tlr=rig(lson(p));
		}
		if(mopt(rson(p))==1){ //'('
			crl=lcnt(rson(p)),trl=lef(rson(p));
		}
		else{ //')'
			crl=lcnt(rson(p))+mcnt(rson(p)),trl=merge(lef(rson(p)),mid(rson(p)));
		}

		//assert(p);
		//assert(k<=siz(p));
		if(opt(p)==1) //'('
			if(clr+1>=crl){
				//puts("S1");
				return solveLef(lson(p),k);
			}
			else
				if(crl-(clr+1)>=k){
					//puts("S2");
					return solveLef(rson(p),k);
				}
				else{
					//puts("S3");
					assert(crl-(clr+1)==mcnt(p));
					return merge(solveLef(lson(p),k-(crl-(clr+1))),mid(p));
				}
		else //')'
			if(clr>=1+crl){
				//puts("S4");
				return solveLef(lson(p),k);
			}
			else
				if((crl+1)-clr>=k){
					//puts("S5");
					if((crl+1)-clr==k)
						return mid(p);
					else
						return solveLef(rson(p),k);
				}
				else{
					//puts("S6");
					assert((crl+1)-clr==mcnt(p));
					return merge(solveLef(lson(p),k-((crl+1)-clr)),mid(p));
				}
	}
	inline Data solveRig(reg uint32_t p,reg uint32_t k){
		if(!k)
			return empDat();
		//printf("solveRig p=%u k=%u\n",p,k);
		reg uint32_t clr,crl;
		Data tlr,trl;
		if(mopt(lson(p))==1){ //'('
			clr=mcnt(lson(p))+rcnt(lson(p)),tlr=merge(mid(lson(p)),rig(lson(p)));
		}
		else{ //')'
			clr=rcnt(lson(p)),tlr=rig(lson(p));
		}
		if(mopt(rson(p))==1){ //'('
			crl=lcnt(rson(p)),trl=lef(rson(p));
		}
		else{ //')'
			crl=lcnt(rson(p))+mcnt(rson(p)),trl=merge(lef(rson(p)),mid(rson(p)));
		}

		//assert(p);
		//assert(k<=siz(p));
		if(opt(p)==1) //'('
			if(crl>=clr+1){
				//puts("pS1");
				return solveRig(rson(p),k);
			}
			else
				if((clr+1)-crl>=k){
					//puts("pS2");
					if((clr+1)-crl==k)
						return mid(p);
					else
						return merge(solveRig(lson(p),k-1),val(p));
				}
				else{
					//puts("pS3");
					//printf("%u %d %d\n",mcnt(p),(clr+1)-crl,mid(p).cnt);
					assert((clr+1)-crl==mcnt(p));
					return merge(mid(p),solveRig(rson(p),k-((clr+1)-crl)));
				}
		else //')'
			if(crl+1>=clr){
				//puts("pS4");
				return solveRig(rson(p),k);
			}
			else
				if(clr-(crl+1)>=k){
					//puts("pS5");
					return solveRig(lson(p),k);
				}
				else{
					//puts("pS6");
					assert((clr-(crl+1))==mcnt(p));
					return merge(mid(p),solveRig(rson(p),k-(clr-(crl+1))));
				}
	}
	inline void pushup(reg uint32_t p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		if(!lson(p)&&!rson(p)){
			mopt(p)=opt(p);
			mcnt(p)=1;
			mid(p)=val(p);

			lcnt(p)=rcnt(p)=0;
			lef(p)=rig(p)=empDat();
			return ;
		}
		reg uint32_t cll,clr,crl,crr;
		Data tll,tlr,trl,trr;
		if(mopt(lson(p))==1){ //'('
			cll=lcnt(lson(p)),tll=lef(lson(p));
			clr=mcnt(lson(p))+rcnt(lson(p)),tlr=merge(mid(lson(p)),rig(lson(p)));
		}
		else{ //')'
			cll=lcnt(lson(p))+mcnt(lson(p)),tll=merge(lef(lson(p)),mid(lson(p)));
			clr=rcnt(lson(p)),tlr=rig(lson(p));
		}
		if(mopt(rson(p))==1){ //'('
			crl=lcnt(rson(p)),trl=lef(rson(p));
			crr=mcnt(rson(p))+rcnt(rson(p)),trr=merge(mid(rson(p)),rig(rson(p)));
		}
		else{ //')'
			crl=lcnt(rson(p))+mcnt(rson(p)),trl=merge(lef(rson(p)),mid(rson(p)));
			crr=rcnt(rson(p)),trr=rig(rson(p));
		}
		lcnt(p)=cll,lef(p)=tll;
		rcnt(p)=crr,rig(p)=trr;
		if(opt(p)==1){ //'('
			if(clr+1>crl){
				if(!crl){
					mopt(p)=1;
					mcnt(p)=(clr+1)-crl;
					mid(p)=merge(solveRig(lson(p),clr-crl),val(p));
				}
				else{
					mopt(p)=1;
					mcnt(p)=(clr+1)-crl;
					mid(p)=solveRig(lson(p),clr+1-crl);
				}
			}
			else if(clr+1==crl){
				mopt(p)=-1;
				mcnt(p)=0;
				mid(p)=empDat();
			}
			else{
				mopt(p)=0;
				mcnt(p)=crl-(clr+1);
				mid(p)=solveLef(rson(p),crl-(clr+1));
			}
		}
		else{ //')'
			if(clr>1+crl){
				mopt(p)=1;
				mcnt(p)=clr-(1+crl);
				mid(p)=solveRig(lson(p),clr-(1+crl));
			}
			else if(clr==1+crl){
				mopt(p)=-1;
				mcnt(p)=0;
				mid(p)=empDat();
			}
			else{
				if(!clr){
					mopt(p)=0;
					mcnt(p)=(1+crl)-clr;
					mid(p)=merge(val(p),solveLef(rson(p),crl-clr));
				}
				else{
					mopt(p)=0;
					mcnt(p)=(1+crl)-clr;
					mid(p)=solveLef(rson(p),(1+crl)-clr);
				}
			}
		}
		/*if(!lson(p)&&!rson(p)){
			printf("ready to merge p=%u\n",p);
			printf("over\n");
		}*/
		return;
	}
	inline uint32_t merge(reg uint32_t x,reg uint32_t y){
		if(!x||!y)
			return x|y;
		if(rng()%(siz(x)+siz(y))<siz(x)){
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
	inline void split(reg uint32_t p,reg uint32_t k,reg uint32_t &x,reg uint32_t &y){
		if(!p){
			x=y=0;
			return;
		}
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
	}/*
	inline void print(reg int p,reg int dep){
		if(!p)
			return;
		print(lson(p),dep+1),printf("{p=%d,dep=%d,",p,dep),val(p).print(),printf("}"),print(rson(p),dep+1);
	}*/
}

inline uint32_t build(reg uint32_t l,reg uint32_t r,reg uint32_t a[],reg uint32_t b[]){
	if(l>r)
		return 0;
	reg uint32_t mid=(l+r)>>1;
	reg uint32_t p=mid;
	FHQTreap::setVal(p,a[mid],b[mid]);
	FHQTreap::lson(p)=build(l,mid-1,a,b),FHQTreap::rson(p)=build(mid+1,r,a,b);
	FHQTreap::pushup(p);
	return p;
}

uint32_t rt;

inline void update(reg uint32_t x,reg uint32_t y){
	using namespace FHQTreap;
	static uint32_t rt1,mid,rt2;
	split(rt,x,mid,rt2);
	split(mid,x-1,rt1,mid);
	setVal(mid,1-unit[mid].opt,y);
	rt=merge(merge(rt1,mid),rt2);
	return;
}

inline void query(reg uint32_t x,reg uint32_t y){
	using namespace FHQTreap;
	static uint32_t rt1,m,rt2;
	split(rt,x-1,rt1,m);
	split(m,y-x+1,m,rt2);
	Data l,r;
	if(mopt(m)==1) //'('
		l=lef(m),r=merge(mid(m),rig(m));
	else //')'
		l=merge(lef(m),mid(m)),r=rig(m);
	Data res=merge(l,r);
	writeln(res.Max^res.Nand1);
	rt=merge(merge(rt1,m),rt2);
	return;
}

inline void move(reg uint32_t x,reg uint32_t y){
	using namespace FHQTreap;
	static uint32_t rt1,mid,rt2;
	split(rt,x-1,rt1,mid);
	split(mid,y-x+1,mid,rt2);
	rt=merge(merge(rt1,rt2),mid);
	return;
}

uint32_t n,m;
uint32_t a[MAXN],b[MAXN];

bool ed;

int main(void){
	n=read_uint32(),m=read_uint32();
	FHQTreap::init();
	for(reg uint32_t i=1;i<=n;++i)
		a[i]=read_uint32(),b[i]=read_uint32();
	rt=build(1,n,a,b);
	while(m--){
		static uint32_t opt,x,y;
		opt=read_uint32(),x=read_uint32(),y=read_uint32();
		switch(opt){
			case 1:{
				update(x,y);
				break;
			}
			case 2:{
				query(x,y);
				break;
			}
			case 3:{
				move(x,y);
				break;
			}
			default:assert(false);
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}