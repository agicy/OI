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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e4+5;
const int mod=998244353;

struct modInt{
	int x;
	inline modInt(void){return;}
	inline modInt(reg int x):x(x){return;}
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
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

template<const int N,const int M> struct Matrix{
	modInt unit[N][M];
	inline Matrix<N,M>(void){
		return;
	}
	inline Matrix<N,M>(const modInt& x){
		for(reg int i=0;i<N;++i)
			for(reg int j=0;j<M;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
};

template<const int N,const int M,const int K> inline Matrix<N,K> operator*(const Matrix<N,M> & a,const Matrix<M,K>& b){
	Matrix<N,K> res(0);
	for(reg int i=0;i<N;++i)
		for(reg int k=0;k<M;++k)
			for(reg int j=0;j<K;++j)
				res.unit[i][j]+=a.unit[i][k]*b.unit[k][j];
	return res;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		Matrix<3,3> M;
		#define M(x) unit[(x)].M
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		M(k)=M(lson)*M(rson);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,const Matrix<3,3>& val){
		if(l==r){
			M(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline void query(reg int k,reg int l,reg int r,reg int L,reg int R,Matrix<1,3>& res){
		if(L<=l&&r<=R){
			res=res*M(k);
			return;
		}
		if(L<=mid)
			query(lson,l,mid,L,R,res);
		if(R>mid)
			query(rson,mid+1,r,L,R,res);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef M
}

int n,q;

bool ed;

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		static modInt p,a,b;
		p=read(),a=read(),b=read();
		static Matrix<3,3> tmp;
		tmp.unit[0][0]=p*a*a-p+1,tmp.unit[0][1]=0,tmp.unit[0][2]=0;
		tmp.unit[1][0]=a*b*p*2,tmp.unit[1][1]=a*p-p+1,tmp.unit[1][2]=0;
		tmp.unit[2][0]=p*b*b,tmp.unit[2][1]=b*p,tmp.unit[2][2]=1;
		SegmentTree::update(1,1,n,i,tmp);
	}
	while(q--){
		static int i,l,r;
		static modInt p,a,b,x;
		static Matrix<1,3> val;
		switch(read()){
			case 0:{
				i=read(),p=read(),a=read(),b=read();
				static Matrix<3,3> tmp;
				tmp.unit[0][0]=p*a*a-p+1,tmp.unit[0][1]=0,tmp.unit[0][2]=0;
				tmp.unit[1][0]=a*b*p*2,tmp.unit[1][1]=a*p-p+1,tmp.unit[1][2]=0;
				tmp.unit[2][0]=p*b*b,tmp.unit[2][1]=b*p,tmp.unit[2][2]=1;
				SegmentTree::update(1,1,n,i,tmp);
				break;
			}
			case 1:{
				l=read(),r=read(),x=read();
				val.unit[0][0]=x*x,val.unit[0][1]=x,val.unit[0][2]=1;
				SegmentTree::query(1,1,n,l,r,val);
				writeln(val.unit[0][1].x);
				break;
			}
			case 2:{
				l=read(),r=read(),x=read();
				val.unit[0][0]=x*x,val.unit[0][1]=x,val.unit[0][2]=1;
				SegmentTree::query(1,1,n,l,r,val);
				writeln((val.unit[0][0]-val.unit[0][1]*val.unit[0][1]).x);
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