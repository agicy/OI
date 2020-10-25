#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline char getc(void){
	static char rbuf[100000],*rp1=rbuf,*rp2=rbuf;
	return rp1==rp2&&(rp2=(rp1=rbuf)+fread(rbuf,1,100000,stdin),rp1==rp2)?EOF:*rp1++;
}

inline void read(int &x){
	char ch=getc();
	x=0;
	while(!isdigit(ch))ch=getc();
	while(isdigit(ch))x=10*x+(ch^'0'),ch=getc();
	return;
}

static char wbuf[1<<21];
const int wp2=1<<21;
static int wp1=0;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
	return;
}

inline void putc(const char& ch){
	if(wp1==wp2)
		flush();
	wbuf[wp1++]=ch;
	return;
}

inline void writeln(int x){
	static char buf[25];
	int p=-1;
	if(!x)
		putc('0');
	else
		for(;x;x/=10)
			buf[++p]=(x%10)^'0';
	while(~p)
		putc(buf[p--]);
	putc('\n');
	return;
}

constexpr int MAXN=1e5+5;
constexpr int MAXA=1e5+1;
constexpr int p=998244353;

inline int add(const int& a,const int& b){
	int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(const int& a,const int& b){
	return 1ll*a*b%p;
}

struct Poly{
	int x,y,z;
	inline Poly(void){
		return;
	}
	inline Poly(const int& x,const int& y,const int& z):x(x),y(y),z(z){
		return;
	}
	inline Poly operator+(const Poly& a)const{
		return Poly(add(x,a.x),add(y,a.y),add(z,a.z));
	}
	inline Poly operator*(const Poly& a)const{
		int
		A=mul(x,a.x),
		B=add(mul(x,a.y),mul(y,a.x)),
		C=add(add(mul(x,a.z),mul(z,a.x)),mul(y,a.y)),
		D=add(mul(y,a.z),mul(z,a.y)),
		E=mul(z,a.z);
		return Poly(add(add(A,p-D),p-mul(2,E)),add(B,add(mul(2,D),mul(3,E))),add(C,add(mul(2,D),mul(6,E))));
	}
};

Poly f[MAXA];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		Poly sum,msum,lsum,rsum;
		inline Node(void){
			return;
		}
		inline Node(const Poly& sum,const Poly& msum,const Poly& lsum,const Poly& rsum):sum(sum),msum(msum),lsum(lsum),rsum(rsum){
			return;
		}
		inline Node operator+(const Node& a)const{
			return Node(
				this->sum+a.sum+this->rsum*a.lsum,
				this->msum*a.msum,
				this->lsum+this->msum*a.lsum,
				a.rsum+a.msum*this->rsum
			);
		}
		#define sum(x) unit[(x)].sum
		#define msum(x) unit[(x)].msum
		#define lsum(x) unit[(x)].lsum
		#define rsum(x) unit[(x)].rsum
	};
	Node unit[MAXN<<2];
	inline void pushup(const int& k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(const int& k,const int& l,const int& r){
		if(l==r){
			static int a;
			read(a);
			sum(k)=lsum(k)=rsum(k)=msum(k)=f[a]+Poly(1,0,0);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(const int& k,const int& l,const int& r,const int& pos,const int& val){
		if(l==r){
			sum(k)=lsum(k)=rsum(k)=msum(k)=f[val]+Poly(1,0,0);
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node query(const int& k,const int& l,const int& r,const int& L,const int& R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
}

int n,q,opt,x,y;

int main(void) {
	f[0]=Poly(1,0,0);
	for(int i=1;i<MAXA;++i)
		f[i]=f[i-1]*Poly(0,1,0);
	read(n),read(q);
	SegmentTree::build(1,1,n);
	while(q--){
		read(opt),read(x),read(y);
		switch(opt){
			case 1:{
				SegmentTree::update(1,1,n,x,y);
				break;
			}
			case 2:{
				Poly p=SegmentTree::query(1,1,n,x,y).sum;
				writeln(add(p.y,p.z));
				break;
			}
		}
	}
	flush();
	return 0;
}