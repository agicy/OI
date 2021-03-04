#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline ll gcd(reg ll a,reg ll b){
	a=abs(a),b=abs(b);
	return b?gcd(b,a%b):a;
}

const int MAXNM=5e5+5;

int n,m,x,y,t;
ll d[MAXNM];
ll a[MAXNM];
ll d1[MAXNM],d2[MAXNM];

namespace SegmentTree2{
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			ll val;
			#define val(x) unit[(x)].val
		};
		Node unit[MAXNM<<4];
		inline int getId(reg int a,reg int b){
			return (a-1)*(m*4+100)+b;
		}
		inline void pushup(reg int id,reg int k){
			val(getId(id,k))=gcd(val(getId(id,lson)),val(getId(id,rson)));
			return;
		}
		inline void update(reg int id,reg int flag,reg int k,reg int l,reg int r,reg int pos,reg ll Val){
			if(l==r){
				if(flag)
					val(getId(id,k))=Val;
				else
					val(getId(id,k))=gcd(val(getId(id<<1,k)),val(getId(id<<1|1,k)));
				return;
			}
			if(pos<=mid)
				update(id,flag,lson,l,mid,pos,Val);
			else
				update(id,flag,rson,mid+1,r,pos,Val);
			pushup(id,k);
			return;
		}
		inline ll query(reg int id,reg int k,reg int l,reg int r,reg int L,reg int R){
			if(L<=l&&r<=R)
				return val(getId(id,k));
			if(L<=mid&&mid<R)
				return gcd(query(id,lson,l,mid,L,R),query(id,rson,mid+1,r,L,R));
			else if(L<=mid)
				return query(id,lson,l,mid,L,R);
			else
				return query(id,rson,mid+1,r,L,R);
		}
		#undef val
		#undef lson
		#undef rson
		#undef mid
	}
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	inline void update(reg int k,reg int l,reg int r,reg int pos1,reg int pos2,reg ll Val){
		if(l==r){
			SegmentTree::update(k,1,1,1,m,pos2,Val);
			return;
		}
		if(pos1<=mid)
			update(lson,l,mid,pos1,pos2,Val);
		else
			update(rson,mid+1,r,pos1,pos2,Val);
		SegmentTree::update(k,0,1,1,m,pos2,Val);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int L1,reg int R1,reg int L2,reg int R2){
		if(L2>R2||L1>R1)
			return 0;
		if(L1<=l&&r<=R1)
			return SegmentTree::query(k,1,1,m,L2,R2);
		if(L1<=mid&&mid<R1)
			return gcd(query(lson,l,mid,L1,R1,L2,R2),query(rson,mid+1,r,L1,R1,L2,R2));
		else if(L1<=mid)
			return query(lson,l,mid,L1,R1,L2,R2);
		else
			return query(rson,mid+1,r,L1,R1,L2,R2);
	}
	#undef lson
	#undef rson
	#undef mid
}

namespace SegmentTree1{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll val;
		#define val(x,y) unit[(x)][(y)].val
	};
	Node unit[2][MAXNM<<2];
	inline void pushup(reg int flag,reg int k){
		val(flag,k)=gcd(val(flag,lson),val(flag,rson));
		return;
	}
	inline void update(reg int flag,reg int k,reg int l,reg int r,reg int pos,reg ll Val){
		if(l==r){
			val(flag,k)=Val;
			return;
		}
		if(pos<=mid)
			update(flag,lson,l,mid,pos,Val);
		else
			update(flag,rson,mid+1,r,pos,Val);
		pushup(flag,k);
		return;
	}
	inline ll query(reg int flag,reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L>R)
			return 0;
		if(L<=l&&r<=R)
			return val(flag,k);
		if(L<=mid&&mid<R)
			return gcd(query(flag,lson,l,mid,L,R),query(flag,rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(flag,lson,l,mid,L,R);
		else
			return query(flag,rson,mid+1,r,L,R);
	}
	#undef val
	#undef lson
	#undef rson
	#undef mid
}

inline int getId(reg int a,reg int b){
	return (a-1)*m+b;
}

int main(void){
	n=read(),m=read(),x=read(),y=read(),t=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			d[getId(i,j)]=readll();
	for(reg int i=1;i<n;++i)
		for(reg int j=1;j<m;++j){
			a[getId(i,j)]=d[getId(i,j)]-d[getId(i+1,j)]-d[getId(i,j+1)]+d[getId(i+1,j+1)];
			SegmentTree2::update(1,1,n,i,j,a[getId(i,j)]);
		}
	for(reg int i=1;i<n;++i){
		d1[i]=d[getId(i+1,y)]-d[getId(i,y)];
		SegmentTree1::update(0,1,1,n,i,d1[i]);
	}
	for(reg int i=1;i<m;++i){
		d2[i]=d[getId(x,i+1)]-d[getId(x,i)];
		SegmentTree1::update(1,1,1,m,i,d2[i]);
	}
	while(t--){
		static int opt,x1,x2,y1,y2;
		static ll c;
		opt=read(),x1=read(),y1=read(),x2=read(),y2=read();
		switch(opt){
			case 0:{
				writeln(gcd(gcd(d[getId(x,y)],SegmentTree2::query(1,1,n,x-x1,x+x2-1,y-y1,y+y2-1)),gcd(SegmentTree1::query(0,1,1,n,x-x1,x+x2-1),SegmentTree1::query(1,1,1,m,y-y1,y+y2-1))));
				break;
			}
			case 1:{
				c=readll();
				if(x1!=1&&y1!=1)
					SegmentTree2::update(1,1,n,x1-1,y1-1,a[getId(x1-1,y1-1)]+=c);
				if(x1!=1&&y2!=m)
					SegmentTree2::update(1,1,n,x1-1,y2,a[getId(x1-1,y2)]-=c);
				if(x2!=n&&y1!=1)
					SegmentTree2::update(1,1,n,x2,y1-1,a[getId(x2,y1-1)]-=c);
				if(x2!=n&&y2!=m)
					SegmentTree2::update(1,1,n,x2,y2,a[getId(x2,y2)]+=c);
				if(y1<=y&&y<=y2){
					if(x1!=1)
						SegmentTree1::update(0,1,1,n,x1-1,d1[x1-1]+=c);
					if(x2!=n)
						SegmentTree1::update(0,1,1,n,x2,d1[x2]-=c);
				}
				if(x1<=x&&x<=x2){
					if(y1!=1)
						SegmentTree1::update(1,1,1,m,y1-1,d2[y1-1]+=c);
					if(y2!=m)
						SegmentTree1::update(1,1,1,m,y2,d2[y2]-=c);
				}
				if(x1<=x&&x<=x2&&y1<=y&&y<=y2)
					d[getId(x,y)]+=c;
				break;
			}
		}
	}
	flush();
	return 0;
}