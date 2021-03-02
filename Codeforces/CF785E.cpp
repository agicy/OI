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

inline void writeln(reg ll x){
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

const int MAXN=2e5+5;
const int MAXA=2e5+5;

int A;

namespace BIT{
	namespace SegmentTree{
		const int MAXSIZE=2e7+5;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			int siz;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define siz(x) unit[(x)].siz
		};
		int tot;
		Node unit[MAXSIZE];
		inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
			if(!p)
				p=++tot;
			siz(p)+=val;
			if(l!=r){
				if(pos<=mid)
					update(lson(p),l,mid,pos,val);
				else
					update(rson(p),mid+1,r,pos,val);
			}
			return;
		}
		inline int query(reg int p,reg int l,reg int r,reg int L,reg int R){
			if(!p)
				return 0;
			if(L<=l&&r<=R)
				return siz(p);
			if(L<=mid&&mid<R)
				return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
			else if(L<=mid)
				return query(lson(p),l,mid,L,R);
			else
				return query(rson(p),mid+1,r,L,R);
		}
		#undef mid
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,rt[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(rt,0,sizeof(rt));
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,A,pos,val);
		return;
	}
	inline int query(reg int id,reg int L,reg int R){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=SegmentTree::query(rt[i],1,A,L,R);
		return res;
	}
	inline int query(reg int l,reg int r,reg int L,reg int R){
		return query(r,L,R)-query(l-1,L,R);
	}
}

int n,k;
int a[MAXN];

int main(void){
	//printf("%.1lf MiB\n",sizeof(BIT::SegmentTree::unit)/1048576.0);
	A=n=read(),k=read();
	BIT::Init(n);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		a[i]=i;
		BIT::update(i,i,1);
	}
	while(k--){
		static int l,r;
		l=read(),r=read();
		if(l!=r){
			if(l>r)
				swap(l,r);
			if(l+1<=r-1)
				ans+=BIT::query(l+1,r-1,1,a[r]-1)-BIT::query(l+1,r-1,a[r]+1,n)+BIT::query(l+1,r-1,a[l]+1,n)-BIT::query(l+1,r-1,1,a[l]-1);
			if(a[l]>a[r])
				--ans;
			if(a[l]<a[r])
				++ans;
			BIT::update(l,a[l],-1),BIT::update(r,a[r],-1);
			swap(a[l],a[r]);
			BIT::update(l,a[l],1),BIT::update(r,a[r],1);
		}
		writeln(ans);
	}
	flush();
	return 0;
}