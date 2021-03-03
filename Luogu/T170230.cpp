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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
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

inline void swap(reg int &a,reg int &b){
	a^=b,b^=a,a^=b;
	return;
}

const int MAXN=1e5+5;

struct Node{
	int l,r;
};

int n,p;
Node row[MAXN],col[MAXN];

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

namespace Heap{
	struct Node{
		int lson,rson,dis;
		int val,id;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define dis(x) unit[(x)].dis
		#define val(x) unit[(x)].val
		#define id(x) unit[(x)].id
	};
	int tot;
	Node unit[MAXN];
	inline int New(reg int v,reg int d){
		reg int p=++tot;
		lson(p)=rson(p)=0;
		val(p)=v,id(p)=d;
		return p;
	}
	inline void pushup(reg int p){
		dis(p)=dis(rson(p))+1;
		return;
	}
	inline int merge(int x,int y){
		if(!x||!y)
			return x|y;
		if(val(x)>val(y))
			swap(x,y);
		rson(x)=merge(rson(x),y);
		if(dis(lson(x))<dis(rson(x)))
			swap(lson(x),rson(x));
		pushup(x);
		return x;
	}
	inline bool empty(reg int rt){
		return !rt;
	}
	inline int pop(reg int rt){
		return merge(lson(rt),rson(rt));
	}
	inline int topv(reg int rt){
		return val(rt);
	}
	inline int topid(reg int rt){
		return id(rt);
	}
	inline int insert(reg int rt,reg int v,reg int id){
		return merge(rt,New(v,id));
	}
}

int rt[MAXN];
int mat[MAXN];

inline int solve(reg Node poi[],int n){
	Heap::tot=0;
	for(reg int i=1;i<=n;++i)
		rt[i]=0;
	reg int res=1,pod=1;
	for(reg int i=1;i<=n;++i){
		reg int l=poi[i].l,r=poi[i].r;
		mat[i]=Heap::New(r,i);
		rt[l]=Heap::merge(rt[l],mat[i]);
		pod=1ll*pod*(r-l+1)%p;
	}
	for(reg int i=1;i<=n;++i){
		while(!Heap::empty(rt[i])&&Heap::topv(rt[i])<i)
			rt[i]=Heap::pop(rt[i]);
		if(Heap::empty(rt[i]))
			return 0;
		reg int v=Heap::topv(rt[i]),d=Heap::topid(rt[i]);
		rt[i]=Heap::pop(rt[i]);
		if(v<n)
			rt[v+1]=Heap::merge(rt[v+1],rt[i]);
		if(d!=i){
			res=sub(p,res);
			Heap::id(mat[i])=d;
			mat[d]=mat[i];
		}
	}
	return 1ll*res*fpow(pod,p-2)%p;
}

int main(void){
	reg int t=read();
	p=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			row[i].l=read(),row[i].r=read(),col[i].l=read(),col[i].r=read();
		writeln(1ll*solve(row,n)*solve(col,n)%p);
	}
	flush();
	return 0;
}