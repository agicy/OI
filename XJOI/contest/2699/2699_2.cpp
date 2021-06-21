#pragma GCC optimize("Ofast")
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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

struct Matrix{
	int x1,y1,x2,y2;
};

int n,m;
Matrix M[MAXN];
int totx,Vx[MAXN<<1],toty,Vy[MAXN<<1];

const int MAXSIZE=MAXN*200;

struct Node{
	int lson,rson,sum;
};

int tot;
Node unit[MAXSIZE];

namespace SegmentTree1{
	#define mid ( ( (l) + (r) ) >> 1 )
	#define lson(x) unit[(x)].lson
	#define rson(x) unit[(x)].rson
	#define sum(x) unit[(x)].sum
	int pos,val;
	inline void update(reg int &k,reg int l,reg int r){
		if(!k)
			k=++tot;
		sum(k)+=val;
		if(l==r)
			return;
		if(pos<=mid)
			update(lson(k),l,mid);
		else
			update(rson(k),mid+1,r);
		return;
	}
	int L,R;
	inline int query(reg int k,reg int l,reg int r){
		if(!k)
			return 0;
		if(L<=l&&r<=R)
			return sum(k);
		if(L<=mid&&mid<R)
			return query(lson(k),l,mid)+query(rson(k),mid+1,r);
		else if(L<=mid)
			return query(lson(k),l,mid);
		else
			return query(rson(k),mid+1,r);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef sum
}

namespace BIT{
	const int MAXSIZE=MAXN*2;
	int n,rt[MAXSIZE];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		SegmentTree1::pos=pos,SegmentTree1::val=val;
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree1::update(rt[i],1,toty);
		return;
	}
	inline int query(reg int id,reg int L,reg int R){
		reg int res=0;
		SegmentTree1::L=L,SegmentTree1::R=R;
		for(reg int i=id;i;i^=lowbit(i))
			res+=SegmentTree1::query(rt[i],1,toty);
		return res;
	}
}

namespace SegmentTree2{
	int rt[MAXN*2];
	#define mid ( ( (l) + (r) ) >> 1 )
	#define lson(x) unit[(x)].lson
	#define rson(x) unit[(x)].rson
	#define sum(x) unit[(x)].sum
	int pos,val;
	inline void update(reg int &p,reg int pre,reg int l,reg int r){
		if(p==pre)
			p=++tot,unit[p]=unit[pre];
		sum(p)+=val;
		if(l!=r){
			if(pos<=mid)
				update(lson(p),lson(pre),l,mid);
			else
				update(rson(p),rson(pre),mid+1,r);
		}
		return;
	}
	int L,R;
	inline int query(reg int p,reg int l,reg int r){
		if(!p)
			return 0;
		if(L<=l&&r<=R)
			return sum(p);
		if(L<=mid&&mid<R)
			return query(lson(p),l,mid)+query(rson(p),mid+1,r);
		else if(L<=mid)
			return query(lson(p),l,mid);
		else
			return query(rson(p),mid+1,r);
	}
	#undef mid
	#undef lson
	#undef rson
	#undef sum
}

struct Event{
	int x,y,val;
	inline Event(reg int x=0,reg int y=0,reg int val=0):x(x),y(y),val(val){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x;
	}
};

bool ed;

int main(void){
	n=read(),m=read();
	Vx[totx++]=-inf,Vx[totx++]=inf;
	Vy[toty++]=-inf,Vy[toty++]=inf;
	for(reg int i=1;i<=n;++i){
		M[i].x1=read(),M[i].y1=read(),M[i].x2=read(),M[i].y2=read();
		Vx[totx++]=M[i].x1-1,Vx[totx++]=M[i].x2;
		Vy[toty++]=M[i].y1-1,Vy[toty++]=M[i].y2;
	}
	sort(Vx,Vx+totx),totx=unique(Vx,Vx+totx)-Vx;
	sort(Vy,Vy+toty),toty=unique(Vy,Vy+toty)-Vy;
	BIT::init(totx);
	reg int tote=0;
	static Event e[MAXN*4];
	for(reg int i=1;i<=n;++i){
		static int le,ri,dn,up;
		le=lower_bound(Vx,Vx+totx,M[i].x1-1)-Vx+1;
		ri=lower_bound(Vx,Vx+totx,M[i].x2)-Vx+1;
		dn=lower_bound(Vy,Vy+toty,M[i].y1-1)-Vy+1;
		up=lower_bound(Vy,Vy+toty,M[i].y2)-Vy+1;
		e[tote++]=Event(le,dn,1);
		e[tote++]=Event(le,up,-1);
		e[tote++]=Event(ri,dn,-1);
		e[tote++]=Event(ri,up,1);
		M[i].x1=lower_bound(Vx,Vx+totx,M[i].x1)-Vx+1;
		M[i].x2=lower_bound(Vx,Vx+totx,M[i].x2)-Vx+1;
		M[i].y1=lower_bound(Vy,Vy+toty,M[i].y1)-Vy+1;
		M[i].y2=lower_bound(Vy,Vy+toty,M[i].y2)-Vy+1;
	}
	sort(e,e+tote);
	for(reg int i=totx,j=tote-1;i>=1;--i){
		SegmentTree2::rt[i]=SegmentTree2::rt[i+1];
		while(j>=0&&e[j].x>=i){
			SegmentTree2::pos=e[j].y,SegmentTree2::val=e[j].val;
			SegmentTree2::update(SegmentTree2::rt[i],SegmentTree2::rt[i+1],1,toty);
			--j;
		}
	}
	while(m--){
		static int x,y;
		x=lower_bound(Vx,Vx+totx,read())-Vx+1,y=lower_bound(Vy,Vy+toty,read())-Vy+1;
		BIT::update(x,y,1);
	}
	reg int q=read();
	reg int a=read();
	reg int lastans=0;
	while(q--){
		static int type,x,y,k;
		type=read();
		switch(type){
			case 1:{
				x=lower_bound(Vx,Vx+totx,read()+lastans*a)-Vx+1,y=lower_bound(Vy,Vy+toty,read()+lastans*a)-Vy+1;
				BIT::update(x,y,1);
				break;
			}
			case 2:{
				k=read()+lastans*a;
				lastans=BIT::query(M[k].x2,M[k].y1,M[k].y2)-BIT::query(M[k].x1-1,M[k].y1,M[k].y2);
				writeln(lastans);
				break;
			}
			case 3:{
				x=lower_bound(Vx,Vx+totx,read()+lastans*a)-Vx+1,y=lower_bound(Vy,Vy+toty,read()+lastans*a)-Vy+1;
				SegmentTree2::L=y,SegmentTree2::R=toty;
				lastans=SegmentTree2::query(SegmentTree2::rt[x],1,toty);
				writeln(lastans);
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}