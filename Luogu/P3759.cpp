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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline void swap(reg int &a,reg int &b){
	a^=b,b^=a,a^=b;
	return;
}

const int MAXN=5e4+5;
const int mod=1e9+7;
const int A=5e4;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

struct Data{
	int cntP,cntB;
	inline Data(reg int cntP=0,reg int cntB=0):cntP(cntP),cntB(cntB){
		return;
	}
};

inline Data operator+(const Data& a,const Data& b){
	return Data(add(a.cntP,b.cntP),add(a.cntB,b.cntB));
}

inline Data operator-(const Data& a,const Data& b){
	return Data(sub(a.cntP,b.cntP),sub(a.cntB,b.cntB));
}

namespace BIT{
	namespace SegmentTree{
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			Data dat;
			inline void Init(void){
				dat=Data(0,0);
				return;
			}
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define dat(x) unit[(x)].dat
		};
		const int MAXSIZE=MAXN*200;
		int tot;
		Node unit[MAXSIZE];
		inline int New(void){
			return ++tot;
		}
		inline void update(reg int &p,reg int l,reg int r,reg int pos,const Data& val){
			if(!p)
				p=New();
			dat(p)=dat(p)+val;
			if(l!=r){
				if(pos<=mid)
					update(lson(p),l,mid,pos,val);
				else
					update(rson(p),mid+1,r,pos,val);
			}
			return;
		}
		inline Data query(reg int p,reg int l,reg int r,reg int L,reg int R){
			if(!p)
				return Data(0,0);
			if(L<=l&&r<=R)
				return dat(p);
			if(L<=mid&&mid<R)
				return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
			else if(L<=mid)
				return query(lson(p),l,mid,L,R);
			else
				return query(rson(p),mid+1,r,L,R);
		}
		#undef lson
		#undef rson
		#undef dat
		#undef mid
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int rt[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(rt,0,sizeof(rt));
		return;
	}
	inline void update(reg int id,reg int a,reg int v){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,A,a,Data(v,1));
		return;
	}
	inline void del(reg int id,reg int a,reg int v){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,A,a,Data(mod-v,mod-1));
		return;
	}
	inline Data query(reg int id,reg int L,reg int R){
		if(id>n) id=n;
		Data res(0,0);
		for(reg int i=id;i;i^=lowbit(i))
			res=res+SegmentTree::query(rt[i],1,A,L,R);
		return res;
	}
	inline Data query(reg int l,reg int r,reg int L,reg int R){
		return query(r,L,R)-query(l-1,L,R);
	}
}

int n,m;
int a[MAXN],v[MAXN];

int main(void){
	//printf("%.1lf MiB\n",sizeof(BIT::SegmentTree::unit)/1048576.0);
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),v[i]=read();
	BIT::Init(n);
	for(reg int i=1;i<=n;++i)
		BIT::update(i,a[i],v[i]);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		Data P=BIT::query(i+1,n,1,a[i]);
		ans=add(ans,add(1ll*v[i]*P.cntB%mod,P.cntP));
 	}
	while(m--){
		static int x,y;
		x=read(),y=read();
		if(x>y)
			swap(x,y);
		if(x!=y){
			reg int L=a[x],R=a[y];
			reg int Min=min(L,R),Max=max(L,R);
			reg int cntP,cntB;
			Data tP;
			tP=BIT::query(x,y,Min+1,Max-1);
			cntP=tP.cntP,cntB=tP.cntB;
			if(Min==L)
				ans=add(ans,add(2ll*cntP%mod,1ll*(cntB+1)*add(v[x],v[y])%mod));
			else
				ans=sub(ans,add(2ll*cntP%mod,1ll*(cntB+1)*add(v[x],v[y])%mod));
			tP=BIT::query(x,y,1,Min-1);
			cntB=tP.cntB;
			ans=add(ans,1ll*cntB*sub(v[y],v[x])%mod);
			tP=BIT::query(x,y,Max+1,n);
			cntB=tP.cntB;
			ans=add(ans,1ll*cntB*sub(v[x],v[y])%mod);
			BIT::del(x,a[x],v[x]),BIT::del(y,a[y],v[y]);
			BIT::update(x,a[y],v[y]),BIT::update(y,a[x],v[x]);
			swap(a[x],a[y]),swap(v[x],v[y]);
		}
		writeln(ans);
	}
	flush();
	return 0;
}