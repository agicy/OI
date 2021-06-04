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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int mod=19940417;
const int MAXN=5e4+5;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt &a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
	inline operator int(void){
		return x;
	}
};

const int C=20+1;

typedef vector<modInt> poly;

inline poly merge(const poly& a,const poly& b){
	reg int s=min(C+1,a.size()+b.size()-1);
	poly res(s);
	for(reg int i=0,siza=a.size();i<siza;++i)
		for(reg int j=0,sizb=b.size();j<sizb&&i+j<s;++j)
			res[i+j]+=a[i]*b[j];
	return res;
}

modInt binom[MAXN][C+1];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		poly dat;
		bool tRev;
		modInt tAdd;
		#define dat(x) unit[(x)].dat
		#define tRev(x) unit[(x)].tRev
		#define tAdd(x) unit[(x)].tAdd
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		dat(k)=merge(dat(lson),dat(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			dat(k)={1,a[l]};
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void rev(reg int k){
		for(reg int i=1,siz=dat(k).size();i<siz;i+=2)
			dat(k)[i]=-dat(k)[i];
		tRev(k)=!tRev(k),tAdd(k)=-tAdd(k);
		return;
	}
	inline void add(reg int k,reg int l,reg int r,modInt v){
		reg int s=dat(k).size();
		poly tmp(s);
		tmp[0]=1;
		for(reg int i=1;i<s;++i)
			tmp[i]=tmp[i-1]*v;
		for(reg int i=s-1;i>=0;--i)
			for(reg int j=0;j<i;++j)
				dat(k)[i]+=dat(k)[j]*tmp[i-j]*binom[(r-l+1)-j][i-j];
		tAdd(k)+=v;
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tRev(k)){
			rev(lson),rev(rson);
			tRev(k)=false;
		}
		if(tAdd(k)){
			add(lson,l,mid,tAdd(k)),add(rson,mid+1,r,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void updateAdd(reg int k,reg int l,reg int r,reg int L,reg int R,modInt v){
		if(L<=l&&r<=R){
			add(k,l,r,v);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			updateAdd(lson,l,mid,L,R,v);
		if(R>mid)
			updateAdd(rson,mid+1,r,L,R,v);
		pushup(k);
		return;
	}
	inline void updateRev(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R){
			rev(k);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			updateRev(lson,l,mid,L,R);
		if(R>mid)
			updateRev(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline poly query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return dat(k);
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return merge(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,q;
int a[MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=(read()%mod+mod)%mod;
	binom[0][0]=1;
	for(reg int i=1;i<=n;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=min(i,C);++j)
			binom[i][j]=binom[i-1][j-1]+binom[i-1][j];
	}
	SegmentTree::build(1,1,n,a);
	while(q--){
		static char opt;
		static int a,b;
		do
			opt=getchar();
		while(!isalpha(opt));
		a=read(),b=read();
		switch(opt){
			case 'I':{
				SegmentTree::updateAdd(1,1,n,a,b,(read()%mod+mod)%mod);
				break;
			}
			case 'R':{
				SegmentTree::updateRev(1,1,n,a,b);
				break;
			}
			case 'Q':{
				writeln(SegmentTree::query(1,1,n,a,b)[read()]);
				break;
			}
		}
	}
	flush();
	return 0;
}