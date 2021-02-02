#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int mod=1e9;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXSIZE=2;

struct Matrix{
	int n,m,unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n=0,reg int m=0,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%mod);
			}
		return res;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
};

int f[MAXN],sf[MAXN];
Matrix M[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		Matrix M;
		int siz,tag;
		#define M(x) unit[(x)].M
		#define siz(x) unit[(x)].siz
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		res.siz=a.siz+b.siz;
		Matrix tmp=b.M*M[a.siz];
		res.M=Matrix(1,2);
		res.M[0][0]=add(a.M.unit[0][0],tmp[0][0]);
		res.M[0][1]=add(a.M.unit[0][1],tmp[0][1]);
		res.tag=0;
		return res;
	}
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		tag(k)=0;
		if(l==r){
			siz(k)=1;
			M(k)=Matrix(1,2);
			M(k)[0][0]=M(k)[0][1]=a[l];
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void Add(reg int k,reg int l,reg int r,reg int val){
		tag(k)=add(tag(k),val);
		M(k)[0][0]=add(M(k)[0][0],1ll*val*sf[r-l]%mod);
		M(k)[0][1]=add(M(k)[0][1],1ll*val*sub(sf[r-l+1],1)%mod);
		return;
	}
	inline void pushdown(reg int k,reg int l,reg int r){
		if(tag(k)){
			Add(lson,l,mid,tag(k));
			Add(rson,mid+1,r,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Add(k,l,r,val);
			return;
		}
		pushdown(k,l,r);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			M(k)[0][0]=M(k)[0][1]=val;
			return;
		}
		pushdown(k,l,r);
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		pushdown(k,l,r);
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
}

int n,m;
int a[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	f[0]=f[1]=1,sf[0]=1,sf[1]=2;
	for(reg int i=2;i<=n;++i){
		f[i]=add(f[i-1],f[i-2]);
		sf[i]=add(sf[i-1],f[i]);
	}
	Matrix f(2,2,0);
	f[0][1]=f[1][0]=f[1][1]=1;
	M[0]=Matrix(2,2,1);
	for(reg int i=1;i<=n;++i)
		M[i]=M[i-1]*f;
	SegmentTree::build(1,1,n,a);
	while(m--){
		static int opt,x,v,l,r,d;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),v=read();
				SegmentTree::update(1,1,n,x,v);
				break;
			}
			case 2:{
				l=read(),r=read();
				printf("%d\n",SegmentTree::query(1,1,n,l,r).M[0][0]);
				break;
			}
			case 3:{
				l=read(),r=read(),d=read();
				SegmentTree::update(1,1,n,l,r,d);
				break;
			}
		}
	}
	return 0;
}