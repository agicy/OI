#include<bits/stdc++.h>
//using namespace std;
#define register
typedef long long ll;

namespace Quick {
	class InStream {
		private:
			char buf[1<<21],*p1,*p2;
			inline char getc() {
				return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
			}
			template<class Type> inline int read(Type &x){
				bool f=false;
				char c=getc();
				for(;!isdigit(c);c=getc())if(c=='-')f=true;
				x=0;
				for(;isdigit(c);c=getc())
					x=(x<<1)+(x<<3)+(c^48);
				if(f)x=-x;
				return 1;
			}
		public:
			InStream() {p1=p2=buf;}
			~InStream() {}
			template<class Type> InStream& operator >> (Type &&x) {
				read(x);
				return *this;
			}
		}cin;
	class OutStream {
		private:
			char buf[1<<21];int p1;const int p2=1<<21;
			inline void flush() {
				fwrite(buf,1,p1,stdout);
				p1=0;
			}
			inline void putc(const char &c) {
				if(p1==p2) flush();
				buf[p1++]=c;
			}
			template<class Type> inline void write(Type x) {
				static char buf[25];
				int p=-1;
				if(x<0) putc('-'),x=-x;
				if(x==0) putc('0');
				else for(;x;x/=10) buf[++p]=x%10+48;
				while(~p) putc(buf[p--]);
			}
			inline void write(const char &c) {putc(c);}
		public:
			OutStream() {p1=0;}
			~OutStream() {flush();}
			template<class Type> OutStream& operator << (const Type &x) {
				write(x);
				return *this;
			}
	}cout;
	const char endl('\n');
	template<class Type> inline void swap(Type &a,Type &b) {
		static Type tmp;
		tmp=a;a=b;b=tmp;
	}
}

using namespace Quick;

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;
const double eps=1e-8;

inline int sgn(double x){
	if(fabs(x)<=eps)
		return 0;
	else
		return x<0?-1:1;
}

inline void cMax(int &a,int b){
	if(a<b)
		a=b;
	return;
}

int n,m;
int buff[MAXN],val[MAXN],dp[MAXN];

inline int getId(int i,int j){
	return i*m+j;
}

namespace SegmentTree{
	const int l=0,r=200000;
	const int MAXSIZE=MAXN*500;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Line{
		int k,b;
		inline Line(int k=0,int b=0):k(k),b(b){
			return;
		}
	};
	struct Node{
		int lson,rson,id;
		inline void clear(void){
			lson=rson=id=0;
			return;
		}
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define id(x) unit[(x)].id
	};
	int root,tot,cnt;
	Line L[MAXN];
	Node unit[MAXSIZE];
	inline int calc(const Line& l,int x){
		return l.k*x+l.b;
	}
	inline void update(int &k,int l,int r,int Id){
		if(!k){
			k=++tot;
			unit[k].clear();
		}
		if(!id(k)||calc(L[id(k)],mid)<calc(L[Id],mid))
			swap(Id,id(k));
		if(l==r||L[id(k)].k==L[Id].k||!Id)
			return;
		double mval=(L[id(k)].b-L[Id].b)*1.0/(L[Id].k-L[id(k)].k);
		if(sgn(mval-l)<0||sgn(mval-r)>0)
			return;
		else if(!sgn(mval-mid))
			if(calc(L[id(k)],l)>calc(L[Id],l))
				update(rson(k),mid+1,r,Id);
			else
				update(lson(k),l,mid,Id);
		else if(sgn(mval-mid)<0)
			update(lson(k),l,mid,Id);
		else
			update(rson(k),mid+1,r,Id);
		return;
	}
	inline int query(int k,int l,int r,int p){
		if(!k)
			return -inf;
		if(l==r)
			return calc(L[id(k)],p);
		int res=calc(L[id(k)],p);
		if(p<=mid)
			cMax(res,query(lson(k),l,mid,p));
		else
			cMax(res,query(rson(k),mid+1,r,p));
		return res;
	}
	inline void reset(void){
		L[0]=Line(0,-inf);
		cnt=root=tot=0;
		return;
	}
	inline void insert(int k,int b){
		L[++cnt]=Line(k,b);
		update(root,l,r,cnt);
		return;
	}
	inline int ask(int x){
		return query(root,l,r,x);
	}
	#undef mid
}

inline void solve(int l,int r){
	if(l==r){
		SegmentTree::reset();
		if(l==0)
			dp[0]=0;
		int id=getId(l,0);
		SegmentTree::insert(buff[id],dp[id]+val[id]);
		for(int i=1;i<m;++i){
			++id;
			cMax(dp[id],SegmentTree::ask(i));
			SegmentTree::insert(buff[id],dp[id]+val[id]-i*buff[id]);
		}
		return;
	}
	int mid=((l+r)>>1);
	solve(l,mid);
	SegmentTree::reset();
	for(int j=0;j<m;++j){
		int id=getId(l,j);
		for(int i=l;i<=mid;++i,id+=m)
			SegmentTree::insert(buff[id],-(i+j)*buff[id]+val[id]+dp[id]);
		for(int i=mid+1;i<=r;++i,id+=m)
			cMax(dp[id],SegmentTree::ask(i+j));
	}
	solve(mid+1,r);
	return;
}

int main(void){
	cin>>n>>m;
	memset(dp,-0x3f,sizeof(dp));
	int id=0;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			cin>>buff[id++];
	id=0;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			cin>>val[id++];
	solve(0,n-1);
	cout<<dp[n*m-1];
	return 0;
}