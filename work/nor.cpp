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

const int MAXN=1e5+5;
const int MAXA=1e9;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x){
	return fpow(x,mod-2);
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max;
		int tCov;
		#define Max(x) unit[(x)].Max
		#define tCov(x) unit[(x)].tCov
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int c[]){
		tCov(k)=-1;
		if(l==r){
			Max(k)=c[l];
			return;
		}
		build(lson,l,mid,c),build(rson,mid+1,r,c);
		pushup(k);
		return;
	}
	inline void cov(reg int k,reg int val){
		Max(k)=val;
		tCov(k)=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tCov(k)!=-1){
			cov(lson,tCov(k)),cov(rson,tCov(k));
			tCov(k)=-1;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			cov(k,val);
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
	inline int query(reg int k,reg int l,reg int r,reg int val){
		if(Max(k)<=val)
			return r+1;
		if(l==r)
			return l;
		pushdown(k);
		if(Max(lson)<=val)
			return query(rson,mid+1,r,val);
		else
			return query(lson,l,mid,val);
	}
	inline int getVal(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return Max(k);
		pushdown(k);
		if(pos<=mid)
			return getVal(lson,l,mid,pos);
		else
			return getVal(rson,mid+1,r,pos);
	}
	#undef lson
	#undef rson
	#undef mid
}

struct Data{
	int cnt,pod;
	inline Data(reg int cnt=0,reg int pod=1):cnt(cnt),pod(pod){
		return;
	}
};

inline Data operator+(const Data& a,const Data& b){
	Data res;
	res.cnt=a.cnt+b.cnt;
	res.pod=1ll*a.pod*b.pod%mod;
	return res;
}

namespace BIT{
	namespace SegmentTree{
		const int MAXSIZE=MAXN*200;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			Data dat;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define dat(x) unit[(x)].dat
		};
		int tot;
		Node unit[MAXSIZE];
		inline void Init(void){
			dat(0)=Data(0,1);
			return;
		}
		inline int New(void){
			reg int p=++tot;
			dat(p)=Data(0,1);
			return p;
		}
		inline void pushup(reg int p){
			dat(p)=dat(lson(p))+dat(rson(p));
			return;
		}
		inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
			if(!p)
				p=New();
			if(l==r){
				dat(p).cnt+=val;
				dat(p).pod=fpow(l,dat(p).cnt);
				return;
			}
			else{
				if(pos<=mid)
					update(lson(p),l,mid,pos,val);
				else
					update(rson(p),mid+1,r,pos,val);
			}
			pushup(p);
			return;
		}
		inline int queryCnt(reg int p,reg int l,reg int r,reg int pos){
			if(!p)
				return 0;
			if(l==r)
				return dat(p).cnt;
			if(pos<=mid)
				return queryCnt(lson(p),l,mid,pos);
			else
				return dat(lson(p)).cnt+queryCnt(rson(p),mid+1,r,pos);
		}
		inline int queryPod(reg int p,reg int l,reg int r,reg int pos){
			if(!p)
				return 1;
			if(l==r)
				return dat(p).pod;
			if(pos<=mid)
				return queryPod(lson(p),l,mid,pos);
			else
				return 1ll*dat(lson(p)).pod*queryPod(rson(p),mid+1,r,pos)%mod;
		}
		#undef lson
		#undef rson
		#undef dat
		#undef mid
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,rt[MAXN];
	inline void Init(reg int s){
		n=s;
		SegmentTree::Init();
		memset(rt,0,sizeof(rt));
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,MAXA,pos,val);
		return;
	}
	inline int queryCnt(reg int id,reg int pos){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res=res+SegmentTree::queryCnt(rt[i],1,MAXA,pos);
		return res;
	}
	inline int queryPod(reg int id,reg int pos){
		reg int res=1;
		for(reg int i=id;i;i^=lowbit(i))
			res=1ll*res*SegmentTree::queryPod(rt[i],1,MAXA,pos)%mod;
		return res;
	}
	inline int queryCnt(reg int l,reg int r,reg int pos){
		return queryCnt(r,pos)-queryCnt(l-1,pos);
	}
	inline int queryPod(reg int l,reg int r,reg int pos){
		return 1ll*queryPod(r,pos)*inv(queryPod(l-1,pos))%mod;
	}
	inline int queryPod(reg int l,reg int r,reg int L,reg int R){
		return 1ll*queryPod(l,r,R)*inv(queryPod(l,r,L-1))%mod;
	}
}

int n,q;
int a[MAXN],b[MAXN],c[MAXN];
int ans=1;

struct Node{
	int l,r,val;
	inline Node(reg int l=0,reg int r=0,reg int val=0):l(l),r(r),val(val){
		return;
	}
};

int tot;
Node S[MAXN];

inline void update(reg int y,reg int l,reg int r,reg int val){
	if(y==val)
		return;
	reg int len=r-l+1;
	reg int cnt=BIT::queryCnt(l,r,val);
	ans=1ll*ans*fpow(fpow(val,len-cnt),mod-2)%mod;
	reg int pod=BIT::queryPod(l,r,val+1,y);
	ans=1ll*ans*pod%mod;
	reg int cntN=BIT::queryCnt(l,r,y);
	ans=1ll*ans*fpow(y,len-cntN)%mod;
	return;
}

inline void updateA(reg int x,reg int y){
	reg int ptr=x;
	while(true){
		reg int val=SegmentTree::getVal(1,1,n,x);
		
	}
	printf("updateA %d %d\n",x,y);
	reg int l=1,r=tot+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(S[mid].val>y)
			r=mid;
		else
			l=mid+1;
	}
	reg int R=l-1;
	l=1,r=tot;
	while(l<r){
		mid=(l+r)>>1;
		if(x<=S[mid].r)
			r=mid;
		else
			l=mid+1;
	}
	reg int L=l;
	printf("L=%d R=%d\n",L,R);
	if(L>R)
		return;
	if(S[L].l!=x){
		for(reg int i=tot;i>=L;++i)
			S[i+1]=S[i];
		++tot;

	}
	if(S[L].l==x){
		puts("S1");
		for(reg int i=L;i<=R;++i)
			update(x,y,S[i]);
		S[L].r=S[R].r;
		S[L].val=y;
		for(reg int i=R+1;i<=tot;++i)
			S[i-R+L]=S[i];
		tot-=R-L;
		S[tot+1]=Node(inf,inf,inf);
	}
	else{
		puts("S2");
		for(reg int i=1;i<=tot+1;++i)
			printf("(%d,%d,%d)%c",S[i].l,S[i].r,S[i].val,i==tot+1?'\n':' ');
		update(x,y,Node(x,S[L].r,S[L].val));
		for(reg int i=L+1;i<=R;++i)
			update(x,y,S[i]);
		S[L+1].r=S[R].r;
		S[L].r=x-1;
		S[L+1].l=x;
		S[L+1].val=y;
		for(reg int i=1;i<=tot+1;++i)
			printf("(%d,%d,%d)%c",S[i].l,S[i].r,S[i].val,i==tot+1?'\n':' ');
		for(reg int i=R+1;i<=tot;++i){

			S[i-R+1+L]=S[i];
			printf("%d <- %d\n",i-R+1+L,i);
		}
		tot-=R-L-1;
		S[tot+1]=Node(inf,inf,inf);
	}
	return;
}

inline void updateB(reg int x,reg int y){
	if(b[x]==y)
		return;
	reg int l=1,r=tot+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(S[mid+1].l<=x)
			l=mid+1;
		else
			r=mid;
	}
	reg int id=l,val=S[id].val;
	if(val<=b[x])
		ans=1ll*ans*inv(val)%mod;
	else
		ans=1ll*ans*inv(b[x])%mod;
	BIT::update(x,b[x],-1);
	b[x]=y;
	if(val<=b[x])
		ans=1ll*ans*val%mod;
	else
		ans=1ll*ans*b[x]%mod;
	BIT::update(x,b[x],1);
	return;
}

int main(void){
	//printf("%.1lf MiB\n",sizeof(BIT::SegmentTree::unit)/1048576.0);
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		c[i]=max(c[i-1],a[i]);
	}
	SegmentTree::build(1,1,n,c);

	S[tot+1]=Node(inf,inf,inf);
	for(reg int i=1;i<=tot+1;++i)
		printf("(%d,%d,%d)%c",S[i].l,S[i].r,S[i].val,i==tot+1?'\n':' ');
	BIT::Init(n);
	for(reg int i=1;i<=n;++i){
		b[i]=read();
		ans=1ll*ans*min(b[i],c[i])%mod;
		BIT::update(i,b[i],1);
	}
	for(reg int i=1;i<=q;++i){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 0:{
				x=read(),y=read();
				updateA(x,y);
				break;
			}
			case 1:{
				x=read(),y=read();
				updateB(x,y);
				break;
			}
		}
		for(reg int i=1;i<=tot+1;++i)
			printf("(%d,%d,%d)%c",S[i].l,S[i].r,S[i].val,i==tot+1?'\n':' ');
		printf("%d\n",ans);
	}
	flush();
	return 0;
}