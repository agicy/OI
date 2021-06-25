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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int add(reg int a,reg int b,reg int mod){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b,reg int mod){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=5e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Data{
		int lef,rig,cnt;
		inline Data(reg int lef=0,reg int rig=0,reg int cnt=0):lef(lef),rig(rig),cnt(cnt){
			return;
		}
	};
	inline Data operator+(const Data& a,const Data& b){
		return Data(a.lef,b.rig,a.cnt+b.cnt-(a.rig==b.lef));
	}
	struct Node{
		Data dat;
		int tCov;
		#define dat(x) unit[(x)].dat
		#define tCov(x) unit[(x)].tCov
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		dat(k)=dat(lson)+dat(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		tCov(k)=0;
		if(l==r){
			dat(k)=Data(a[l],a[l],1);
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void cover(reg int k,reg int val){
		dat(k)=Data(val,val,1),tCov(k)=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tCov(k)){
			cover(lson,tCov(k)),cover(rson,tCov(k));
			tCov(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			dat(k)=Data(val,val,1);
			return;
		}
		pushdown(k);
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cover(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return dat(k).lef;
		pushdown(k);
		if(pos<=mid)
			return query(lson,l,mid,pos);
		else
			return query(rson,mid+1,r,pos);
	}
	inline Data query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return dat(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int delta;
bool flag;
int n,c;
int x[MAXN];

int main(void){
	n=read(),c=read();
	for(reg int i=0;i<n;++i)
		x[i]=read();
	SegmentTree::build(1,0,n-1,x);
	reg int q=read();
	while(q--){
		static char opt;
		static int i,j,k,c;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'R':{
				k=read();
				if(flag)
					delta=sub(delta,k,n);
				else
					delta=add(delta,k,n);
				break;
			}
			case 'F':{
				flag=!flag;
				break;
			}
			case 'S':{
				i=read()-1,j=read()-1;
				if(flag)
					swap(i,j);
				if(flag)
					i=sub(0,i,n),j=sub(0,j,n);
				reg int x,y;
				x=sub(i,delta,n),y=sub(j,delta,n);
				reg int cx=SegmentTree::query(1,0,n-1,x),cy=SegmentTree::query(1,0,n-1,y);
				SegmentTree::update(1,0,n-1,x,cy),SegmentTree::update(1,0,n-1,y,cx);
				break;
			}
			case 'P':{
				i=read()-1,j=read()-1,c=read();
				if(flag)
					swap(i,j);
				if(flag)
					i=sub(0,i,n),j=sub(0,j,n);
				reg int x,y;
				x=sub(i,delta,n),y=sub(j,delta,n);
				if(x<=y)
					SegmentTree::update(1,0,n-1,x,y,c);
				else{
					SegmentTree::update(1,0,n-1,x,n-1,c);
					SegmentTree::update(1,0,n-1,0,y,c);
				}
				break;
			}
			case 'C':{
				opt=getchar();
				if(opt=='S'){
					i=read()-1,j=read()-1;
					if(flag)
						swap(i,j);
					if(flag)
						i=sub(0,i,n),j=sub(0,j,n);
					reg int x,y;
					x=sub(i,delta,n),y=sub(j,delta,n);
					SegmentTree::Data res;
					if(x<=y)
						res=SegmentTree::query(1,0,n-1,x,y);
					else
						res=SegmentTree::query(1,0,n-1,x,n-1)+SegmentTree::query(1,0,n-1,0,y);
					writeln(res.cnt);
				}
				else{
					SegmentTree::Data res=SegmentTree::query(1,0,n-1,0,n-1);
					writeln(res.cnt-(res.lef==res.rig&&res.cnt>1));
				}
				break;
			}
		}
	}
	flush();
	return 0;
}